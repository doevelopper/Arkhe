
#include <iostream>
#include <arkhe/osgi/core/workflow/Workflow.hpp>
#include <arkhe/osgi/core/workflow/WorkflowPrivate.hpp>
#include <arkhe/osgi/core/workflow/WorkflowStep.hpp>

osgi::core::Workflow::Workflow(QObject* _parent) 
: Superclass(_parent)
  , d_ptr(new WorkflowPrivate(*this))
{
  Q_D(Workflow);
  d->StateMachine = new QStateMachine(this);
}

osgi::core::Workflow::~Workflow()
{
	Q_D(Workflow);

	if (d->StateMachine->isRunning())
    {
		d->StateMachine->stop();
    }

	// Clean registered step
	while (!d->RegisteredSteps.isEmpty())
    {
		delete d->RegisteredSteps.takeFirst();
    }
}

bool osgi::core::Workflow::addTransition(WorkflowStep* origin, WorkflowStep* destination,
                                const QString& branchId,
                                const Workflow::TransitionDirectionality directionality)
{
	Q_D(Workflow);

	if (d->StateMachine->isRunning())
    {
		qWarning() << "addTransition - Cannot add a transition while the workflow is started !";
		return false;
    }

	// Set origin id if empty
	if (origin && origin->id().isEmpty())
    {
		origin->setId(QString("step%1").arg(d->StepToForwardAndBackwardStepMap.count()));
    }

	// cannot currently create a transition between two steps of the same id, which is equivalent to
	// adding a transition from a step to itself
	if (origin && destination && (QString::compare(origin->id(), destination->id(), Qt::CaseInsensitive) == 0))
    {
		qWarning() << "addTransition - Workflow does not currently support a transition"
                  " from a step to itself.  Use GoToStep instead !";
		return false;
    }

	// add the origin step if it doesn't exist in the workflow yet
	if (origin && !this->hasStep(origin->id()))
    {
		bool ok = d->addStep(origin);
		if (!ok)
		{
			return false;
		}
    }

	// Set destination id if empty
	if (destination && destination->id().isEmpty())
    {
		destination->setId(QString("step%1").arg(d->StepToForwardAndBackwardStepMap.count()));
    }

	// add the destination step if it doesn't exist in the workflow yet
	if (destination && !this->hasStep(destination->id()))
    {
		bool ok = d->addStep(destination);
		if (!ok)
		{
			return false;
		}
    }

	if (origin && destination)
    {
		// ensure we haven't already added a transition with the same origin, destination and directionality
		if (this->hasTransition(origin, destination, branchId, directionality))
		{
			qWarning() << "addTransition - Cannot create a transition that matches a "
                    "previously created transition";
			return false;
		}

		// create the forward transition
		if (directionality == Workflow::Forward
			|| directionality == Workflow::Bidirectional)
		{
			//qDebug() << "addTransition" << origin->id() << "->" << destination->id();
			d->createTransitionToNextStep(origin, destination, branchId);
		}

			// create the backward transition
		if (directionality == Workflow::Backward
			|| directionality == Workflow::Bidirectional)
		{
			//qDebug() << "addTransition" << origin->id() << "<-" << destination->id();
			d->createTransitionToPreviousStep(origin, destination, branchId);
		}
    }

	// Set initialStep if needed
	if (origin && d->StepToForwardAndBackwardStepMap.count() == 2 && !this->initialStep())
    {
		this->setInitialStep(origin);
    }

  return (true);
}

bool osgi::core::Workflow::hasTransition(WorkflowStep* origin, WorkflowStep* destination,
                                const QString& branchId,
                                const Workflow::TransitionDirectionality directionality)
{
	Q_D(Workflow);

  // we have a bidirectional transition if we have both a forward and a backward transition
	if (directionality == Workflow::Bidirectional)
    {
		return this->hasTransition(origin, destination, branchId, Workflow::Forward)
			&& this->hasTransition(origin, destination, branchId, Workflow::Backward);
    }
	else
    {
		if (branchId.isEmpty())
		{
			return d->hasDuplicateTransition(origin, destination, directionality);
		}
		else
		{
			return d->hasDuplicateTransition(origin, destination, directionality)
				|| d->hasTransitionWithSameBranchId(origin, destination, branchId, directionality);
		}
    }
}

