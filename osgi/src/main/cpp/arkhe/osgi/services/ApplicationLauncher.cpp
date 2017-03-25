#include <arkhe/osgi/core/framework/PluginConstants.hpp>
#include <arkhe/osgi/Services/ApplicationLauncher.hpp>



//const QString osgi::svc::ApplicationLauncher::APPLICATION_PID = osgi::core::PluginConstants::SERVICE_PID;
const QString osgi::svc::ApplicationLauncher::APPLICATION_DESCRIPTOR = "application.descriptor";
const QString osgi::svc::ApplicationLauncher::APPLICATION_STATE = "application.state";
const QString osgi::svc::ApplicationLauncher::APPLICATION_SUPPORTS_EXITVALUE = "application.supports.exitvalue";

const QString osgi::svc::ApplicationLauncher::RUNNING = "RUNNING";
const QString osgi::svc::ApplicationLauncher::STOPPING = "STOPPING";

osgi::svc::ApplicationLauncher::ApplicationLauncher()
{
}

osgi::svc::ApplicationLauncher::~ApplicationLauncher()
{
}
