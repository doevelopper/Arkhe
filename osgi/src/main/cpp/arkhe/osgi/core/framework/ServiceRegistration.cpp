#include <arkhe/osgi/core/framework/ServiceRegistration.hpp>
#include <arkhe/osgi/core/framework/ServiceRegistrationPrivate.hpp>

osgi::core::ServiceRegistration::ServiceRegistration()
  : d_ptr(0)
{
}

osgi::core::ServiceRegistration::ServiceRegistration(const ServiceRegistration& reg)
  : d_ptr(reg.d_ptr)
{
	if (d_func()) d_func()->ref.ref();
}

osgi::core::ServiceRegistration::ServiceRegistration(ServiceRegistrationPrivate* registrationPrivate)
  : d_ptr(registrationPrivate)
{
	if(d_func()) d_func()->ref.ref();
}

osgi::core::ServiceRegistration::~ServiceRegistration()
{
  if (d_func() && !d_func()->ref.deref())
    delete d_ptr;
}

osgi::core::ServiceRegistration::ServiceRegistration(PluginPrivate* plugin, QObject* service, const osgi::Dictionary& props)
  : d_ptr(new ServiceRegistrationPrivate(plugin, service, props))
{

}


osgi::core::ServiceRegistration::operator bool() const
{
  return d_func();
}


osgi::core::ServiceRegistration& osgi::core::ServiceRegistration::operator=(int null)
{
  if (null == 0)
  {
    if (d_func() && !d_func()->ref.deref())
    {
      delete d_ptr;
    }
    d_ptr = 0;
  }
  return *this;
}



osgi::core::ServiceReference osgi::core::ServiceRegistration::getReference() const
{
  Q_D(const ServiceRegistration);

  // if (!d) throw IllegalStateException("ServiceRegistration object invalid");
  // if (!d->available) throw IllegalStateException("Service is unregistered");

  return d->reference;
}

void osgi::core::ServiceRegistration::setProperties(const osgi::Dictionary& props)
{
  Q_D(ServiceRegistration);
  // if (!d) throw IllegalStateException("ServiceRegistration object invalid");

  QMutexLocker lock(&d->eventLock);

  QSet<ServiceSlotEntry> before;
  // TBD, optimize the locking of services
  {
    QMutexLocker lock2(&d->plugin->fwCtx->globalFwLock);
    QMutexLocker lock3(&d->propsLock);

    if (d->available)
    {
      // NYI! Optimize the MODIFIED_ENDMATCH code
      int old_rank = d->properties.value(PluginConstants::SERVICE_RANKING).toInt();
      before = d->plugin->fwCtx->listeners.getMatchingServiceSlots(d->reference, false);
      QStringList classes = d->properties.value(PluginConstants::OBJECTCLASS).toStringList();
      qlonglong sid = d->properties.value(PluginConstants::SERVICE_ID).toLongLong();
      d->properties = Services::createServiceProperties(props, classes, sid);
      int new_rank = d->properties.value(PluginConstants::SERVICE_RANKING).toInt();

      if (old_rank != new_rank)
      {
        d->plugin->fwCtx->services->updateServiceRegistrationOrder(*this, classes);
      }
    }
    else
    {
      // throw IllegalStateException("Service is unregistered");
    }
  }
  d->plugin->fwCtx->listeners.serviceChanged( d->plugin->fwCtx->listeners.getMatchingServiceSlots(d->reference),
      ServiceEvent(ServiceEvent::MODIFIED, d->reference), before);

  d->plugin->fwCtx->listeners.serviceChanged( before, ServiceEvent(ServiceEvent::MODIFIED_ENDMATCH, d->reference));
}


void osgi::core::ServiceRegistration::unregister()
{
  Q_D(ServiceRegistration);
  // if (!d) throw IllegalStateException("ServiceRegistration object invalid");

  if (d->unregistering) return; // Silently ignore redundant unregistration.
  {
    QMutexLocker lock(&d->eventLock);
    if (d->unregistering) return;
    d->unregistering = true;

    if (d->available)
    {
      if (d->plugin)
      {
        d->plugin->fwCtx->services->removeServiceRegistration(*this);
      }
    }
    else
    {
      // throw IllegalStateException("Service is unregistered");
    }
  }

  if (d->plugin)
  {
     d->plugin->fwCtx->listeners.serviceChanged(
         d->plugin->fwCtx->listeners.getMatchingServiceSlots(d->reference),
         ServiceEvent(ServiceEvent::UNREGISTERING, d->reference));
  }

  {
    QMutexLocker lock(&d->eventLock);
    {
      QMutexLocker lock2(&d->propsLock);
      d->available = false;
      if (d->plugin)
      {
        for (QHashIterator<QSharedPointer<Plugin>, QObject*> i(d->serviceInstances); i.hasNext();)
        {
          QObject* obj = i.next().value();
          try
          {
            // NYI, don't call inside lock
            qobject_cast<ctkServiceFactory*>(d->service)->ungetService(i.key(), *this, obj);
          }
          // catch (const Exception& ue)
          {
            // PluginFrameworkEvent pfwEvent(PluginFrameworkEvent::PLUGIN_ERROR, d->plugin->q_func(), ue);
            // d->plugin->fwCtx->listeners.emitFrameworkEvent(pfwEvent);
          }
        }
      }
      d->plugin = 0;
      d->dependents.clear();
      d->service = 0;
      d->serviceInstances.clear();
      d->reference = 0;
      d->unregistering = false;
    }
  }
}


bool osgi::core::ServiceRegistration::operator<(const ServiceRegistration& o) const
{
  Q_D(const ServiceRegistration);
  if (!d) return true;
  return d->reference <(o.d_func()->reference);
}


bool osgi::core::ServiceRegistration::operator==(const ServiceRegistration& registration) const
{
  Q_D(const ctkServiceRegistration);
  return d == registration.d_func();
}

osgi::core::ServiceRegistration& osgi::core::ServiceRegistration::operator=(const ServiceRegistration& registration)
{
  ServiceRegistrationPrivate* curr_d = d_func();
  d_ptr = registration.d_ptr;
  if (d_ptr) d_ptr->ref.ref();

  if (curr_d && !curr_d->ref.deref())
    delete curr_d;

  return *this;
}

uint qHash(const osgi::core::ServiceRegistration& serviceReg)
{
  return qHash(serviceReg.d_func());
}

