#include <arkhe/osgi/core/framework/ServiceTracker.hpp>


#include <QVarLengthArray>
#include <QDebug>

#include <stdexcept>
#include <limits>

//----------------------------------------------------------------------------
template<class S, class T>
osgi::core::ServiceTracker<S,T>::~ServiceTracker()
{
}


template<class S, class T>
osgi::core::ServiceTracker<S,T>::ServiceTracker(PluginContext* context,
                                          const ServiceReference& reference,
                                          _ServiceTrackerCustomizer* customizer)
  : d_ptr(new _ServiceTrackerPrivate(this, context, reference, customizer))
{
}


template<class S, class T>
osgi::core::ServiceTracker<S,T>::ServiceTracker(PluginContext* context, const QString& clazz,
                                          _ServiceTrackerCustomizer* customizer)
  : d_ptr(new _ServiceTrackerPrivate(this, context, clazz, customizer))
{
}


template<class S, class T>
osgi::core::ServiceTracker<S,T>::ServiceTracker(PluginContext* context, const LDAPSearchFilter& filter,
                                          _ServiceTrackerCustomizer* customizer)
  : d_ptr(new _ServiceTrackerPrivate(this, context, filter, customizer))
{
}

template<class S, class T>
osgi::core::ServiceTracker<S,T>::ServiceTracker(PluginContext *context, _ServiceTrackerCustomizer<T> *customizer)
  : d_ptr(new _ServiceTrackerPrivate(this, context, qobject_interface_iid<S>(), customizer))
{
	const char* clazz = qobject_interface_iid<S>();
	if (clazz == 0) 
		// throw ServiceException("The service interface class has no Q_DECLARE_INTERFACE macro");
}


template<class S, class T>
void osgi::core::ServiceTracker<S,T>::open()
{
	Q_D(_ServiceTracker);
	QSharedPointer<_TrackedService> t;
	{
		QMutexLocker lock(&d->mutex);
		if (d->trackedService)
		{
			return;
		}

		if (d->DEBUG_FLAG)
		{
			qDebug() << "ServiceTracker<S,T>::open: " << d->filter;
		}

		t = QSharedPointer<_TrackedService>( new _TrackedService(this, d->customizer));
		{
			QMutexLocker lockT(t.data());

			try 
			{
				d->context->connectServiceListener(t.data(), "serviceChanged", d->listenerFilter);

				QList<ServiceReference> references;
				if (!d->trackClass.isEmpty())
				{
					references = d->getInitialReferences(d->trackClass, QString());
				}
				else
				{
					if (!d->trackReference.getPlugin().isNull())
					{
						references.push_back(d->trackReference);
					}
					else
					{ /* user supplied filter */
						references = d->getInitialReferences(QString(), (d->listenerFilter.isNull()) ? d->filter.toString() : d->listenerFilter);
					}
				}
				/* set tracked with the initial references */
				t->setInitial(references);
			}
			// catch (const InvalidArgumentException& e)
			{
				// throw RuntimeException(QString("unexpected InvalidArgumentException exception: %1").arg(e.what()));
			}
		}

		d->trackedService = t;
	}
	/* Call tracked outside of synchronized region */
	t->trackInitial(); /* process the initial references */
}


template<class S, class T>
void osgi::core::ServiceTracker<S,T>::close()
{
	Q_D(_ServiceTracker);
	QSharedPointer<_TrackedService> outgoing;
	QList<ServiceReference> references;
	
	{
		QMutexLocker lock(&d->mutex);
		outgoing = d->trackedService;
		
		if (outgoing.isNull())
		{
			return;
		}
		
		if (d->DEBUG_FLAG)
		{
			qDebug() << "ServiceTracker<S,T>::close:" << d->filter;
		}

		outgoing->close();
		references = getServiceReferences();
		d->trackedService.clear();;

		try
		{
			d->context->disconnectServiceListener(outgoing.data(), "serviceChanged");
		}
		catch (const IllegalStateException& /*e*/)
		{
		/* In case the context was stopped. */
		}
	}

	d->modified(); /* clear the cache */

	{
		QMutexLocker lockT(outgoing.data());
		outgoing->wakeAll(); /* wake up any waiters */
	}
  
	foreach (ServiceReference ref, references)
	{
		outgoing->untrack(ref, ServiceEvent());
	}

	if (d->DEBUG_FLAG)
	{
		QMutexLocker lock(&d->mutex);

		if ((d->cachedReference.getPlugin().isNull()) && (d->cachedService == 0))
		{
			qDebug() << "ServiceTracker<S,T>::close[cached cleared]:"
				<< d->filter;
		}
	}
}