QList< osgi::core::WorkflowStep*> osgi::core::Workflow::forwardSteps(WorkflowStep* step)const
{
	Q_D(const Workflow);
  // use the given step if provided, otherwise use the workflow's current step
	if (step && d->StepToForwardAndBackwardStepMap.contains(step))
    {
		return d->StepToForwardAndBackwardStepMap.value(step)->forwardSteps();
    }
	else if (d->CurrentStep && d->StepToForwardAndBackwardStepMap.contains(d->CurrentStep))
    {
		return d->StepToForwardAndBackwardStepMap.value(d->CurrentStep)->forwardSteps();
    }
	else
    {
		return QList<WorkflowStep*>();
    }
}

QList< osgi::core::WorkflowStep*> osgi::core::Workflow::backwardSteps(WorkflowStep* step)const
{
	Q_D(const Workflow);
  // use the current step if provided, otherwise use the workflow's current step
	if (step && d->StepToForwardAndBackwardStepMap.contains(step))
    {
		return d->StepToForwardAndBackwardStepMap.value(step)->backwardSteps();
    }
	else if (d->CurrentStep && d->StepToForwardAndBackwardStepMap.contains(d->CurrentStep))
    {
		return d->StepToForwardAndBackwardStepMap.value(d->CurrentStep)->backwardSteps();
    }
	else
    {
		return QList<WorkflowStep*>();
    }
}

QList< osgi::core::WorkflowStep*> osgi::core::Workflow::finishSteps()const
{
	Q_D(const Workflow);

  // iterate through our list of steps, and keep the steps that don't have anything following them
	QList<WorkflowStep*> finishSteps;
	foreach (WorkflowStep* step, d->StepToForwardAndBackwardStepMap.keys())
    {
		if (!this->canGoForward(step))
		{
			finishSteps.append(step);
		}
    }

	return finishSteps;
}

QList< osgi::core::WorkflowStep*> osgi::core::Workflow::steps()const
{
	Q_D(const Workflow);
	return d->RegisteredSteps;
}

bool osgi::core::Workflow::canGoForward(WorkflowStep* step)const
{
  return (!this->forwardSteps(step).isEmpty());
}

bool osgi::core::Workflow::canGoBackward(WorkflowStep* step)const
{
  return (!this->backwardSteps(step).isEmpty());
}


bool osgi::core::Workflow::canGoToStep(const QString& targetId, WorkflowStep* step)const
{
	Q_D(const Workflow);
	return d->pathExists(targetId, step);
}


bool osgi::core::Workflow::hasStep(const QString& id)const
{
  Q_D(const Workflow);
  return d->stepFromId(id);
}


osgi::core::WorkflowStep* osgi::core::Workflow::step(const QString& id)const
{
	Q_D(const Workflow);
	return d->stepFromId(id);
}


// Convenience method to set the QStateMachine's initialState to a
// specific step's processing state.
GET_CPP(Workflow, WorkflowStep*, initialStep, InitialStep);
SET_CPP(Workflow, WorkflowStep*, setInitialStep, InitialStep);


GET_CPP(Workflow, WorkflowStep*, currentStep, CurrentStep);


void osgi::core::Workflow::start()
{
	Q_D(Workflow);
	if (!d->InitialStep)
    {
		qWarning() << "start - Cannot start workflow without an initial step";
		return;
    }

	d->StateMachine->setInitialState(d->InitialStep->processingState());
	d->OriginStep = 0;
	d->DestinationStep = d->InitialStep;
	d->TransitionType = WorkflowInterstepTransition::StartingWorkflow;
	d->onEntryInternal(d->DestinationStep, d->OriginStep, d->TransitionType);

	d->StateMachine->start();
}

bool osgi::core::Workflow::isRunning()const
{
	Q_D(const Workflow);
	return d->StateMachine->isRunning();
}

