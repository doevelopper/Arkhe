#include <arkhe/osgi/core/framework/ServiceSlotEntryData.hpp>

osgi::core::ServiceSlotEntryData::ServiceSlotEntryData()
{
}

osgi::core::ServiceSlotEntryData::ServiceSlotEntryData(QSharedPointer<Plugin> p, QObject* receiver, const char* slot)
	: plugin(p)
	, receiver(receiver)
	, slot(slot)
	, removed(false)
	, hashValue(0)
{
	
}

osgi::core::ServiceSlotEntryData::~ServiceSlotEntryData()
{
}
