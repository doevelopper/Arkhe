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
			WorkflowPrivate(Workflow& object);
			virtual ~WorkflowPrivate();
		  /*! 
		   *  @brief Add a step to the workflow
		   *  @note The step's components will be automatically be added to the state machine
		   *         (i.e. the processingState state, validationState state, validationTransition transition
		   *          and validationFailedtransition transition.
		   * @return True or False indicating whether the method was successful.
		   */
			bool addStep(WorkflowStep* step);
			
			/*! @brief Returns whether a transition has been previously added with the same origin,
			 *	       destination and directionality
			 */
			bool hasDuplicateTransition(WorkflowStep* origin, WorkflowStep* destination,
                              const Workflow::TransitionDirectionality directionality);

		  /*! 
		   *  @brief brief Returns whether a transition has been previously added with the same origin and branch
		   *         id (for forward transitions) or with the same destination and branch id (for backward transitions
		   */
			bool hasTransitionWithSameBranchId(WorkflowStep* origin, WorkflowStep* destination,
                                     const QString& branchId,
                                     const Workflow::TransitionDirectionality directionality);

		  /*! 
		   *  @brief Creates a transition from the origin to the destinatio.
		   *         More specifically, the transition is from the @a origin's validation state to the @a
		   *         destination's processing state, and is of type WorkflowTransition::TransitionToNextStep
		   *        The destination step should semantically be a next step, i.e. from a workflow perspective, the
		   *        @a destination step is meant to appear after the @a origin step.
           * Returns true/false indicating whether the method was successful.
		   */
			void createTransitionToNextStep(WorkflowStep* origin,
                                  WorkflowStep* destination,
                                  const QString& branchId = "");

		  /*! 
		   *  @brief Creates a transition from the destination to the origin
		  /// More specifically, the transition is from the \a destination's processing state to the \a
		  /// origin's processing state, and is of type WorkflowTransition::TransitionToPreviousStep
		  ///
		  /// The destination step should semantically be a next step, i.e. from a workflow perspective, the
		  /// \a destination step is meant to appear after the \a origin step.
		  ///
		  /// Returns true/false indicating whether the method was successful.
		  */
			void createTransitionToPreviousStep(WorkflowStep* origin,
                                      WorkflowStep* destination,
                                      const QString& branchId = "");
									  
		  /// \brief Creates a transition from the goTo step to the step from which the attempt to go to the
		  /// goTo step was initiated.
		  ///
		  /// More specifically, the transition is from the \a goTo step's processing state to the \a
		  /// starting step's processing state, and is of type WorkflowTransition::TransitionToPreviousStartingStep
		  ///
		  /// Returns true/false indicating whether the method was successful.
			void createTransitionToPreviousStartingStep(WorkflowStep* startingStep,
													  WorkflowStep* currentStep);
			///
			void validateInternal(WorkflowStep* step);

			/// \brief Performs computation required when entering this step.
			/// Does some sanity checks and then either calls onEntry() or emits the invokeOnEntryCommand(),
			/// depending on whether the user indicates that there is an onEntryCommand.
			void onEntryInternal(WorkflowStep* step, WorkflowStep* comingFrom,
                       const WorkflowInterstepTransition::InterstepTransitionType& transitionType);
					   
			  /// \brief Performs computation required when exiting this step.
			  ///
			  /// Does some sanity checks and then either calls onExit() or emits the invokeOnExitCommand(),
			  /// depending on whether the user indicates that there is an onExitCommand.
			void onExitInternal(WorkflowStep* step, WorkflowStep* goingTo,
                      const WorkflowInterstepTransition::InterstepTransitionType& transitionType);

			/*! 
		    *  @brief Get the step in the workflow with a given id.
		    */
			WorkflowStep* stepFromId(const QString& id)const;

			/*! 
		    *  @brief Get the step that a state belongs to (if any)
		    */
			WorkflowStep* stepFromState(const QAbstractState* state);

			/*! 
		    *  @brief Get the number of forward steps from the given step
		    */
			int numberOfForwardSteps(WorkflowStep* step);

			/*! 
		    *  @brief Get the number of backward steps from the given step
		    */
			int numberOfBackwardSteps(WorkflowStep* step);

			/*! 
		    *  @brief Get the ids of the steps that directly follow the given step.
		    */
			QList<QString> forwardBranchIds(WorkflowStep* step)const;

			/*! 
		    *  @brief Get the ids of the steps that directly preceed the given step.
		    */
			QList<QString> backwardBranchIds(WorkflowStep* step)const;

			/*! 
		    *  @brief Determines whether there exists a path from the origin step (the current step by default) to
			*         the step with the given goalId
		    */
			bool pathExists(const QString& goalId, WorkflowStep* origin = 0)const;

			/*! 
		    *  @brief Determines whether there exists a path from the current step's next step (as given by the
            *         branchId) to the step with the given goalId
		    */
			bool pathExistsFromNextStep(const QString& goalId, const QString& branchId)const;

		public Q_SLOTS:

			/*! 
		    *  @brief Workflow processing executed after a step's onEntry function is run.
			*/
			void processingAfterOnEntry();

			/*! 
		    *  @brief Workflow processing executed after a step's onExit function is run.
			*/
			void processingAfterOnExit();

		protected:

			Workflow* const q_ptr;
			
		public:

			QStateMachine* StateMachine;

			// Maintain a list of pointers to the steps in the workflow,
			// along with their forward and backward transitions
			QMap<WorkflowStep*, ForwardAndBackwardSteps*>         StepToForwardAndBackwardStepMap;

			// ... and its associated convenient typedef
			using StepToForwardAndBackwardStepMapType = QMap<WorkflowStep*, ForwardAndBackwardSteps*> ;
			using StepListType = QList<WorkflowStep*>;

			// Register a list of pointers to the steps in the worflow for cleaning purpose
			StepListType RegisteredSteps;

			// Maintain a map of <state, step> key/value pairs, to find the step
			// that a given state belongs to
			using StateToStepMapType = QMap<const QAbstractState*, WorkflowStep*> ;
			using StateToStepMapIterator = QMap<const QAbstractState*, WorkflowStep*>::iterator;

			StateToStepMapType StateToStepMap;

			WorkflowStep* InitialStep;
			WorkflowStep* CurrentStep;
			QMap<WorkflowStep*, WorkflowStep*> StepToPreviousStepMap;

			// Used when performing a transition
			WorkflowStep*  OriginStep;
			WorkflowStep*  DestinationStep;
			WorkflowInterstepTransition::InterstepTransitionType TransitionType;

			QString          DesiredBranchId; // Desired branchId specified when invoking goForward

			WorkflowStep* GoToStep;   // Desired step when attempting to go to a finish step

			WorkflowStep* StartingStep; // Current step when we began the attempt to go to the desired finish step

			// Temporary transition after successfully going to finish step, to get us back to the starting step
			WorkflowInterstepTransition* TransitionToPreviousStartingStep;

			bool GoBackToOriginStepUponSuccess;

			QString ARTIFICIAL_BRANCH_ID_PREFIX;
			bool Verbose;
		};		
	}
}
#endif
