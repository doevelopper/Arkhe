#include <arkhe/osgi/core/workflow/WorkflowIntrastepTransitionEvent.hpp>

osgi::core::WorkflowIntrastepTransitionEvent::WorkflowIntrastepTransitionEvent(int newTransitionType)
    : QEvent(QEvent::Type(getWorkflowIntrastepTransitionEventType()))
	, EventTransitionType(newTransitionType)
{
	
}

int osgi::core::WorkflowIntrastepTransitionEvent::getWorkflowIntrastepTransitionEventType()
{
	static int workflowIntrastepTransitionEventType = QEvent::registerEventType(QEvent::User+1);
	return workflowIntrastepTransitionEventType;
}