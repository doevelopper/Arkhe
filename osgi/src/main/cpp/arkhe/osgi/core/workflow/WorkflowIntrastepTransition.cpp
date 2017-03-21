#include <arkhe/osgi/core/workflow/WorkflowIntrastepTransition.hpp>
#include <arkhe/osgi/core/workflow/WorkflowIntrastepTransitionEvent.hpp>

// osgi::core::WorkflowIntrastepTransition::WorkflowIntrastepTransition()
// {
	
// }

osgi::core::WorkflowIntrastepTransition::~WorkflowIntrastepTransition()
{
	
}

osgi::core::WorkflowIntrastepTransition::WorkflowIntrastepTransition(osgi::core::WorkflowIntrastepTransition::IntrastepTransitionType newTransitionType)
    : TransitionType(newTransitionType)
{
	
}

osgi::core::WorkflowIntrastepTransition::IntrastepTransitionType osgi::core::WorkflowIntrastepTransition::transitionType()
{
	return this->TransitionType;
}

bool osgi::core::WorkflowIntrastepTransition::eventTest(QEvent* e)
{
    // check the event type
    // if (e->type() != osgi::core::WorkflowIntrastepTransitionEvent::getWorkflowIntrastepTransitionEventType())
	{
		return false;
	}

    // check the event value (i.e. the TransitionType)
    // WorkflowIntrastepTransitionEvent* workflowEvent = static_cast<WorkflowIntrastepTransitionEvent*>(e);

    // return (this->TransitionType == workflowEvent->EventTransitionType);	
}

void osgi::core::WorkflowIntrastepTransition::onTransition(QEvent*)
{
	
}
