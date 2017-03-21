#include <arkhe/osgi/core/workflow/WorkflowInterstepTransitionEvent.hpp>

osgi::core::WorkflowInterstepTransitionEvent::WorkflowInterstepTransitionEvent(int newTransitionType)
	: QEvent(QEvent::Type(getWorkflowInterstepTransitionEventType()))
	, EventTransitionType(newTransitionType)
{
				
}

osgi::core::WorkflowInterstepTransitionEvent::~WorkflowInterstepTransitionEvent()
{
	
}

osgi::core::WorkflowInterstepTransitionEvent::WorkflowInterstepTransitionEvent(int newTransitionType, const QString& newId)
	: QEvent(QEvent::Type(getWorkflowInterstepTransitionEventType()))
	, EventTransitionType(newTransitionType)
	, EventId(newId)
{
				
}

int osgi::core::WorkflowInterstepTransitionEvent::getWorkflowInterstepTransitionEventType()
{
	static int workflowInterstepTransitionEventType = QEvent::registerEventType(QEvent::User+1);
	return workflowInterstepTransitionEventType;
}
			

