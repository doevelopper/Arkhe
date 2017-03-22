#include <arkhe/osgi/core/workflow/WorkflowInterstepTransition.hpp>
#include <arkhe/osgi/core/workflow/WorkflowPrivate.hpp>
#include <arkhe/osgi/core/workflow/Workflow.hpp>

osgi::core::WorkflowPrivate::WorkflowPrivate(Workflow& object)
  :q_ptr(&object)
{
	this->InitialStep = 0;
	this->CurrentStep = 0;

	this->OriginStep = 0;
	this->DestinationStep = 0;

	this->GoToStep = 0;
	this->StartingStep = 0;
	this->TransitionToPreviousStartingStep = 0;

	// By default, go back to the origin step upon success of the goToStep(targetId) attempt.
	this->GoBackToOriginStepUponSuccess = true;

	this->ARTIFICIAL_BRANCH_ID_PREFIX = "WorkflowArtificialBranchId_";

	this->Verbose = false;
}

osgi::core::WorkflowPrivate::~WorkflowPrivate()
{
}

bool osgi::core::WorkflowPrivate::addStep(WorkflowStep* step)
{
	Q_Q(Workflow);

	Q_ASSERT(step);
	Q_ASSERT(!q->hasStep(step->id()));
	Q_ASSERT(!this->StateMachine->isRunning());

	if (!step->workflow())
    {
		step->setWorkflow(q);
    }

	if (step->workflow() != q)
    {
		// Check if steps are not already associated with a different workflow
		QString msg("addStep - step [%1] already associated with a different workfow !");
		qWarning() << msg.arg(step->id());
		return false;
    }

	if (!this->RegisteredSteps.contains(step))
    {
		this->RegisteredSteps << step;
		emit q->stepRegistered(step);
    }

	// Add the states, creating them if necessary
	this->StateMachine->addState(step->processingState());
	this->StateMachine->addState(step->validationState());

	// Update the map of steps to transitions and the <state,step> map
	this->StepToForwardAndBackwardStepMap.insert(step, new ForwardAndBackwardSteps);

	// this->StateToStepMap[step->processingState()] = step;
	// this->StateToStepMap[step->validationState()] = step;

	// Setup the signal/slot that triggers the attempt to go to the next step
	QObject::connect(step->validationState(), SIGNAL(entered()), q, SLOT(attemptToGoToNextStep()));

	// Setup the signal/slot that triggers the evaluation of the validation results
	// after validate(const QString&) is called
	this->connect(step->WorkflowStepQObject()
				, SIGNAL(validationComplete(bool,QString))
				,q
				, SLOT(evaluateValidationResults(bool,QString)));

	this->connect(step->WorkflowStepQObject()
				, SIGNAL(onEntryComplete())
				, SLOT(processingAfterOnEntry()));

	this->connect(step->WorkflowStepQObject()
				, SIGNAL(onExitComplete())
				, SLOT(processingAfterOnExit()));

	return (true);
}

bool osgi::core::WorkflowPrivate::hasDuplicateTransition(WorkflowStep* origin, WorkflowStep* destination,
                                                const Workflow::TransitionDirectionality directionality)
{
	Q_Q(Workflow);

	Q_ASSERT(origin);
	Q_ASSERT(destination);
	Q_ASSERT(directionality == Workflow::Forward || Workflow::Backward);

	WorkflowPrivate::StepListType stepList;
	WorkflowStep* targetStep = 0;

	if (directionality == Workflow::Forward)
    {
		stepList = q->forwardSteps(origin);
		targetStep = destination;
    }
	else if (directionality == Workflow::Backward)
    {
		stepList = q->backwardSteps(destination);
		targetStep = origin;
    }

	foreach(WorkflowStep * step, stepList)
    {
		if (step == targetStep)
		{
			return true;
		}
    }

	return (false);
}