void osgi::core::Workflow::stop()
{
	Q_D(Workflow);
	if (!d->StateMachine->isRunning())
    {
		return;
    }

	// Setup to do the exit processing for the current step
	if (d->CurrentStep)
    {
		d->OriginStep = d->CurrentStep;
		d->DestinationStep = 0;
		d->TransitionType = ctkWorkflowInterstepTransition::StoppingWorkflow;
		d->onExitInternal(d->OriginStep, d->DestinationStep, d->TransitionType);
    }

	d->StateMachine->stop();
}

void osgi::core::Workflow::goForward(const QString& desiredBranchId)
{
	Q_D(Workflow);

	if (!this->isRunning())
    {
		qWarning() << "goForward - The workflow is not running !";
		return;
    }

	  // if we're just going to the next step and not to a 'goTo' step, then check to make sure that
	  // there exists a step following the current step
	if (!d->GoToStep)
    {
		if (!this->canGoForward())
		{
			qWarning() << "goForward - Attempt to goForward from a finish step !";
			return;
		}
    }

	d->DesiredBranchId = desiredBranchId;

	if (d->Verbose)
    {
		qDebug() << "goForward - posting ValidationTransition";
    }
	d->StateMachine->postEvent(
		new WorkflowIntrastepTransitionEvent(WorkflowIntrastepTransition::ValidationTransition));
}

void osgi::core::Workflow::goBackward(const QString& desiredBranchId)
{
	Q_D(Workflow);

	if (!this->isRunning())
    {
		qWarning() << "goBackward - The workflow is not running !";
		return;
    }

	if (!this->canGoBackward())
    {
		qWarning() << "goBackward - Attempt to goBackward from first step !";
		return;
    }

	WorkflowStep* previousStep = d->StepToPreviousStepMap[d->CurrentStep];
	Q_ASSERT(previousStep);
	QString branchId = d->StepToForwardAndBackwardStepMap.value(d->CurrentStep)->backwardBranchId(previousStep);
	Q_ASSERT(!branchId.isEmpty());

	d->DesiredBranchId = desiredBranchId;

	if (d->Verbose)
    {
		qDebug() << "goBackward - posting TransitionToPreviousStep";
    }
	d->StateMachine->postEvent(
                             new WorkflowInterstepTransitionEvent(WorkflowInterstepTransition::TransitionToPreviousStep, branchId));
}


GET_CPP(Workflow, bool, goBackToOriginStepUponSuccess, GoBackToOriginStepUponSuccess);
SET_CPP(Workflow, bool, setGoBackToOriginStepUponSuccess, GoBackToOriginStepUponSuccess);

GET_CPP(Workflow, bool, verbose, Verbose);
SET_CPP(Workflow, bool, setVerbose, Verbose);


void osgi::core::Workflow::goToStep(const QString& targetId)
{
	Q_D(Workflow);

	if (!this->isRunning())
    {
		qWarning() << "goToStep - The workflow is not running !";
		return;
    }

	// TODO currently returns true only if the workflow is running - need logic here
	if (!this->canGoToStep(targetId))
    {
		qWarning() << QString("goToStep - Cannot goToStep %1 ").arg(targetId);
		return;
    }

#ifndef QT_NO_DEBUG
	WorkflowStep* step = d->stepFromId(targetId);
	Q_ASSERT(step);
#endif

	if (d->Verbose)
    {
		qDebug() << QString("goToStep - Attempting to go to finish step %1").arg(targetId);
    }

  // if (step == d->CurrentStep)
  //   {
  //   if (d->Verbose)
  //     {
  //     qDebug() << "we are already in the desired finish step";
  //     }
  //   return;
  //   }

	d->GoToStep = d->stepFromId(targetId);
	d->StartingStep = d->CurrentStep;
	this->goForward();
}


void osgi::core::Workflow::attemptToGoToNextStep()
{
	Q_D(Workflow);
	if (d->Verbose)
    {
		qDebug() << "attemptToGoToNextStep - Attempting to go to the next step ";
    }

	Q_ASSERT(d->CurrentStep);
  //Q_ASSERT(this->canGoForward(d->CurrentStep));

	d->validateInternal(d->CurrentStep);
}

