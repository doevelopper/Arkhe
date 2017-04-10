#include <QSharedData>
#include <cstring>

#include <arkhe/osgi/core/framework/ServiceSlotEntry.hpp>
#include <arkhe/osgi/core/framework/ServiceSlotEntryData.hpp>

osgi::core::ServiceSlotEntry::ServiceSlotEntry()
{
}

osgi::core::ServiceSlotEntry::ServiceSlotEntry(QSharedPointer<Plugin> p, QObject* receiver, const char* slot, const QString& filter)
  : d(new ServiceSlotEntryData(p, receiver, slot))
{
	if (!filter.isNull())
	{
		d->ldap = LDAPExpr(filter);
	}
}

osgi::core::ServiceSlotEntry::ServiceSlotEntry(const ServiceSlotEntry& other)
  : d(other.d)
{

}

osgi::core::ServiceSlotEntry::ServiceSlotEntry()
  : d(new ServiceSlotEntryData(QSharedPointer<Plugin>(0), 0, 0))
{

}

osgi::core::ServiceSlotEntry& osgi::core::ServiceSlotEntry::operator=(const ServiceSlotEntry& other)
{
	d = other.d;
	return *this;
}

osgi::core::ServiceSlotEntry::~ServiceSlotEntry()
{
}

bool osgi::core::ServiceSlotEntry::operator==(const ServiceSlotEntry& other) const
{
  return ((d->plugin == 0 || other.d->plugin == 0) || d->plugin == other.d->plugin) 
			&& d->receiver == other.d->receiver 
			&& ((d->slot == 0 || other.d->slot == 0)  || std::strcmp(d->slot, other.d->slot) == 0);
}

void osgi::core::ServiceSlotEntry::invokeSlot(const ServiceEvent &event)
{
	if (!QMetaObject::invokeMethod(d->receiver, d->slot, Qt::DirectConnection, Q_ARG(ServiceEvent, event)))
	{
		// throw RuntimeException(
                // QString("Slot %1 of %2 could not be invoked. A call to "
                        // "PluginContext::connectServiceListener() must only contain "
                        // "the slot name, not the whole signature.").
                // arg(d->slot).arg(d->receiver->metaObject()->className()));
	}
}

----------------------------
void osgi::core::ServiceSlotEntry::setRemoved(bool removed)
{
  d->removed = removed;
}

bool osgi::core::ServiceSlotEntry::isRemoved() const
{
	return d->removed;
}


QSharedPointer<osgi::core::Plugin> osgi::core::ServiceSlotEntry::getPlugin() const
{
	return d->plugin;
}

osgi::core::LDAPExpr osgi::core::ServiceSlotEntry::getLDAPExpr() const
{
	return d->ldap;
}

QString osgi::core::ServiceSlotEntry::getFilter() const
{
	return d->ldap.isNull() ? QString() : d->ldap.toString();
}


osgi::core::LDAPExpr::LocalCache& osgi::core::ServiceSlotEntry::getLocalCache() const
{
	return d->local_cache;
}

uint qHash(const osgi::core::ServiceSlotEntry& serviceSlot)
{
	if (serviceSlot.d->hashValue == 0)
	{
		serviceSlot.d->hashValue = qHash(serviceSlot.d->plugin) * 4 +
			qHash(serviceSlot.d->receiver) * 2 + qHash(serviceSlot.d->slot);
	}

	return serviceSlot.d->hashValue;
}


