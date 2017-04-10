
#include <QtGlobal>
#include <arkhe/osgi/core/framework/TrackedService.hpp>

template<class S, class T>
osgi::core::TrackedService<S,T>::TrackedService()
{
}

template<class S, class T>
osgi::core::TrackedService<S,T>::TrackedService(ServiceTracker<S,T>* serviceTracker,ServiceTrackerCustomizer<T>* customizer)
  : serviceTracker(serviceTracker)
  , customizer(customizer)
{

}

osgi::core::TrackedService<S,T>::~TrackedService()
{
}

template<class S, class T>
void osgi::core::TrackedService<S,T>::serviceChanged(const ServiceEvent& event)
{

	if (this->closed)
	{
		return;
	}

	ServiceReference reference = event.getServiceReference();

	if (serviceTracker->d_func()->DEBUG_FLAG)
	{
		qDebug() << "TrackedService::serviceChanged[" << event.getType() << "]: " << reference;
	}

	switch (event.getType())
	{
		case ServiceEvent::REGISTERED :
		case ServiceEvent::MODIFIED :
		{
			if (!serviceTracker->d_func()->listenerFilter.isNull())
			{ 
				this->track(reference, event);
			}
			else
			{ 
				if (serviceTracker->d_func()->filter.match(reference))
				{
					this->track(reference, event);
				}
				else
				{
					this->untrack(reference, event);
				}
			}
			break;
		}
		case ServiceEvent::MODIFIED_ENDMATCH :
		case ServiceEvent::UNREGISTERING :
			this->untrack(reference, event);

		break;
	}
}

template<class S, class T>
void osgi::core::TrackedService<S,T>::modified()
{
	Superclass::modified(); /* increment the modification count */
	serviceTracker->d_func()->modified();
}


template<class S, class T>
T osgi::core::TrackedService<S,T>::customizerAdding(ServiceReference item, const ServiceEvent& related)
{
	Q_UNUSED(related)
	return customizer->addingService(item);
}

template<class S, class T>
void osgi::core::TrackedService<S,T>::customizerModified(ServiceReference item, const ServiceEvent& related, T object)
{
	Q_UNUSED(related)
	customizer->modifiedService(item, object);
}

template<class S, class T>
void osgi::core::TrackedService<S,T>::customizerRemoved(ServiceReference item, const ServiceEvent& related, T object)
{
	Q_UNUSED(related)
	customizer->removedService(item, object);
}

