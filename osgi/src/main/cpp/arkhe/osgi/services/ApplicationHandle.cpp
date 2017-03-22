#include <ctkPluginConstants.h>
#include <arkhe/osgi/Services/Location.hpp>


const QString osgi::svc::ApplicationHandle::APPLICATION_PID = ctkPluginConstants::SERVICE_PID;
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
