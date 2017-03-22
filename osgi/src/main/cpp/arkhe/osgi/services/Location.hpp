#ifndef ARKHE_OSGI_SERVICES_LOCATION_HPP
#define ARKHE_OSGI_SERVICES_LOCATION_HPP

#include <arkhe/osgi/osgi.hpp>

#include <QObject>
class QUrl;

/*!
 * @brief Rrepresents a QUrl which may have a default value, may be read only, may
 * 			or may not have a current value and may be cascaded on to a parent location.
 */
namespace osgi
{
	namespace svc
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT Location
		{

		public:
			Location();
			virtual ~Location();
			virtual bool allowsDefault() const = 0;
			virtual QUrl getDefault() const = 0;
			virtual Location* getParentLocation() const = 0;
			virtual QUrl getUrl() const = 0;
			virtual bool isSet() const = 0;
			virtual bool isReadOnly() const = 0;
			virtual bool set(const QUrl& value, bool lock) = 0;
			virtual bool set(const QUrl& value, bool lock, const QString& lockFilePath) = 0;
			virtual bool lock() = 0;
			virtual void release() = 0;
			virtual bool isLocked() const = 0;
			virtual Location* createLocation(Location* parent, const QUrl& defaultValue, bool readonly) = 0;
			virtual QUrl getDataArea(const QString& path) const = 0;
			
		protected:

		private:

			static const QString INSTANCE_FILTER;
			static const QString INSTALL_FILTER;
			static const QString CONFIGURATION_FILTER;
			static const QString USER_FILTER;
			static const QString HOME_FILTER;
		};		
	}
}
Q_DECLARE_INTERFACE(Location, "000.levitics.arkhe.service.datalocation.Location")
#endif