bool osgi::core::WorkflowPrivate::hasTransitionWithSameBranchId(WorkflowStep* origin, WorkflowStep* destination,
                                                       const QString& branchId,
                                                       const Workflow::TransitionDirectionality directionality)
{
	Q_ASSERT(origin);
	Q_ASSERT(destination);
	Q_ASSERT(directionality == Workflow::Forward || Workflow::Backward);
	Q_ASSERT(!branchId.isEmpty());

	QList<QString> branchIdList;

	if (directionality == Workflow::Forward)
    {
		branchIdList = this->forwardBranchIds(origin);
    }
	else if (directionality == Workflow::Backward)
    {
		branchIdList = this->backwardBranchIds(destination);
    }

	foreach(QString id, branchIdList)
    {
		if (QString::compare(id, branchId, Qt::CaseInsensitive) == 0)
		{
			return (true);
		}
    }
	
	return (false);
}

void osgi::core::WorkflowPrivate::createTransitionToNextStep(WorkflowStep* origin,
                                                    WorkflowStep* destination,
                                                    const QString& branchId)
{
	Q_Q(Workflow);

	Q_ASSERT(origin);
	Q_ASSERT(destination);
	Q_ASSERT(!q->hasTransition(origin, destination, branchId, Workflow::Forward));

	QString id;
	// create an artificial branchId if one is not given
	if (branchId.isEmpty())
    {
		id.setNum(this->numberOfForwardSteps(origin));
		id.prepend(this->ARTIFICIAL_BRANCH_ID_PREFIX);
    }
	else
    {
		id = branchId;
    }

	// Create the transition
	WorkflowInterstepTransition* transition = new WorkflowInterstepTransition(WorkflowInterstepTransition::TransitionToNextStep, id);
	transition->setTargetState(destination->processingState());
	origin->validationState()->addTransition(transition);

	// Update the step to transitions map
	this->StepToForwardAndBackwardStepMap.value(origin)->appendForwardStep(destination, id);

	// Setup the signal/slot that shows and hides the steps' user interfaces
	// on transition to the next step
	QObject::connect(transition, SIGNAL(triggered()), q, SLOT(performTransitionBetweenSteps()));
}

void osgi::core::WorkflowPrivate::createTransitionToPreviousStep(WorkflowStep* origin,
                                                        WorkflowStep* destination,
                                                        const QString& branchId)
{
	Q_Q(Workflow);

	Q_ASSERT(origin);
	Q_ASSERT(destination);
	Q_ASSERT(!q->hasTransition(origin, destination, branchId, Workflow::Backward));

	QString id;
	// create an artificial branchId if one is not given
	if (branchId.isEmpty())
    {
		id.setNum(this->numberOfBackwardSteps(destination));
		id.prepend(this->ARTIFICIAL_BRANCH_ID_PREFIX);
    }
	else
    {
		id = branchId;
    }

	WorkflowInterstepTransition* transition = new WorkflowInterstepTransition(WorkflowInterstepTransition::TransitionToPreviousStep, id);
	transition->setTargetState(origin->processingState());
	destination->processingState()->addTransition(transition);

	// Update the step to transitions map
	this->StepToForwardAndBackwardStepMap.value(destination)->appendBackwardStep(origin, id);

	// Setup the signal/slot that shows and hides the steps' user
	// interfaces on transition to the previous step
	QObject::connect(transition, SIGNAL(triggered()), q, SLOT(performTransitionBetweenSteps()));
}

void osgi::core::WorkflowPrivate::createTransitionToPreviousStartingStep(WorkflowStep* startingStep,
                                                                WorkflowStep* currentStep)
{
	Q_Q(Workflow);

	Q_ASSERT(startingStep);
	Q_ASSERT(currentStep);

	if (!this->TransitionToPreviousStartingStep)
    {
		WorkflowInterstepTransition* transition = new WorkflowInterstepTransition(
        WorkflowInterstepTransition::TransitionToPreviousStartingStepAfterSuccessfulGoToFinishStep);

		// Setup the signal/slot that shows and hides the steps' user interfaces
		// on transition to the previous step
		QObject::connect(transition, SIGNAL(triggered()), q, SLOT(performTransitionBetweenSteps()));

		this->TransitionToPreviousStartingStep = transition;
    }

	QState* currentState;
	// looping on the finish step
	if (startingStep == currentStep)
    {
		currentState = currentStep->validationState();
    }
	else
    {
		currentState = currentStep->processingState();
    }

    this->TransitionToPreviousStartingStep->setTargetState(startingStep->processingState());
    currentState->addTransition(this->TransitionToPreviousStartingStep);
}