void osgi::core::Workflow::evaluateValidationResults(bool validationSucceeded, const QString& branchId)
{
	if (validationSucceeded)
    {
		this->goToNextStepAfterSuccessfulValidation(branchId);
    }
	else
    {
		this->goToProcessingStateAfterValidationFailed();
    }
}

// --------------------------------------------------------------------------
// if ctkWorkflowStep::validationComplete() did not provide a branchId, then:
// - if there is one step following the current step, we will follow that transition
// - if there are multiple steps following the current step, then we will follow the first
// transition that was added
// (either way this corresponds to following the first forwardBranchId we've recorded)
// if ctkWorkflowStep::validationComplete() provided a branchId, then:
// - if there is one transition following the current step that was not created using a branchId,
// then we will follow it
// - otherwise do a conditional branching based on the branchId provided by validationComplete()

void osgi::core::Workflow::goToNextStepAfterSuccessfulValidation(const QString& branchId)
{
	Q_D(Workflow);
	if (d->Verbose)
    {
		qDebug() << "goToNextStepAfterSuccessfulValidation - Validation succeeded";
		qDebug() << "goToNextStepAfterSuccessfulValidation - Posting TransitionToNextStep";
    }

	// we may already be in the 'goTo' step - i.e. looping on a finish step
	if (d->GoToStep && d->CurrentStep == d->GoToStep)
    {
		this->goToStepSucceeded();
		return;
    }

	QString transitionBranchId;

	// these values are helpful for the logic below
	QString firstForwardBranchId = d->StepToForwardAndBackwardStepMap.value(d->CurrentStep)->firstForwardBranchId();
	int numberOfForwardSteps = d->numberOfForwardSteps(d->CurrentStep);
	Q_ASSERT(!firstForwardBranchId.isEmpty());
	Q_ASSERT(numberOfForwardSteps);

	// validationComplete() does not give us a branchId
	if (branchId.isEmpty())
    {
		transitionBranchId = firstForwardBranchId;
		if (numberOfForwardSteps > 1)
		{
			qWarning() << "goToNextStepAfterSuccessfulValidation - WorkflowStep::ValidatComplete() "
                    "did not provide branchId at a branch in the workflow - will follow first "
                    "transition that was created";
		}
    }
	// validationComplete() gives us a branchId
	else
    {
		if (numberOfForwardSteps == 1 && firstForwardBranchId.contains(d->ARTIFICIAL_BRANCH_ID_PREFIX))
		{
			transitionBranchId = firstForwardBranchId;
			qWarning() << "goToNextStepAfterSuccessfulValidation -  WorkflowStep::ValidationComplete()"
                    " returns a branchId, but was overridden by the workflow";
		}
		else
		{
			transitionBranchId = branchId;
		}
    }

	// if we are trying to go to a 'goTo' step, check that the selected branch will still take us along a path that leads to the 'goTo' step, and fail if not
	if (d->GoToStep && !d->pathExistsFromNextStep(d->GoToStep->id(), transitionBranchId))
    {
		this->goToProcessingStateAfterValidationFailed();
		return;
    }

  d->StateMachine->postEvent(new WorkflowInterstepTransitionEvent(WorkflowInterstepTransition::TransitionToNextStep, transitionBranchId));
}

void osgi::core::Workflow::goToProcessingStateAfterValidationFailed()
{
	Q_D(Workflow);
	if (d->Verbose)
    {
		qDebug() << "goToNextStepAfterSuccessfulValidation - Validation failed";
    }
	// Validation failed in the process of attempting to go to the finish step
	if (d->GoToStep)
    {
		this->goToStepFailed();
    }

	if (d->Verbose)
    {
		qDebug() << "goToNextStepAfterSuccessfulValidation - Posting ValidationFailedTransition";
    }
  d->StateMachine->postEvent(new WorkflowIntrastepTransitionEvent(WorkflowIntrastepTransition::ValidationFailedTransition));
}

