#include <QStringListIterator>
#include <QMutexLocker>
#include <QBuffer>
#include <algorithm>

#include <arkhe/osgi/core/framework/Services.hpp>
#include <arkhe/osgi/core/framework/PluginConstants.hpp>
#include <arkhe/osgi/core/framework/ServiceFactory.hpp>
#include <arkhe/osgi/core/framework/PluginFrameworkContext.hpp>
#include <arkhe/osgi/core/framework/ServiceException.hpp>
#include <arkhe/osgi/core/framework/ServiceRegistration.hpp>
#include <arkhe/osgi/core/framework/LDAPExpr.hpp>


struct ServiceRegistrationComparator
{
	bool operator()(const osgi::core::ServiceRegistration& a, const osgi::core::ServiceRegistration& b) const
	{
		return a < b;
	}
};


osgi::core::Services::Services()
{
}

osgi::core::Services::Services(PluginFrameworkContext* fwCtx)
  : mutex(), framework(fwCtx)
{

}

osgi::core::Services::~Services()
{
	clear();
}

osgi::Dictionary osgi::core::Services::createServiceProperties(const Dictionary& in, const QStringList& classes, long sid)
{
	static qlonglong nextServiceID = 1;
	osgi::Dictionary props = in;

	if (!classes.isEmpty())
	{
		// props.insert(PluginConstants::OBJECTCLASS, classes);
	}

	// props.insert(PluginConstants::SERVICE_ID, sid != -1 ? sid : nextServiceID++);

  return props;
}

void osgi::core::Services::clear()
{
	services.clear();
	classServices.clear();
	framework = 0;
}

osgi::core::ServiceRegistration osgi::core::Services::registerService(PluginPrivate* plugin,
                             const QStringList& classes,
                             QObject* service,
                             const Dictionary& properties)
{
  if (service == 0)
  {
    // throw InvalidArgumentException("Can't register 0 as a service");
  }

  // Check if service implements claimed classes and that they exist.
  for (QStringListIterator i(classes); i.hasNext();)
  {
    QString cls = i.next();
    if (cls.isEmpty())
    {
      // throw InvalidArgumentException("Can't register as null class");
    }

    if (!(qobject_cast<ServiceFactory*>(service)))
    {
      if (!checkServiceClass(service, cls))
      {
        QString msg = QString("Service class %1 is not an instance of %2. Maybe you forgot the Q_INTERFACES macro in the service class.")
            .arg(service->metaObject()->className()).arg(cls);
        // throw InvalidArgumentException(msg);
      }
    }
  }

  ServiceRegistration res(plugin, service,
                             createServiceProperties(properties, classes));
  {
    QMutexLocker lock(&mutex);
    services.insert(res, classes);
    for (QStringListIterator i(classes); i.hasNext(); )
    {
      QString currClass = i.next();
      QList<ServiceRegistration>& s = classServices[currClass];
      QList<ServiceRegistration>::iterator ip =
          std::lower_bound(s.begin(), s.end(), res, ServiceRegistrationComparator());
      s.insert(ip, res);
    }
  }

  ServiceReference r = res.getReference();
  plugin->fwCtx->listeners.serviceChanged(
      plugin->fwCtx->listeners.getMatchingServiceSlots(r),
      ServiceEvent(ServiceEvent::REGISTERED, r));
  return res;
}

//----------------------------------------------------------------------------
void osgi::core::Services::updateServiceRegistrationOrder(const ServiceRegistration& sr,
                                              const QStringList& classes)
{
  QMutexLocker lock(&mutex);
  for (QStringListIterator i(classes); i.hasNext(); )
  {
    QList<ServiceRegistration>& s = classServices[i.next()];
    s.removeAll(sr);
    s.insert(std::lower_bound(s.begin(), s.end(), sr, ServiceRegistrationComparator()), sr);
  }
}

//----------------------------------------------------------------------------
bool osgi::core::Services::checkServiceClass(QObject* service, const QString& cls) const
{
  return service->inherits(cls.toLatin1());
}

//----------------------------------------------------------------------------
QList<osgi::core::ServiceRegistration> osgi::core::Services::get(const QString& clazz) const
{
  QMutexLocker lock(&mutex);
  return classServices.value(clazz);
}

