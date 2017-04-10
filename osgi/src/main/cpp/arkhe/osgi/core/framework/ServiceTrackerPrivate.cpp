#include <arkhe/osgi/core/framework/ServiceTrackerPrivate.hpp>

template<class S, class T>
const bool osgi::core::ServiceTrackerPrivate<S,T>::DEBUG_FLAG = false;

template<class S, class T>
osgi::core::ServiceTrackerPrivate<S,T>::ServiceTrackerPrivate()
{
}


template<class S, class T>
osgi::core::ServiceTrackerPrivate<S,T>::ServiceTrackerPrivate( ServiceTracker<S,T>* st, PluginContext* context, const ServiceReference& reference, ServiceTrackerCustomizer<T>* customizer)
  : context(context)
  , customizer(customizer)
  , trackReference(reference)
  , trackedService(0)
  , cachedReference(0)
  , cachedService(0)
  , q_ptr(st)
{
	this->customizer = customizer ? customizer : q_func();
	this->listenerFilter = QString("(") + PluginConstants::SERVICE_ID +
						 "=" + reference.getProperty(PluginConstants::SERVICE_ID).toString() + ")";
	try
	{
		// this->filter = LDAPSearchFilter(listenerFilter);
	}
		// catch (const InvalidArgumentException& e)
	{
		/*
		 * we could only get this exception if the ServiceReference was
		 * invalid
		 */
		// InvalidArgumentException ia(QString("unexpected InvalidArgumentException exception: %1").arg(e.what()));
		// throw ia;
	}
}


template<class S, class T>
osgi::core::ServiceTrackerPrivate<S,T>::ServiceTrackerPrivate(ServiceTracker<S,T>* st, PluginContext* context, const QString& clazz, ServiceTrackerCustomizer<T>* customizer)
      : context(context)
	  , customizer(customizer)
	  , trackClass(clazz)
	  , trackReference(0)
	  , trackedService(0)
	  , cachedReference(0)
	  , cachedService(0)
	  , q_ptr(st)
{
	this->customizer = customizer ? customizer : q_func();
	this->listenerFilter = QString("(") + PluginConstants::OBJECTCLASS + "=" + clazz + ")";
	try
	{
		// this->filter = LDAPSearchFilter(listenerFilter);
	}
	// catch (const InvalidArgumentException& e)
	{
		/*
		 * we could only get this exception if the clazz argument was
		 * malformed
		 */
		// InvalidArgumentException ia(
			  // QString("unexpected InvalidArgumentException exception: %1").arg(e.what()));
		// throw ia;
	}
}


template<class S, class T>
osgi::core::ServiceTrackerPrivate<S,T>::ServiceTrackerPrivate(ServiceTracker<S,T>* st, PluginContext* context, const LDAPSearchFilter& filter,ServiceTrackerCustomizer<T>* customizer)
      : context(context)
	  , filter(filter)
	  , customizer(customizer)
	  , listenerFilter(filter.toString())
	  , trackReference(0)
	  , trackedService(0)
	  , cachedReference(0)
	  , cachedService(0)
	  , q_ptr(st)
{
	this->customizer = customizer ? customizer : q_func();

	if (context == 0)
	{
		// throw InvalidArgumentException("The plugin context cannot be null.");
	}
}

template<class S, class T>
osgi::core::ServiceTrackerPrivate<S,T>::~ServiceTrackerPrivate()
{

}

template<class S, class T>
QList<osgi::core::ServiceReference> osgi::core::ServiceTrackerPrivate<S,T>::getInitialReferences(const QString& className, const QString& filterString)
{
	return context->getServiceReferences(className, filterString);
}

template<class S, class T>
QList<osgi::core::ServiceReference> osgi::core::ServiceTrackerPrivate<S,T>::getServiceReferences_unlocked(TrackedService<S,T>* t) const
{
	if (t->size() == 0)
	{
		return QList<ServiceReference>();
	}
	return t->getTracked();
}

template<class S, class T>
QSharedPointer<osgi::core::TrackedService<S,T> > osgi::core::ServiceTrackerPrivate<S,T>::tracked() const
{
	return trackedService;
}

template<class S, class T>
void osgi::core::ServiceTrackerPrivate<S,T>::modified()
{
	cachedReference = 0; /* clear cached value */
	cachedService = 0; /* clear cached value */
	if (DEBUG_FLAG)
	{
		qDebug() << "ServiceTracker::modified:" << filter;
	}
}
