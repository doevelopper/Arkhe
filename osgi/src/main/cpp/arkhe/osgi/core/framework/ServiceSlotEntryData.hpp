#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICESLOTENTRYDATA_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICESLOTENTRYDATA_HPP

#include <QSharedData>
#include <cstring>

#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ServiceSlotEntryData : public QSharedData
		{

		public:
			ServiceSlotEntryData();
			virtual ~ServiceSlotEntryData();
			
			LDAPExpr::LocalCache local_cache;
			LDAPExpr ldap;
			QSharedPointer<Plugin> plugin;
			QObject* receiver;
			const char* slot;
			bool removed;
			uint hashValue;

		protected:

		private:

		};		
	}
}
#endif
