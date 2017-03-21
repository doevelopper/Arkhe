# add_subdirectory (arkhe/osgi/core/workflow)

include_directories(.)
# Work arorund for  #include <bfd.h> on windows
include_directories(D:/Qt/Qt5.8.0/Tools/mingw530_32/include
)
add_library(${PROJECT_NAME}-osgi
	arkhe/osgi/osgi.cpp
	arkhe/osgi/core/BackTrace.cpp
	arkhe/osgi/core/logger/LoggingCategory.cpp
	arkhe/osgi/core/AbstractFactoryItem.cpp
	arkhe/osgi/core/AbstractFactory.cpp
	arkhe/osgi/core/AbstractFactoryFileBasedItem.cpp
	arkhe/osgi/core/AbstractFileBasedFactory.cpp
	arkhe/osgi/core/AbstractLibraryFactory.cpp
	arkhe/osgi/core/FactoryLibraryItem.cpp
	arkhe/osgi/core/AbstractObjectFactory.cpp
	arkhe/osgi/core/FactoryObjectItem.cpp
	arkhe/osgi/core/AbstractPluginFactory.cpp
	arkhe/osgi/core/FactoryPluginItem.cpp
	arkhe/osgi/core/ScopedCurrentDir.cpp
	arkhe/osgi/core/AbstractQObjectFactory.cpp
	arkhe/osgi/core/BinaryFileDescriptor.cpp
	arkhe/osgi/core/BooleanMapper.cpp
	arkhe/osgi/core/CommandLineParser.cpp
	arkhe/osgi/core/Exception.cpp
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
	
)

target_link_libraries( ${PROJECT_NAME}-osgi Qt5::Widgets )