void osgi::core::Workflow::performTransitionBetweenSteps()
{
	Q_D(Workflow);

	if (d->Verbose)
    {
		qDebug() << "performTransitionBetweenSteps - Performing transition between steps";
    }

  // Alternative: could find the origin and destination step based on
  // d->CurrentStep rather than QObject::sender(), but would require
  // keeping track of an origin step's destination step (and would be
  // tricky in an extension to branching workflows, unless we change
  // this method signature)

	WorkflowInterstepTransition* transition = qobject_cast<WorkflowInterstepTransition*>(QObject::sender());
	Q_ASSERT(transition);

	d->OriginStep = d->stepFromState(transition->sourceState());
	d->DestinationStep = d->stepFromState(transition->targetState());
	d->TransitionType = transition->transitionType();
	Q_ASSERT(d->TransitionType == WorkflowInterstepTransition::TransitionToNextStep
           || d->TransitionType == WorkflowInterstepTransition::TransitionToPreviousStep
           || d->TransitionType == WorkflowInterstepTransition::TransitionToPreviousStartingStepAfterSuccessfulGoToFinishStep);

	// update the map from the step to the previous step if we are going forward
	if (d->TransitionType == WorkflowInterstepTransition::TransitionToNextStep)
    {
		d->StepToPreviousStepMap.insert(d->DestinationStep, d->OriginStep);
    }

	// exit the destination step
	d->onExitInternal(d->OriginStep, d->DestinationStep, d->TransitionType);
}

void osgi::core::Workflow::goToStepSucceeded()
{
	Q_D(Workflow);

	if (d->Verbose)
    {
		qDebug() << "goToStepSucceeded";
    }

	  // after success, go back to the step at which we begin looking for
	  // the finish step (will exit the current step and enter the starting step)
	  // only if the property goBackToOriginStepUponSuccess is true.

	if (this->goBackToOriginStepUponSuccess())
    {
		d->createTransitionToPreviousStartingStep(d->StartingStep, d->CurrentStep);
    }

	d->GoToStep = 0;
	d->StartingStep->setStatusText("Attempt to go to the finish step succeeded");
	d->StartingStep = 0;

	if (this->goBackToOriginStepUponSuccess())
    {
		this->goFromGoToStepToStartingStep();
    }
}


void osgi::core::Workflow::goFromGoToStepToStartingStep()
{
	Q_D(Workflow);
	if (d->Verbose)
    {
		qDebug() << "goFromGoToStepToStartingStep - Posting TransitionToPreviousStartingStep";
    }
	d->StateMachine->postEvent(new WorkflowInterstepTransitionEvent(WorkflowInterstepTransition::TransitionToPreviousStartingStepAfterSuccessfulGoToFinishStep));
}


void osgi::core::Workflow::goToStepFailed()
{
  // Abort attempt to get to the finish step
	Q_D(Workflow);

	d->GoToStep = 0;
	d->StartingStep = 0;

	  // We don't need to transition between steps - leave the user at the
	  // point of failure, so that they can try to continue manually
	  // Emit the signal that we have changed the current step, since it wasn't emitted in the process
	  // of going to the 'goTo' step.
	  emit this->currentStepChanged(d->CurrentStep);

  // if (failedOnBranch)
  //   {
  //   this->goToProcessingStateAfterValidationFailed();
  //   }

}

int osgi::core::Workflow::backwardDistanceToStep(WorkflowStep* fromStep,
                                        WorkflowStep* origin) const
{
	if (!fromStep)
    {
		fromStep = this->currentStep();
    }
	if (!origin)
    {
		origin = this->initialStep();
    }

	if (!fromStep || !origin)
    {
		return -1;
    }

	QQueue< std::pair<WorkflowStep*, int> > queue;
	queue.append(std::make_pair(fromStep, 0));
	
	while (! queue.isEmpty())
    {
		std::pair<WorkflowStep*, int> p = queue.dequeue();
		WorkflowStep* step = p.first;

		if (! step)
		{
			return -1;
		}

		if (step->id() == origin->id())
		{
			return p.second;
		}

		foreach(WorkflowStep* previousStep, this->backwardSteps(step))
		{
			queue.append(std::make_pair(previousStep, p.second + 1));
		}
    }

  return -1;
}
