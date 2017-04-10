#include <arkhe/osgi/core/framework/ServiceReference.hpp>
#include <arkhe/osgi/core/framework/ServiceReferencePrivate.hpp>


osgi::core::ServiceReference::ServiceReference()
	: d_ptr(new ServiceReferencePrivate(0))
{
}

osgi::core::ServiceReference::ServiceReference(const ServiceReference& ref)
  : d_ptr(ref.d_ptr)
{
	d_func()->ref.ref();
}

osgi::core::ServiceReference::ServiceReference(ServiceRegistrationPrivate* reg)
  : d_ptr(new ServiceReferencePrivate(reg))
{

}


osgi::core::ServiceReference::operator bool() const
{
	return getPlugin();
}


osgi::core::ServiceReference& osgi::core::ServiceReference::operator=(int null)
{
	if (null == 0)
	{
		if (!d_func()->ref.deref())
			delete d_ptr;

		d_ptr = new ServiceReferencePrivate(0);
	}

	return *this;
}

osgi::core::ServiceReference::~ServiceReference()
{
	if (!d_func()->ref.deref())
		delete d_ptr;
}


QVariant osgi::core::ServiceReference::getProperty(const QString& key) const
{
	Q_D(const ServiceReference);

	QMutexLocker lock(&d->registration->propsLock);

	return d->registration->properties.value(key);
}


QStringList osgi::core::ServiceReference::getPropertyKeys() const
{
	Q_D(const ServiceReference);

	QMutexLocker lock(&d->registration->propsLock);

	return d->registration->properties.keys();
}


QSharedPointer<osgi::core::Plugin> osgi::core::ServiceReference::getPlugin() const
{
	if (d_func()->registration == 0 || d_func()->registration->plugin == 0)
	{
		return QSharedPointer<osgi::core::Plugin>();
	}

	return d_func()->registration->plugin->q_func().toStrongRef();
}


QList<QSharedPointer<osgi::core::Plugin> > osgi::core::ServiceReference::getUsingPlugins() const
{
	Q_D(const ServiceReference);
	QMutexLocker lock(&d->registration->propsLock);
	return d->registration->dependents.keys();
}


bool osgi::core::ServiceReference::operator<(const ServiceReference& reference) const
{
	bool sameFw = d_func()->registration->plugin->fwCtx == reference.d_func()->registration->plugin->fwCtx;
	
	if (!sameFw)
	{
		// throw InvalidArgumentException("Can not compare service references "
                                      // "belonging to different framework "
                                      // "instances.");
	}

	int r1 = getProperty(PluginConstants::SERVICE_RANKING).toInt();
	int r2 = reference.getProperty(PluginConstants::SERVICE_RANKING).toInt();

	if (r1 != r2)
	{
		// use ranking if ranking differs
		return r1 < r2;
	}
	else
	{
		qlonglong id1 = getProperty(PluginConstants::SERVICE_ID).toLongLong();
		qlonglong id2 = reference.getProperty(PluginConstants::SERVICE_ID).toLongLong();

		// otherwise compare using IDs,
		// is less than if it has a higher ID.
		return id2< id1;
	}
}


bool osgi::core::ServiceReference::operator==(const ServiceReference& reference) const
{
	return d_func()->registration == reference.d_func()->registration;
}


osgi::core::ServiceReference& osgi::core::ServiceReference::operator=(const ServiceReference& reference)
{
	ServiceReferencePrivate* curr_d = d_func();
  
	d_ptr = reference.d_ptr;
	d_ptr->ref.ref();

	if (!curr_d->ref.deref())
		delete curr_d;

	return *this;
}


uint qHash(const ServiceReference& serviceRef)
{
	return qHash(serviceRef.d_func()->registration);
}


QDebug operator<<(QDebug dbg, const ServiceReference& serviceRef)
{
	dbg.nospace() << "Reference for service object registered from "
      << serviceRef.getPlugin()->getSymbolicName() << " " << serviceRef.getPlugin()->getVersion()
      << " (";

	int i = serviceRef.getPropertyKeys().size();

	foreach(QString key, serviceRef.getPropertyKeys())
	{
		dbg.nospace() << key << "=" << serviceRef.getProperty(key).toString();
		if (--i > 0) dbg.nospace() << ",";
	}
	
	dbg.nospace() << ")";

	return dbg.maybeSpace();
}
