#include <arkhe/osgi/core/workflow/WorkflowStep.hpp>

osgi::core::WorkflowStep::WorkflowStep()
: d_ptr(new WorkflowStepPrivate(*this))
{
}

osgi::core::WorkflowStep::WorkflowStep(const QString& newId)
  : d_ptr(new osgi::core::WorkflowStepPrivate(*this))
{
	Q_D(WorkflowStep);
	d->Id = newId;
}

osgi::core::WorkflowStep::WorkflowStep(osgi::core::WorkflowStepPrivate * pimpl, const QString& newId)
	:d_ptr(pimpl)
{
	Q_D(WorkflowStep);
	d->Id = newId;
}

osgi::core::WorkflowStep::~WorkflowStep()
{
}

GET_CPP(WorkflowStep, Workflow*, workflow, _Workflow);
SET_CPP(WorkflowStep, Workflow*, setWorkflow, _Workflow);

void osgi::core::WorkflowStep::setId(const QString& newId)
{
	Q_D(_WorkflowStep);
	if (d->Workflow && d->Workflow->hasStep(newId) && !this->id().isEmpty())
    {
		qWarning() << QString("WorkflowStep - Failed to change id from '%1' to '%2' - "
                          "Step already added to a workflow !").arg(this->id()).arg(newId);
		return;
    }

	d->Id = newId;
}

GET_CPP(WorkflowStep, QString, name, Name);
SET_CPP(WorkflowStep, const QString&, setName, Name);

GET_CPP(WorkflowStep, QString, description, Description);
SET_CPP(WorkflowStep, const QString&, setDescription, Description);

GET_CPP(WorkflowStep, QString, statusText, StatusText);
SET_CPP(WorkflowStep, const QString&, setStatusText, StatusText);

GET_CPP(WorkflowStep, bool, hasValidateCommand, HasValidateCommand);
SET_CPP(WorkflowStep, bool, setHasValidateCommand, HasValidateCommand);

GET_CPP(WorkflowStep, bool, hasOnEntryCommand, HasOnEntryCommand);
SET_CPP(WorkflowStep, bool, setHasOnEntryCommand, HasOnEntryCommand);

GET_CPP(WorkflowStep, bool, hasOnExitCommand, HasOnExitCommand);
SET_CPP(WorkflowStep, bool, setHasOnExitCommand, HasOnExitCommand);

GET_CPP(WorkflowStep, QState*, processingState, ProcessingState);
GET_CPP(WorkflowStep, QState*, validationState, ValidationState);

GET_CPP(WorkflowStep, WorkflowIntrastepTransition*, validationTransition, ValidationTransition);
GET_CPP(WorkflowStep, WorkflowIntrastepTransition*, validationFailedTransition, ValidationFailedTransition);

GET_CPP(WorkflowStep, bool, isWidgetType, WidgetType);


QObject* osgi::core::WorkflowStep::WorkflowStepQObject()
{
	Q_D(WorkflowStep);
	return d;
}

void osgi::core::WorkflowStep::validationComplete(bool validationResults, const QString& branchId)const
{
	Q_D(const WorkflowStep);
	d->validationCompleteInternal(validationResults, branchId);
}

void osgi::core::WorkflowStep::onEntryComplete()const
{
	Q_D(const WorkflowStep);
	d->onEntryCompleteInternal();
}

void osgi::core::WorkflowStep::onExitComplete()const
{
	Q_D(const WorkflowStep);
	d->onExitCompleteInternal();
}

void osgi::core::WorkflowStep::invokeValidateCommand(const QString& desiredBranchId)const
{
	Q_D(const WorkflowStep);
	d->invokeValidateCommandInternal(desiredBranchId);
}

void osgi::core::WorkflowStep::invokeOnEntryCommand(const WorkflowStep* comingFrom, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const
{
	Q_D(const WorkflowStep);
	d->invokeOnEntryCommandInternal(comingFrom, transitionType);
}

void osgi::core::WorkflowStep::invokeOnExitCommand(const WorkflowStep* goingTo, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const
{
	Q_D(const WorkflowStep);
	d->invokeOnExitCommandInternal(goingTo, transitionType);
}

void osgi::core::WorkflowStep::validate(const QString& desiredBranchId)
{
	Q_D(WorkflowStep);
	if (this->workflow()->verbose())
    {
		qDebug() << QString("validate - validating the input from %1").arg(d->Name);
    }

	this->validationComplete(true, desiredBranchId);
}


void osgi::core::WorkflowStep::onEntry(const WorkflowStep* comingFrom,
                              const WorkflowInterstepTransition::InterstepTransitionType transitionType)
{
	Q_UNUSED(comingFrom);
	Q_UNUSED(transitionType);

	// Signals that we are finished
	this->onEntryComplete();
}

void osgi::core::WorkflowStep::onExit(const WorkflowStep* goingTo,
                             const WorkflowInterstepTransition::InterstepTransitionType transitionType)
{
	Q_UNUSED(goingTo);
	Q_UNUSED(transitionType);

	// Signals that we are finished
	this->onExitComplete();
}
