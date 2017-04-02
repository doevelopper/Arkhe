#include <arkhe/osgi/core/workflow/WorkflowInterstepTransition.hpp>

osgi::core::WorkflowInterstepTransition::WorkflowInterstepTransition()
{
	
}

osgi::core::WorkflowInterstepTransition::~WorkflowInterstepTransition()
{
	
}

osgi::core::WorkflowInterstepTransition::WorkflowInterstepTransition(InterstepTransitionType newTransitionType)
: TransitionType(newTransitionType)
{
	
}

osgi::core::WorkflowInterstepTransition::WorkflowInterstepTransition(InterstepTransitionType newTransitionType, const QString& newId)
: TransitionType(newTransitionType)
, Id(newId) 
{
	
}

osgi::core::WorkflowInterstepTransition::InterstepTransitionType osgi::core::WorkflowInterstepTransition::transitionType() 
{
	return this->TransitionType;
}
	
QString& osgi::core::WorkflowInterstepTransition::id() 
{
	return this->Id;
}

bool osgi::core::WorkflowInterstepTransition::eventTest(QEvent* e)
{
			////check the event type
	// if (e->type() != WorkflowInterstepTransitionEvent::getWorkflowInterstepTransitionEventType())
	{
		return false;
	}
			////check the event value (i.e. the TransitionType)
	// WorkflowInterstepTransitionEvent* workflowEvent = static_cast<WorkflowInterstepTransitionEvent*>(e);
	// return (this->TransitionType == workflowEvent->EventTransitionType && this->Id == workflowEvent->EventId); 
}

void osgi::core::WorkflowInterstepTransition::onTransition(QEvent*)
{
	
}