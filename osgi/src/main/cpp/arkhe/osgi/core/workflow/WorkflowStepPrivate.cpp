#include <QMetaEnum>
#include <arkhe/osgi/core/workflow/WorkflowStepPrivate.hpp>
#include <arkhe/osgi/core/workflow/WorkflowStep.hpp>
#include <arkhe/osgi/core/workflow/Workflow.hpp>

osgi::core::WorkflowStepPrivate::WorkflowStepPrivate(WorkflowStep& object)
  :q_ptr(&object)
{
	qRegisterMetaType<WorkflowStep*>("WorkflowStep*");
	this->_Workflow = 0;

	this->WidgetType = false;

	this->HasValidateCommand = false;
	this->HasOnEntryCommand = false;
	this->HasOnExitCommand = false;

	// Create state
	this->ProcessingState = new QState();
	this->ValidationState = new QState();

	// Create 'validation' transition
	this->ValidationTransition = new WorkflowIntrastepTransition(WorkflowIntrastepTransition::ValidationTransition);
	this->ValidationTransition->setTargetState(this->ValidationState);
	this->ProcessingState->addTransition(this->ValidationTransition);

	  // Create 'failed validation' transation
	this->ValidationFailedTransition = 0;
	this->ValidationFailedTransition = new WorkflowIntrastepTransition(WorkflowIntrastepTransition::ValidationFailedTransition);
	this->ValidationFailedTransition->setTargetState(this->ProcessingState);
	this->ValidationState->addTransition(this->ValidationFailedTransition);
}

osgi::core::WorkflowStepPrivate::~WorkflowStepPrivate()
{
	if (!this->ValidationState.isNull())
    {
		delete this->ValidationState;
    }
	if (!this->ProcessingState.isNull())
    {
		delete this->ProcessingState;
    }

	// If we delete the states, then Qt will handle deleting the transitions
}

void osgi::core::WorkflowStepPrivate::validationCompleteInternal(bool validationResults, const QString& branchId)const
{
	emit validationComplete(validationResults, branchId);
}

void osgi::core::WorkflowStepPrivate::onEntryCompleteInternal()const
{
	emit onEntryComplete();
}

void osgi::core::WorkflowStepPrivate::onExitCompleteInternal()const
{
	emit onExitComplete();
}

void osgi::core::WorkflowStepPrivate::invokeValidateCommandInternal(const QString& desiredBranchId)const
{
	emit invokeValidateCommand(desiredBranchId);
}

void osgi::core::WorkflowStepPrivate::invokeOnEntryCommandInternal(const WorkflowStep* comingFrom, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const
{
	emit invokeOnEntryCommand(comingFrom, transitionType);
}

void osgi::core::WorkflowStepPrivate::invokeOnExitCommandInternal(const WorkflowStep* goingTo, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const
{
	emit invokeOnExitCommand(goingTo, transitionType);
}
