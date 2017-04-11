# add_subdirectory (arkhe/osgi/core/workflow)

include_directories(.)
# Work arorund for  #include <bfd.h> on windows
include_directories(D:/Qt/Qt5.8.0/Tools/mingw530_32/include
)
add_library(${PROJECT_NAME}-osgi
	arkhe/osgi/osgi.cpp
	arkhe/osgi/core/BackTrace.cpp
	arkhe/osgi/core/CrashHandler.cpp
	# arkhe/osgi/core/BacktraceCollectorPrivate.cpp
	# arkhe/osgi/core/BacktraceCollector.cpp
	# arkhe/osgi/core/Reports.cpp
	arkhe/osgi/core/logger/LoggingCategory.cpp
	arkhe/osgi/core/AbstractFactoryItem.cpp
	arkhe/osgi/core/AbstractFactory.cpp
	arkhe/osgi/core/AbstractFactoryFileBasedItem.cpp
	arkhe/osgi/core/AbstractFileBasedFactory.cpp
	arkhe/osgi/core/AbstractLibraryFactory.cpp
	arkhe/osgi/core/AbstractObjectFactory.cpp
	arkhe/osgi/core/FactoryLibraryItem.cpp
	arkhe/osgi/core/FactoryObjectItem.cpp
	arkhe/osgi/core/AbstractPluginFactory.cpp
	arkhe/osgi/core/FactoryPluginItem.cpp
	arkhe/osgi/core/ScopedCurrentDir.cpp
	arkhe/osgi/core/AbstractQObjectFactory.cpp
	arkhe/osgi/core/BinaryFileDescriptor.cpp
	arkhe/osgi/core/BooleanMapper.cpp
	arkhe/osgi/core/CommandLineParser.cpp
	arkhe/osgi/core/Exception.cpp
	arkhe/osgi/core/Callback.cpp
	arkhe/osgi/core/HighPrecisionTimer.cpp
	arkhe/osgi/core/Logger.cpp
	arkhe/osgi/core/Singleton.cpp
	arkhe/osgi/core/ValueProxy.cpp


	arkhe/osgi/core/workflow/WorkflowIntrastepTransition.cpp
	arkhe/osgi/core/workflow/WorkflowInterstepTransitionEvent.cpp
	arkhe/osgi/core/workflow/WorkflowInterstepTransition.cpp
	arkhe/osgi/core/workflow/WorkflowIntrastepTransitionEvent.cpp
	arkhe/osgi/core/workflow/Workflow.cpp
	arkhe/osgi/core/workflow/WorkflowPrivate.cpp
	arkhe/osgi/core/workflow/WorkflowStep.cpp
	arkhe/osgi/core/workflow/ForwardAndBackwardSteps.cpp
	arkhe/osgi/core/workflow/WorkflowStepPrivate.cpp


	arkhe/osgi/services/Location.cpp
	arkhe/osgi/services/ApplicationHandle.cpp
	arkhe/osgi/services/AttributeDefinition.cpp
	arkhe/osgi/services/MetaTypeProvider.cpp
	arkhe/osgi/services/MetaTypeService.cpp
	arkhe/osgi/services/ObjectClassDefinition.cpp
	arkhe/osgi/services/Event.cpp 
	arkhe/osgi/services/EventAdmin.cpp
	arkhe/osgi/services/EventConstants.cpp
	arkhe/osgi/services/EventHandler.cpp
	arkhe/osgi/services/Configuration.cpp
	arkhe/osgi/services/ConfigurationAdmin.cpp
	arkhe/osgi/services/ConfigurationException.cpp
	arkhe/osgi/services/ConfigurationListener.cpp
	arkhe/osgi/services/ConfigurationPlugin.cpp
	arkhe/osgi/services/ManagedService.cpp
	arkhe/osgi/services/ManagedServiceFactory.cpp

	arkhe/osgi/core/framework/Runnable.cpp
	arkhe/osgi/core/framework/DefaultApplicationLauncher.cpp
	arkhe/osgi/core/framework/BasicLocation.cpp
	arkhe/osgi/core/framework/Version.cpp
	arkhe/osgi/core/framework/VersionRange.cpp
	arkhe/osgi/core/framework/PluginConstants.cpp
	arkhe/osgi/core/framework/Plugin.cpp
	arkhe/osgi/core/framework/Plugins.cpp
	arkhe/osgi/core/framework/PluginLocalizationData.cpp
	arkhe/osgi/core/framework/VersionRange.cpp
	arkhe/osgi/core/framework/LocationManager.cpp
	arkhe/osgi/core/framework/PluginPrivate.cpp
	arkhe/osgi/core/framework/PluginAbstractTracked.cpp
	arkhe/osgi/core/framework/PluginArchive.cpp
	arkhe/osgi/core/framework/PluginActivator.cpp
	arkhe/osgi/core/framework/PluginArchiveSQL.cpp
	arkhe/osgi/core/framework/PluginContext.cpp
	arkhe/osgi/core/framework/PluginContextPrivate.cpp
	arkhe/osgi/core/framework/PluginEvent.cpp
	arkhe/osgi/core/framework/PluginException.cpp
	arkhe/osgi/core/framework/PluginFramework.cpp
	arkhe/osgi/core/framework/PluginFrameworkContext.cpp
	arkhe/osgi/core/framework/PluginFrameworkDebug.cpp
	arkhe/osgi/core/framework/PluginFrameworkEvent.cpp
	arkhe/osgi/core/framework/PluginFrameworkFactory.cpp
	arkhe/osgi/core/framework/PluginFrameworkListeners.cpp
	arkhe/osgi/core/framework/PluginFrameworkProperties.cpp
	arkhe/osgi/core/framework/PluginFrameworkUtil.cpp
	arkhe/osgi/core/framework/PluginLocalization.cpp
	arkhe/osgi/core/framework/PluginStorage.cpp
	arkhe/osgi/core/framework/PluginTracker.cpp
	arkhe/osgi/core/framework/PluginTrackerPrivate.cpp
	arkhe/osgi/core/framework/PluginTrackerCustomizer.cpp
	arkhe/osgi/core/framework/RequirePlugin.cpp
	arkhe/osgi/core/framework/ServiceEvent.cpp
	arkhe/osgi/core/framework/ServiceEventData.cpp
	arkhe/osgi/core/framework/ServiceProperties.cpp
	arkhe/osgi/core/framework/ServiceException.cpp
	arkhe/osgi/core/framework/ServiceReference.cpp
	arkhe/osgi/core/framework/ServiceRegistration.cpp
	arkhe/osgi/core/framework/ServiceRegistrationPrivate.cpp
	arkhe/osgi/core/framework/ServiceFactory.cpp
	arkhe/osgi/core/framework/Services.cpp
	arkhe/osgi/core/framework/ServiceSlotEntry.cpp
	arkhe/osgi/core/framework/ServiceTracker.cpp
	arkhe/osgi/core/framework/TrackedService.cpp
	arkhe/osgi/core/framework/TrackedPluginListener.cpp
	arkhe/osgi/core/framework/TrackedPlugin.cpp
	arkhe/osgi/core/framework/ServiceTrackerPrivate.cpp
	arkhe/osgi/core/framework/TrackedServiceListener.cpp
	
	arkhe/osgi/Services/log/LogService.cpp
	arkhe/osgi/Services/log/LogEntry.cpp
	arkhe/osgi/Services/log/LogReaderService.cpp
	
	
	arkhe/osgi/cli/CmdLineModuleBackend.cpp
	arkhe/osgi/cli/CmdLineModuleCache.cpp
	arkhe/osgi/cli/CmdLineModuleCachePrivate.cpp
	arkhe/osgi/cli/CmdLineModuleConcurrentRegister.cpp
	arkhe/osgi/cli/CmdLineModuleConcurrentUnRegister.cpp
	arkhe/osgi/cli/CmdLineModuleDefaultPathBuilder.cpp
	arkhe/osgi/cli/CmdLineModuleDefaultPathBuilderPrivate.cpp
	arkhe/osgi/cli/CmdLineModuleDescription.cpp
	arkhe/osgi/cli/CmdLineModuleDescriptionPrivate.cpp
	arkhe/osgi/cli/CmdLineModuleDirectoryWatcher.cpp
	arkhe/osgi/cli/CmdLineModuleDirectoryWatcherPrivate.cpp
	arkhe/osgi/cli/CmdLineModuleEnumerationParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleFileParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleFrontend.cpp
	arkhe/osgi/cli/CmdLineModuleFrontendFactory.cpp
	arkhe/osgi/cli/CmdLineModuleFuture.cpp
	arkhe/osgi/cli/CmdLineModuleFutureCallOutEvent.cpp
	arkhe/osgi/cli/CmdLineModuleFutureCallOutInterface.cpp
	arkhe/osgi/cli/CmdLineModuleFutureInterface.cpp
	arkhe/osgi/cli/CmdLineModuleFutureInterfacePrivate.cpp
	arkhe/osgi/cli/CmdLineModuleFutureWatcher.cpp
	arkhe/osgi/cli/CmdLineModuleGeometryParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleImageParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleManager.cpp
	arkhe/osgi/cli/CmdLineModuleMultipleParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleParameter.cpp
	arkhe/osgi/cli/CmdLineModuleParameterGroup.cpp
	arkhe/osgi/cli/CmdLineModuleParameterGroupPrivate.cpp
	arkhe/osgi/cli/CmdLineModuleParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleParameterPrivate.cpp
	arkhe/osgi/cli/CmdLineModulePathBuilder.cpp
	arkhe/osgi/cli/CmdLineModulePointParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleReference.cpp
	arkhe/osgi/cli/CmdLineModuleReferencePrivate.cpp
	arkhe/osgi/cli/CmdLineModuleReferenceResult.cpp
	arkhe/osgi/cli/CmdLineModuleResult.cpp
	arkhe/osgi/cli/CmdLineModuleRunException.cpp
	arkhe/osgi/cli/CmdLineModuleScalarParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleScalarVectorParameterParser.cpp
	arkhe/osgi/cli/CmdLineModuleTimeoutException.cpp
	arkhe/osgi/cli/CmdLineModuleUtils.cpp
	arkhe/osgi/cli/CmdLineModuleXmlException.cpp
	arkhe/osgi/cli/CmdLineModuleXmlMsgHandler.cpp
	arkhe/osgi/cli/CmdLineModuleXmlParser.cpp
	arkhe/osgi/cli/CmdLineModuleXmlValidator.cpp
	arkhe/osgi/cli/CmdLineModuleXmlValidatorPrivate.cpp
	arkhe/osgi/cli/CmdLineModuleXslTransform.cpp
	arkhe/osgi/cli/CmdLineModuleXmlProgressWatcherPrivate.cpp

)

target_link_libraries( ${PROJECT_NAME}-osgi Qt5::Core )