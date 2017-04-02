#ifndef ARKHE_OSGI_WORKFLOWPRIVATE_HPP
#define ARKHE_OSGI_WORKFLOWPRIVATE_HPP

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/workflow/Workflow.hpp>
#include <arkhe/osgi/core/workflow/WorkflowStep.hpp>
#include <arkhe/osgi/core/workflow/ForwardAndBackwardSteps.hpp>

class QStateMachine;
// class Workflow;
/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class WorkflowPrivate : public QObject
		{
			Q_OBJECT
			Q_DECLARE_PUBLIC(Workflow);

		public:

			// WorkflowPrivate();
			WorkflowPrivate(Workflow& object);
			virtual ~WorkflowPrivate();
			/*!
			 *	@brief
			 */
			bool addStep(WorkflowStep* step);
			/*!
			 *	@brief
			 */
			bool hasDuplicateTransition(WorkflowStep* origin, WorkflowStep* destination,
                              const Workflow::TransitionDirectionality directionality);
			/*!
			 *	@brief
			 */
			bool hasTransitionWithSameBranchId(WorkflowStep* origin, WorkflowStep* destination,
                                     const QString& branchId,
                                     const Workflow::TransitionDirectionality directionality);
			/*!
			 *	@brief
			 */
			void createTransitionToNextStep(WorkflowStep* origin,
                                  WorkflowStep* destination,
                                  const QString& branchId = "");
			/*!
			 *	@brief
			 */
			void createTransitionToPreviousStep(WorkflowStep* origin,
                                      WorkflowStep* destination,
                                      const QString& branchId = "");
			/*!
			 *	@brief
			 */
			void createTransitionToPreviousStartingStep(WorkflowStep* startingStep,
                                              WorkflowStep* currentStep);
			/*!
			 *	@brief
			 */
			void validateInternal(WorkflowStep* step);
			/*!
			 *	@brief
			 */
			void onEntryInternal(WorkflowStep* step, WorkflowStep* comingFrom,
                       const WorkflowInterstepTransition::InterstepTransitionType& transitionType);
			/*!
			 *	@brief
			 */
			void onExitInternal(WorkflowStep* step, WorkflowStep* goingTo,
                      const WorkflowInterstepTransition::InterstepTransitionType& transitionType);
			/*!
			 *	@brief Get the step in the workflow with a given id.
			 */
			WorkflowStep* stepFromId(const QString& id)const; 
			/*!
			 *	@brief Get the step that a state belongs to (if any).
			 */
			WorkflowStep* stepFromState(const QAbstractState* state);
			/*!
			 *	@brief Get the number of forward steps from the given step.
			 */
			int numberOfForwardSteps(WorkflowStep* step);
			/*!
			 *	@brief Get the number of backward steps from the given step.
			 */
			int numberOfBackwardSteps(WorkflowStep* step);
			/*!
			 *	@brief Get the ids of the steps that directly follow the given step.
			 */
			QList<QString> forwardBranchIds(WorkflowStep* step)const;
			/*!
			 *	@brief Get the ids of the steps that directly preceed the given step.
			 */
			QList<QString> backwardBranchIds(WorkflowStep* step)const;
			/*!
			 *	@brief Determines whether there exists a path from the origin step (the current step by default) to
			 *         the step with the given goal Id.
			 */
			bool pathExists(const QString& goalId, WorkflowStep* origin = 0)const;
			/*!
			 *	@brief Determines whether there exists a path from the current step's next step (as given by the
			 *         branchId) to the step with the given goal Id.
			 */
			bool pathExistsFromNextStep(const QString& goalId, const QString& branchId)const;
			
			
			using StepToForwardAndBackwardStepMapType = QMap<WorkflowStep*, ForwardAndBackwardSteps*>;
			using StepListType = QList<WorkflowStep*>;
			using StateToStepMapType = QMap<const QAbstractState*, WorkflowStep*>;
			using StateToStepMapIterator = QMap<const QAbstractState*, WorkflowStep*>::iterator;

			QStateMachine* StateMachine;
			QMap<WorkflowStep*, ForwardAndBackwardSteps*>  StepToForwardAndBackwardStepMap;
			StepListType RegisteredSteps;
			StateToStepMapType StateToStepMap;
			
			WorkflowStep* InitialStep;
			WorkflowStep* CurrentStep;
			QMap<WorkflowStep*, WorkflowStep*> StepToPreviousStepMap;
			WorkflowStep* OriginStep;
			WorkflowStep* DestinationStep;
			WorkflowInterstepTransition::InterstepTransitionType TransitionType;
			QString DesiredBranchId;
			WorkflowStep* GoToStep;
			WorkflowStep* StartingStep;
			WorkflowInterstepTransition* TransitionToPreviousStartingStep;
			bool GoBackToOriginStepUponSuccess;
			QString ARTIFICIAL_BRANCH_ID_PREFIX;
			bool Verbose;

		public Q_SLOTS:
			/*!
			 *	@brief Workflow processing executed after a step's onEntry function is run.
			 */
			void processingAfterOnEntry();
			/*!
			 *	@brief Workflow processing executed after a step's onExit function is run.
			 */
			void processingAfterOnExit();
			
		protected:

			Workflow* const q_ptr;
		};		
	}
}
#endif
