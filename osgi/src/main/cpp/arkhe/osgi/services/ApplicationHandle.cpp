#include <arkhe/osgi/core/framework/PluginConstants.hpp>
#include <arkhe/osgi/Services/ApplicationHandle.hpp>

//const QString osgi::svc::ApplicationHandle::APPLICATION_PID = osgi::core::PluginConstants::SERVICE_PID;
const QString osgi::svc::ApplicationHandle::APPLICATION_DESCRIPTOR = "application.descriptor";
const QString osgi::svc::ApplicationHandle::APPLICATION_STATE = "application.state";
const QString osgi::svc::ApplicationHandle::APPLICATION_SUPPORTS_EXITVALUE = "application.supports.exitvalue";

const QString osgi::svc::ApplicationHandle::RUNNING = "RUNNING";
const QString osgi::svc::ApplicationHandle::STOPPING = "STOPPING";

osgi::svc::ApplicationHandle::ApplicationHandle()
{
}

osgi::svc::ApplicationHandle::~ApplicationHandle()
{
}