//----------------------------------------------------------------------------
osgi::core::ServiceReference osgi::core::Services::get(PluginPrivate* plugin, const QString& clazz) const
{
  QMutexLocker lock(&mutex);
  try {
    QList<ServiceReference> srs = get_unlocked(clazz, QString(), plugin);
    if (framework->debug.service_reference)
    {
      qDebug() << "get service ref" << clazz << "for plugin"
               << plugin->location << " = " << srs.size() << "refs";
    }
    if (!srs.isEmpty()) {
      return srs.front();
    }
  }
  catch (const InvalidArgumentException& )
  { }

  return ServiceReference();
}

//----------------------------------------------------------------------------
QList<osgi::core::ServiceReference> osgi::core::Services::get(const QString& clazz, const QString& filter,
                                            PluginPrivate* plugin) const
{
  QMutexLocker lock(&mutex);
  return get_unlocked(clazz, filter, plugin);
}

//----------------------------------------------------------------------------
QList<osgi::core::ServiceReference> osgi::core::Services::get_unlocked(const QString& clazz, const QString& filter,
                                                     ctkPluginPrivate* plugin) const
{
  Q_UNUSED(plugin)

  QListIterator<ServiceRegistration>* s = 0;
  QList<ServiceRegistration> v;
  LDAPExpr ldap;
  if (clazz.isEmpty())
  {
    if (!filter.isEmpty())
    {
      ldap = LDAPExpr(filter);
      QSet<QString> matched;
      if (ldap.getMatchedObjectClasses(matched))
      {
        v.clear();
        foreach (QString className, matched)
        {
          const QList<ServiceRegistration>& cl = classServices[className];
          v += cl;
        }
        if (!v.isEmpty())
        {
          s = new QListIterator<ServiceRegistration>(v);
        }
        else
        {
          return QList<ServiceReference>();
        }
      }
      else
      {
        s = new QListIterator<ServiceRegistration>(services.keys());
      }
    }
    else
    {
      s = new QListIterator<ServiceRegistration>(services.keys());
    }
  }
  else
  {
    QList<ServiceRegistration> v = classServices.value(clazz);
    if (!v.isEmpty())
    {
      s = new QListIterator<ServiceRegistration>(v);
    }
    else
    {
      return QList<ServiceReference>();
    }
    if (!filter.isEmpty())
    {
      ldap = LDAPExpr(filter);
    }
  }

  QList<ServiceReference> res;
  while (s->hasNext())
  {
    ServiceRegistration sr = s->next();
    ServiceReference sri = sr.getReference();

    if (filter.isEmpty() || ldap.evaluate(sr.d_func()->properties, false))
    {
      res.push_back(sri);
    }
  }

  delete s;

  return res;
}


void osgi::core::Services::removeServiceRegistration(const ServiceRegistration& sr)
{
  QMutexLocker lock(&mutex);

  QStringList classes = sr.d_func()->properties.value(PluginConstants::OBJECTCLASS).toStringList();
  services.remove(sr);
  for (QStringListIterator i(classes); i.hasNext(); )
  {
    QString currClass = i.next();
    QList<ServiceRegistration>& s = classServices[currClass];
    if (s.size() > 1)
    {
      s.removeAll(sr);
    }
    else
    {
      classServices.remove(currClass);
    }
  }
}

QList<osgi::core::ServiceRegistration> osgi::core::Services::getRegisteredByPlugin(PluginPrivate* p) const
{
	QMutexLocker lock(&mutex);
	QList<ServiceRegistration> res;
	
	for (QHashIterator<ServiceRegistration, QStringList> i(services); i.hasNext(); )
	{
		ServiceRegistration sr = i.next().key();
		if (sr.d_func()->plugin == p)
		{
			res.push_back(sr);
		}
	}

	return res;
}


QList<osgi::core::ServiceRegistration> osgi::core::Services::getUsedByPlugin(QSharedPointer<Plugin> p) const
{
	QMutexLocker lock(&mutex);
	QList<ServiceRegistration> res;

	for (QHashIterator<ServiceRegistration, QStringList> i(services); i.hasNext(); )
	{
		ServiceRegistration sr = i.next().key();
		if (sr.d_func()->isUsedByPlugin(p))
		{
			res.push_back(sr);
		}
	}

	return res;
}