osgi::core::WorkflowStep* osgi::core::WorkflowPrivate::stepFromId(const QString& id)const
{
	foreach(WorkflowStep* step, this->StepToForwardAndBackwardStepMap.keys())
    {
		Q_ASSERT(step);
		if (QString::compare(step->id(), id, Qt::CaseInsensitive) == 0)
		{
			return step;
		}
    }
  return 0;
}

QList<QString> osgi::core::WorkflowPrivate::forwardBranchIds(WorkflowStep* step)const
{
	Q_ASSERT(step);
	return this->StepToForwardAndBackwardStepMap.value(step)->forwardBranchIds();
}

QList<QString> osgi::core::WorkflowPrivate::backwardBranchIds(WorkflowStep* step)const
{
	Q_ASSERT(step);
	return this->StepToForwardAndBackwardStepMap.value(step)->backwardBranchIds();
}

void osgi::core::WorkflowPrivate::validateInternal(WorkflowStep* step)
{
	Q_ASSERT(step);

	if(this->Verbose)
    {
		qDebug() << QString("validateInternal - validating input from %1").arg(step->name());
    }

	if (step->hasValidateCommand())
    {
		step->invokeValidateCommand(this->DesiredBranchId);
    }
	else
    {
		step->validate(this->DesiredBranchId);
    }
}


void osgi::core::WorkflowPrivate::onEntryInternal(WorkflowStep* step, WorkflowStep* comingFrom,
    const WorkflowInterstepTransition::InterstepTransitionType& transitionType)
{
	Q_ASSERT(step);

	if(this->Verbose)
    {
		qDebug() << QString("onEntryInternal - entering input from %1").arg(step->name());
    }

	//Ensure we are transitioning between steps or starting the workflow
	Q_ASSERT(transitionType == WorkflowInterstepTransition::TransitionToNextStep
           || transitionType == WorkflowInterstepTransition::TransitionToPreviousStep
           || transitionType == WorkflowInterstepTransition::StartingWorkflow
           || transitionType == WorkflowInterstepTransition::TransitionToPreviousStartingStepAfterSuccessfulGoToFinishStep);

	if (step->hasOnEntryCommand())
    {
		step->invokeOnEntryCommand(comingFrom, transitionType);
    }
	else
    {
		step->onEntry(comingFrom, transitionType);
    }
}

void osgi::core::WorkflowPrivate::processingAfterOnEntry()
{
	Q_Q(Workflow);

	if (this->Verbose)
    {
		qDebug() << "processingAfterOnEntry";
    }

	if (!this->DestinationStep)
    {
		qWarning() << "processingAfterOnEntry - Called processingAfterOnEntry without "
                  "having set a destination step";
		return;
    }

	// Update the currentStep and previous step
	this->CurrentStep = this->DestinationStep;

	// Reset the pointers used internally for performing a transition
	this->OriginStep = 0;
	this->DestinationStep = 0;

	// // Reset the pointers used internally for performing a transition
	// // back to the starting step
	// if (d->TransitionToPreviousStartingStep)
	//   {

	//   std::cout << "TRANSITION TO PREVIOUS STARTING STEP EXISTS" << std::endl;
	//   //d->TransitionToPreviousStartingStep->sourceState()->removeTransition(d->TransitionToPreviousStartingStep);
	//   //std::cout << "removed" << std::endl;
	//   // d->TransitionToPreviousStartingStep = 0;
	//   //destination->processingState()->removeTransition(d->TransitionToPreviousStartingStep);
	//   //delete d->TransitionToPreviousStartingStep;
	//   // d->TransitionToPreviousStartingStep = 0;
	//   std::cout << "here" << std::endl;
	//   }

	// If we are trying to get to the finish step, then check if we are
	// finished.
	if (this->GoToStep)
    {
		if (this->CurrentStep == this->GoToStep)
		{
			q->goToStepSucceeded();
		}
		// if we're not finished, continue transitioning to the next step
		else
		{
			q->goForward();
		}
    }
	else
    {
		emit q->currentStepChanged(this->CurrentStep);
    }
}