template<class S, class T>
T osgi::core::ServiceTracker<S,T>::waitForService(unsigned long timeout)
{
	Q_D(_ServiceTracker);
	
	T object = getService();

	while (object == 0)
	{
		QSharedPointer<_TrackedService> t = d->tracked();
	
		if (t.isNull())
		{ /* if ServiceTracker is not open */
			return 0;
		}

		{
			QMutexLocker lockT(t.data());

			if (t->size() == 0)
			{
				t->wait(timeout);
			}
		}
		object = getService();

		if (timeout > 0)
		{
			return object;
		}
	}
	return object;
}


template<class S, class T>
QList<osgi::core::ServiceReference> osgi::core::ServiceTracker<S,T>::getServiceReferences() const
{
	Q_D(const _ServiceTracker);
	QSharedPointer<_TrackedService> t = d->tracked();
	if (t.isNull())
	{ /* if ServiceTracker is not open */
		return QList<ServiceReference>();
	}
	
	{
		QMutexLocker lockT(t.data());
		return d->getServiceReferences_unlocked(t.data());
	}
}

template<class S, class T>
osgi::core::ServiceReference osgi::core::ServiceTracker<S,T>::getServiceReference() const
{
	Q_D(const _ServiceTracker);
	ServiceReference reference(0);
	{
		QMutexLocker lock(&d->mutex);
		reference = d->cachedReference;
	}
	if (!reference.getPlugin().isNull())
	{
		if (d->DEBUG_FLAG)
		{
			qDebug() << "ServiceTracker<S,T>::getServiceReference[cached]:"
                   << d->filter;
		}
		return reference;
	}
	if (d->DEBUG_FLAG)
	{
		qDebug() << "ServiceTracker<S,T>::getServiceReference:" << d->filter;
	}

	QList<ServiceReference> references = getServiceReferences();

	int length = references.size();

	if (length == 0)
	{ /* if no service is being tracked */
		// throw ServiceException("No service is being tracked");
	}

	int index = 0;

	if (length > 1)
	{ /* if more than one service, select highest ranking */
		QVarLengthArray<int, 10> rankings(length);
		int count = 0;
		int maxRanking = std::numeric_limits<int>::min();

		for (int i = 0; i < length; i++)
		{
			bool ok = false;
			int ranking = references[i].getProperty(PluginConstants::SERVICE_RANKING).toInt(&ok);

			if (!ok) ranking = 0;

			rankings[i] = ranking;

			if (ranking > maxRanking)
			{
				index = i;
				maxRanking = ranking;
				count = 1;
			}
			else
			{
				if (ranking == maxRanking)
				{
					count++;
				}
			}
		}
		if (count > 1)
		{ /* if still more than one service, select lowest id */
			qlonglong minId = std::numeric_limits<qlonglong>::max();

			for (int i = 0; i < length; i++)
			{
				if (rankings[i] == maxRanking)
				{
					qlonglong id = references[i].getProperty(PluginConstants::SERVICE_ID).toLongLong();
					
					if (id < minId)
					{
						index = i;
						minId = id;
					}
				}
			}
		}
	}

	{
		QMutexLocker lock(&d->mutex);
		d->cachedReference = references[index];
		return d->cachedReference;
	}
}

template<class S, class T>
T osgi::core::ServiceTracker<S,T>::getService(const ServiceReference& reference) const
{
	Q_D(const _ServiceTracker);
	QSharedPointer<_TrackedService> t = d->tracked();
	if (t.isNull())
	{ /* if ServiceTracker is not open */
		return 0;
	}
	{
		QMutexLocker lockT(t.data());
		return t->getCustomizedObject(reference);
	}
}

