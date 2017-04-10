#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICESLOTENTRY_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICESLOTENTRY_HPP

#include <QHash>
#include <QList>
#include <QString>
#include <QStringList>
#include <QExplicitlySharedDataPointer>

#include <arkhe/osgi/osgi.hpp>

#include <arkhe/osgi/core/framework/ServiceEvent.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class Plugin;
		class ServiceSlotEntryData;
		class QObject;

		class  ServiceSlotEntry
		{

		public:
			ServiceSlotEntry();
			ServiceSlotEntry& operator=(const ServiceSlotEntry& other);
			ServiceSlotEntry(QSharedPointer<Plugin> p, QObject* receiver, const char* slot, const QString& filter = QString());
			ServiceSlotEntry(const ServiceSlotEntry& other);
			virtual ~ServiceSlotEntry();
			
			bool operator==(const ctkServiceSlotEntry& other) const;
			void invokeSlot(const ctkServiceEvent& event);
			void setRemoved(bool removed);
			bool isRemoved() const;
			QSharedPointer<ctkPlugin> getPlugin() const;
			LDAPExpr getLDAPExpr() const;
			QString getFilter() const;
			LDAPExpr::LocalCache& getLocalCache() const;

		protected:

		private:

			friend uint qHash(const ServiceSlotEntry& serviceSlot);
			QExplicitlySharedDataPointer<ServiceSlotEntryData> d;
		};
		
		uint qHash(const osgi::core::ServiceSlotEntry& serviceSlot);
	}
}
#endif