void osgi::core::WorkflowPrivate::onExitInternal(WorkflowStep* step,
    WorkflowStep* goingTo,
    const WorkflowInterstepTransition::InterstepTransitionType& transitionType)
{
	Q_ASSERT(step);

	if (this->Verbose)
    {
		qDebug() << QString("onExitInternal - exiting %1").arg(step->name());
    }

	// Ensure we are transitioning between steps or starting the workflow
	Q_ASSERT (transitionType == WorkflowInterstepTransition::TransitionToNextStep ||
				transitionType == WorkflowInterstepTransition::TransitionToPreviousStep ||
				transitionType == WorkflowInterstepTransition::StoppingWorkflow ||
				transitionType == WorkflowInterstepTransition::TransitionToPreviousStartingStepAfterSuccessfulGoToFinishStep);

	if (step->hasOnExitCommand())
    {
		step->invokeOnExitCommand(goingTo, transitionType);
    }
	else
    {
		step->onExit(goingTo, transitionType);
    }
}
void osgi::core::WorkflowPrivate::processingAfterOnExit()
{
	// enter the destination step if we have one
	if (this->DestinationStep)
    {
		this->onEntryInternal(this->DestinationStep, this->OriginStep, this->TransitionType);
    }
		// reset the pointers used internally for performing a transition if we're done
	else
    {
		this->OriginStep = 0;
		this->DestinationStep = 0;
		// we've exited the CurrentStep and haven't gone into another step, so we no longer have a
		// currentStep.
		this->CurrentStep = 0;
    }
}

osgi::core::WorkflowStep* osgi::core::WorkflowPrivate::stepFromState(const QAbstractState* state)
{
	if (state)
    {
		return this->StateToStepMap.value(state);
    }
	return 0;
}

int osgi::core::WorkflowPrivate::numberOfForwardSteps(WorkflowStep* step)
{
	Q_Q(Workflow);
	return q->forwardSteps(step).length();
}

int osgi::core::WorkflowPrivate::numberOfBackwardSteps(WorkflowStep* step)
{
	Q_Q(Workflow);
	return q->backwardSteps(step).length();
}

bool osgi::core::WorkflowPrivate::pathExists(const QString& goalId, WorkflowStep* origin)const
{
	// Q_Q(const Workflow);

	// Q_ASSERT(!goalId.isEmpty());
	// Q_ASSERT(this->CurrentStep);

	// QString originId;
	// if (origin)
    // {
		// originId = origin->id();
    // }
	// else
    // {
		// originId = this->CurrentStep->id();
    // }

	// there exists a path from the origin to the goal if:
	// - there is a goal AND
	// - either:
	//   - the origin is already the goal
	//   - there is a path from at least one of the origin's successors to the goal
	// return (q->hasStep(goalId)
				// && ((QString::compare(goalId, originId, Qt::CaseInsensitive) == 0)
				// || (q->canGoForward(origin)))); // <-- TODO insert logic here for looking at graph
}

bool osgi::core::WorkflowPrivate::pathExistsFromNextStep(const QString& goalId, const QString& branchId)const
{
	// Q_ASSERT(!goalId.isEmpty());
	// Q_ASSERT(!branchId.isEmpty());
	// Q_ASSERT(this->CurrentStep);

	// //return whether there exists a path from the the step that will be followed (given the branchId) to the goal
	// WorkflowStep* nextStep = this->StepToForwardAndBackwardStepMap.value(this->CurrentStep)->forwardStep(branchId);

	// if (!nextStep)
    // {
		// return false;
    // }
	// else
    // {
		// return this->pathExists(goalId, nextStep);
    // }
}

