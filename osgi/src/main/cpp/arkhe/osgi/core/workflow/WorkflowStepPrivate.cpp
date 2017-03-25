#include <QMetaEnum>
#include <arkhe/osgi/core/workflow/WorkflowStepPrivate.hpp>

osgi::core::WorkflowStepPrivate::WorkflowStepPrivate()

{

}

osgi::core::WorkflowStepPrivate::~WorkflowStepPrivate()
{


	// If we delete the states, then Qt will handle deleting the transitions
}
/*
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
*/
