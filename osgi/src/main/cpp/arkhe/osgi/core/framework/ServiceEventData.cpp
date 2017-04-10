
#include <QStringList>

#include <arkhe/osgi/core/framework/ServiceEventData.hpp>
#include <arkhe/osgi/core/framework/PluginConstants.hpp>

osgi::core::ServiceEventData::ServiceEventData()
{
}

osgi::core::ServiceEventData(ServiceEvent::Type type, const ServiceReference& reference)
	: type(type)
	, reference(reference)
{

}

osgi::core::ServiceEventData(const ServiceEventData& other)
    : QSharedData(other)
	, type(other.type)
	, reference(other.reference)
  {

  // }
  
osgi::core::ServiceEventData::~ServiceEventData()
{
}
