#include <arkhe/osgi/core/workflow/WorkflowStep.hpp>

osgi::core::WorkflowStep::WorkflowStep()
	: d_ptr(new WorkflowStepPrivate(*this))

{
}

osgi::core::WorkflowStep::WorkflowStep(const QString& newId)
	: d_ptr(new WorkflowStepPrivate(*this))
{
  Q_D(WorkflowStep);
  d->Id = newId;
}

osgi::core::WorkflowStep::WorkflowStep(WorkflowStepPrivate * pimpl, const QString& newId)
	: d_ptr(pimpl)
{
	Q_D(WorkflowStep);
	d->Id = newId;
}

osgi::core::WorkflowStep::~WorkflowStep()
{
}

GET_CPP(osgi::core::WorkflowStep, osgi::core::Workflow*, workflow, _workflow);
SET_CPP(osgi::core::WorkflowStep, osgi::core::Workflow*, setWorkflow, _workflow);
GET_CPP(osgi::core::WorkflowStep, QString, id, Id);

void osgi::core::WorkflowStep::setId(const QString& newId)
{
	Q_D(WorkflowStep);
	// if (d->_workflow && d->_workflow->hasStep(newId) && !this->id().isEmpty())
    {
		qWarning() << QString("ctkWorkflowStep - Failed to change id from '%1' to '%2' - "
                          "Step already added to a workflow !").arg(this->id()).arg(newId);
		return;
    }

	d->Id = newId;
}

GET_CPP(osgi::core::WorkflowStep, QString, name, Name);
SET_CPP(osgi::core::WorkflowStep, const QString&, setName, Name);
GET_CPP(osgi::core::WorkflowStep, QString, description, Description);
SET_CPP(osgi::core::WorkflowStep, const QString&, setDescription, Description);
GET_CPP(osgi::core::WorkflowStep, QString, statusText, StatusText);
SET_CPP(osgi::core::WorkflowStep, const QString&, setStatusText, StatusText);
GET_CPP(osgi::core::WorkflowStep, bool, hasValidateCommand, HasValidateCommand);
SET_CPP(osgi::core::WorkflowStep, bool, setHasValidateCommand, HasValidateCommand);
GET_CPP(osgi::core::WorkflowStep, bool, hasOnEntryCommand, HasOnEntryCommand);
SET_CPP(osgi::core::WorkflowStep, bool, setHasOnEntryCommand, HasOnEntryCommand);
GET_CPP(osgi::core::WorkflowStep, bool, hasOnExitCommand, HasOnExitCommand);
SET_CPP(osgi::core::WorkflowStep, bool, setHasOnExitCommand, HasOnExitCommand);
GET_CPP(osgi::core::WorkflowStep, QState*, processingState, ProcessingState);
GET_CPP(osgi::core::WorkflowStep, QState*, validationState, ValidationState);
GET_CPP(osgi::core::WorkflowStep, osgi::core::WorkflowIntrastepTransition*, validationTransition, ValidationTransition);
GET_CPP(osgi::core::WorkflowStep, osgi::core::WorkflowIntrastepTransition*, validationFailedTransition, ValidationFailedTransition);
GET_CPP(osgi::core::WorkflowStep, bool, isWidgetType, WidgetType);

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
	// if (this->workflow()->verbose())
    {
		qDebug() << QString("validate - validating the input from %1").arg(d->Name);
    }

	this->validationComplete(true, desiredBranchId);
}

void osgi::core::WorkflowStep::onEntry(const WorkflowStep* comingFrom,
                              const osgi::core::WorkflowInterstepTransition::InterstepTransitionType transitionType)
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
 
 this->onExitComplete();
}




