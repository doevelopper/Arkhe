#ifndef ARKHE_OSGI_CORE_FRAMEWORK_PLUGINPRIVATE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_PLUGINPRIVATE_HPP

#include <QHash>
#include <QPluginLoader>
#include <QDateTime>
#include <QFileInfo>
#include <QMutex>
#include <QWaitCondition>


#include <arkhe/osgi/core/framework/Plugin>
#include <arkhe/osgi/core/framework/PluginException>
#include <arkhe/osgi/core/framework/RequirePlugin>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class PluginActivator;
		class PluginArchive;
		class PluginFrameworkContext;

		class PluginPrivate
		{

		public:
			PluginPrivate();
			PluginPrivate(QWeakPointer<ctkPlugin> qq, PluginFrameworkContext* fw,
                   QSharedPointer<PluginArchive> pa /*, Object checkContext*/);
			PluginPrivate(QWeakPointer<Plugin> qq,PluginFrameworkContext* fw, long id, const QString& loc, const QString& sym, const ctkVersion& ver);	   
			virtual ~PluginPrivate();
			
			Plugin::State getUpdatedState();
			QFileInfo getDataRoot();
			void setStateInstalled(bool sendEvent);
			void purge();
			void setAutostartSetting(const Plugin::StartOptions& setting);
			void ignoreAutostartSetting();
			void modified();
			void finalizeActivation();
			
			const RuntimeException* stop();
			const RuntimeException* stop();
			void update0(const QUrl &updateLocation, bool wasActive);
			int getStartLevel();
			void waitOnOperation(LockObject* lock, const QString& src, bool longWait);
			QStringList findResourceEntries(const QString& path, const QString& pattern, bool recurse) const;

			inline QWeakPointer<Plugin> q_func() 
			{ 
				return q_ptr; 
			}
			
			inline QWeakPointer<const Plugin> q_func() const 
			{ 
				return q_ptr; 
			}

			friend class Plugin;
			
			struct Locker
			{
					Locker(LockObject* obj) 
					: m_Obj(obj) 
					{ 
						m_Obj->lock(); 
					}
					~Locker() 
					{ 
						m_Obj->unlock(); 
					}
				private:
					LockObject* m_Obj;
			};
			
			static const Plugin::States RESOLVED_FLAGS;
			PluginFrameworkContext * const fwCtx;
			const long id;
			const QString location;
			QString symbolicName;
			Version version;
			Plugin::State state;
			QSharedPointer<PluginArchive> archive;
			QFileInfo pluginDir;
			QScopedPointer<PluginContext> pluginContext;
			PluginActivator* pluginActivator;
			QPluginLoader pluginLoader;
			QDateTime lastModified;
			QHash<QString, QString> cachedHeaders;
			QHash<QString, QString> cachedRawHeaders;
			QAtomicInt operation;
			PluginException* resolveFailException;
			bool eagerActivation;
			QList<RequirePlugin*> require;

			static const int IDLE = 0;
			static const int ACTIVATING = 1;
			static const int DEACTIVATING = 2;
			static const int RESOLVING = 3;
			static const int UNINSTALLING = 4;
			static const int UNRESOLVING = 5;
			static const int UPDATING = 6;
			LockObject operationLock;


		protected:
		
			const QWeakPointer<Plugin> q_ptr;
			class LockObject
			{
				public:

					LockObject() {};

					void lock();
					bool tryLock();
					bool tryLock(int timeout);
					void unlock();

					bool wait(unsigned long time = ULONG_MAX);
					void wakeAll();
					void wakeOne();

				private:

					Q_DISABLE_COPY(LockObject)
					QMutex m_Lock;
					QWaitCondition m_Condition;
			};

		private:
			bool wasStarted;
			void checkManifestHeaders();
			PluginException* start0();
			void startDependencies();
			void removePluginResources();
			Plugin::State getUpdatedState_unlocked();
		};		
	}
}
#endif
