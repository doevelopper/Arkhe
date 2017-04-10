#include <QObject>
#include <QMutexLocker>

#include <arkhe/osgi/core/framework/ServiceReferencePrivate.hpp>
#include <arkhe/osgi/core/framework/Plugin.hpp>
#include <arkhe/osgi/core/framework/PluginConstants.hpp>
#include <arkhe/osgi/core/framework/ServiceFactory.hpp>
#include <arkhe/osgi/core/framework/ServiceException.hpp>
#include <arkhe/osgi/core/framework/Services.hpp>
#include <arkhe/osgi/core/framework/ServiceRegistration.hpp>


osgi::core::ServiceReferencePrivate::ServiceReferencePrivate()
{
}

osgi::core::ServiceReferencePrivate::ServiceReferencePrivate(ServiceRegistrationPrivate* reg)
  : ref(1)
  , registration(reg)
{
	if (registration) registration->ref.ref();
}

osgi::core::ServiceReferencePrivate::~ServiceReferencePrivate()
{
	if (registration && !registration->ref.deref())
	{
		delete registration;
	}
}


QObject* osgi::core::ServiceReferencePrivate::getService(QSharedPointer<Plugin> plugin)
{
	QObject* s = 0;
	{
		QMutexLocker lock(&registration->propsLock);

		if (registration->available)
		{
			int count = registration->dependents.value(plugin);

			if (count == 0)
			{
				QStringList classes = registration->properties.value(PluginConstants::OBJECTCLASS).toStringList();
				registration->dependents[plugin] = 1;

				if (ServiceFactory* serviceFactory = qobject_cast<ServiceFactory*>(registration->getService()))
				{
					try
					{
						s = serviceFactory->getService(plugin, ServiceRegistration(registration));
					}
					catch (const Exception& pe)
					{
						ServiceException se("ServiceFactory throw an exception",
                                   ServiceException::FACTORY_EXCEPTION, pe);
						plugin->d_func()->fwCtx->listeners.frameworkError(registration->plugin->q_func(), se);
						return 0;
					}

					if (s == 0)
					{
						ServiceException se("ServiceFactory produced null",
                                   ServiceException::FACTORY_ERROR);
						plugin->d_func()->fwCtx->listeners.frameworkError(registration->plugin->q_func(), se);
						return 0;
					}

					for (QStringListIterator i(classes); i.hasNext(); )
					{
						QString cls = i.next();

						if (!registration->plugin->fwCtx->services->checkServiceClass(s, cls))
						{
							ServiceException se(QString("ServiceFactory produced an object ") +
                                     "that did not implement: " + cls,
                                     ServiceException::FACTORY_ERROR);
							plugin->d_func()->fwCtx->listeners.frameworkError(registration->plugin->q_func(), se);
							return 0;
						}
					}

					registration->serviceInstances.insert(plugin, s);
				}
				else
				{
					s = registration->getService();
				}
			}
			else
			{
				registration->dependents.insert(plugin, count + 1);

				if (qobject_cast<ServiceFactory*>(registration->getService()))
				{
					s = registration->serviceInstances.value(plugin);
				}
				else
				{
					s = registration->getService();
				}
			}
		}
	}
	return s;
}


bool osgi::core::ServiceReferencePrivate::ungetService(QSharedPointer<Plugin> plugin, bool checkRefCounter)
{
	QMutexLocker lock(&registration->propsLock);
	bool hadReferences = false;
	bool removeService = false;

	int count= registration->dependents.value(plugin);
	if (count > 0)
	{
		hadReferences = true;
	}

	if(checkRefCounter)
	{
		if (count > 1)
		{
			registration->dependents[plugin] = count - 1;
		}
		else if(count == 1)
		{
			removeService = true;
		}
	}
	else
	{
		removeService = true;
	}

	if (removeService)
	{
		QObject* sfi = registration->serviceInstances[plugin];
		registration->serviceInstances.remove(plugin);

		if (sfi != 0)
		{
			try
			{
				qobject_cast<ServiceFactory*>( registration->getService())->ungetService(plugin, ServiceRegistration(registration), sfi);
			}
			catch (const Exception& e)
			{
				plugin->d_func()->fwCtx->listeners.frameworkError(registration->plugin->q_func(), e);
			}
		}

		registration->dependents.remove(plugin);
	}

	return hadReferences;
}


const osgi::core::ServiceProperties& osgi::core::ServiceReferencePrivate::getProperties() const
{
	return registration->properties;
}


QVariant osgi::core::ServiceReferencePrivate::getProperty(const QString& key, bool lock) const
{
	if (lock)
	{
		QMutexLocker lock(&registration->propsLock);
		return registration->properties.value(key);
	}

	return registration->properties.value(key);
}