template<class S, class T>
QList<T> osgi::core::ServiceTracker<S,T>::getServices() const
{
	Q_D(const _ServiceTracker);
	QSharedPointer<_TrackedService> t = d->tracked();
	if (t.isNull())
	{ /* if ServiceTracker is not open */
		return QList<T>();
	}
	{
		QMutexLocker lockT(t.data());
		QList<ServiceReference> references = d->getServiceReferences_unlocked(t.data());
		QList<T> objects;
		foreach (ServiceReference ref, references)
		{
			//objects << getService(ref);
			objects << t->getCustomizedObject(ref);
		}
		return objects;
	}
}

template<class S, class T>
T osgi::core::ServiceTracker<S,T>::getService() const
{
	Q_D(const _ServiceTracker);
	T service = d->cachedService;
	if (service != 0)
	{
		if (d->DEBUG_FLAG)
		{
		qDebug() << "ServiceTracker<S,T>::getService[cached]:"
               << d->filter;
		}
		return service;
	}
	if (d->DEBUG_FLAG)
	{
		qDebug() << "ServiceTracker<S,T>::getService:" << d->filter;
	}

	try
	{
		ServiceReference reference = getServiceReference();
		if (reference.getPlugin().isNull())
		{
			return 0;
		}
		return d->cachedService = getService(reference);
	}
	catch (const ServiceException&)
	{
		return 0;
	}
}


template<class S, class T>
void osgi::core::ServiceTracker<S,T>::remove(const ServiceReference& reference)
{
	Q_D(_ServiceTracker);
	QSharedPointer<_TrackedService> t = d->tracked();
	if (t.isNull())
	{ /* if ServiceTracker is not open */
		return;
	}
	t->untrack(reference, ServiceEvent());
}

template<class S, class T>
int osgi::core::ServiceTracker<S,T>::size() const
{
	Q_D(const _ServiceTracker);
	QSharedPointer<_TrackedService> t = d->tracked();
	
	if (t.isNull())
	{ /* if ServiceTracker is not open */
		return 0;
	}
	{
		QMutexLocker lockT(t.data());
		return t->size();
	}
}

//----------------------------------------------------------------------------
template<class S, class T>
int osgi::core::ServiceTracker<S,T>::getTrackingCount() const
{
	Q_D(const _ServiceTracker);
	QSharedPointer<_TrackedService> t = d->tracked();
	if (t.isNull())
	{ /* if ServiceTracker is not open */
		return -1;
	}
	{
		QMutexLocker lockT(t.data());
		return t->getTrackingCount();
	}
}


template<class S, class T>
QMap<osgi::core::ServiceReference, T> osgi::core::ServiceTracker<S,T>::getTracked() const
{
	QMap<ServiceReference, T> map;
	Q_D(const _ServiceTracker);
	QSharedPointer<_TrackedService> t = d->tracked();
  
	if (t.isNull())
	{ /* if ServiceTracker is not open */
		return map;
	}
	{
		QMutexLocker lockT(t.data());
		return t->copyEntries(map);
	}
}

template<class S, class T>
bool osgi::core::ServiceTracker<S,T>::isEmpty() const
{
	Q_D(const ServiceTracker);
	QSharedPointer<TrackedService> t = d->tracked();

	if (t.isNull())
	{ /* if ServiceTracker is not open */
		return true;
	}
	{
		QMutexLocker lockT(t.data());
		return t->isEmpty();
	}
}

template<class S, class T>
T osgi::core::ServiceTracker<S,T>::addingService(const ServiceReference& reference)
{
	Q_D(ServiceTracker);
	return qobject_cast<T>(d->context->getService(reference));
}

template<class S, class T>
void osgi::core::ServiceTracker<S,T>::modifiedService(const ServiceReference& reference, T service)
{
  Q_UNUSED(reference)
  Q_UNUSED(service)
  
  /* do nothing */
}


template<class S, class T>
void osgi::core::ServiceTracker<S,T>::removedService(const ServiceReference& reference, T service)
{
	Q_UNUSED(service)
	Q_D(ServiceTracker);
	d->context->ungetService(reference);
}
