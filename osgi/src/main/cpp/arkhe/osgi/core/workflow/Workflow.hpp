#ifndef ARKHE_OSGI_WORKFLOW_HPP
#define ARKHE_OSGI_WORKFLOW_HPP

#include <QDebug>
#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QScopedPointer>
#include <QQueue>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief Basis for a state machine with enhancements to support Work flow Step.
 */
namespace osgi
{
	namespace core
	{
		class WorkflowStep;
		class WorkflowPrivate;
		class QAbstractState;

		class ARKHE_CORE_EXPORT Workflow  : public QObject
		{
			Q_OBJECT
			Q_ENUMS(TransitionDirectionality)
			Q_PROPERTY(bool isRunning READ isRunning DESIGNABLE false)
			Q_PROPERTY(bool goBackToOriginStepUponSuccess READ goBackToOriginStepUponSuccess WRITE setGoBackToOriginStepUponSuccess)
			Q_PROPERTY(bool verbose READ verbose WRITE setVerbose)
		public:
			enum TransitionDirectionality
			{
				BIDIRECTIONAL = 0,
				FORWARD,
				BACKWARD
			};
			using Superclass = QObject;
			explicit Workflow(QObject* parent = 0);
			virtual ~Workflow();
			/*!
			 * @brief Start the workflow.
			 *        The workflow will always start in the initial step, even if it is stopped and restarted).
			 * @note  Calls onEntry() for the initial step.
			 */
			Q_INVOKABLE virtual void start();
			/*!
			 *	@brief Returns whether the workflow is currently running.
			 */
			bool isRunning()const;
			/*!
			 *	@brief Stops the workflow.
			 *  @note  Calls onExit() for the current step.
			 */
			Q_INVOKABLE virtual void stop();
			/*!
			 *	@brief Creates a transition between two steps, and adds the two steps to the workflow if they
			 *         have not been previously added. (Cannot add two steps with the same id).
			 *         The destination step should semantically be a next step, i.e. from a workflow perspective, the
			 *         @a destination step is meant to appear after the @a origin step.
			 *  @note  To add a single step, @a destination can be set to 0.
			 *  
			 * @retval TRUE   The method was successful.
			 * @retval FALSE  Oops, The method failed.
			 */
			Q_INVOKABLE virtual bool addTransition(WorkflowStep* origin, WorkflowStep* destination,
                                         const QString& branchId = QString(),
                                         const Workflow::TransitionDirectionality directionality = Workflow::BIDIRECTIONAL);
			/*!
			 *	@brief 	Determine whether a transition has already been added.
			 *			<ul>
			 *				<li>
			 *						If a branch id is not given or is empty: a transition exists if a transition has been
			 *						previously added with the same origin, destination and directionality
			 *				</li>
			 *				<li>
			 *						If a non-empty branch id is given: a transition exists if the transition has been previously
			 *	                    added with the same origin, destination and directionality, OR if a transition has been
			 *						previously added with the same origin and branch id (for forward transitions) or
			 *						with the same destination and branch id (for backward transitions)
			 *				</li>
			 *			</ul>
			 */
			Q_INVOKABLE bool hasTransition(WorkflowStep* origin, WorkflowStep* destination,
                                 const QString& branchId = QString(),
                                 const Workflow::TransitionDirectionality directionality = Workflow::BIDIRECTIONAL);
			/*!
			 *	@brief 	Set/get the initial step.
			 *	@note In not specified, the first step added will be considered as the initialStep
  			 *	@sa currentStep(), step(), hasStep(), steps()
			 */
			Q_INVOKABLE WorkflowStep* initialStep()const;
			Q_INVOKABLE virtual void setInitialStep(WorkflowStep* step);
			/*!
			 *	@brief Get the current step of the state machine.
  			 *	@sa currentStep(), step(), hasStep(), steps()
			 */
			Q_INVOKABLE WorkflowStep* currentStep() const;
			/*!
			 *	@brief Check to see if there is a step with a given id in the workflow.
  			 *	@sa currentStep(), step(), hasStep(), steps()
			 */
			Q_INVOKABLE bool hasStep(const QString& id) const; 
			/*!
			 *	@brief Return the step with Id.
  			 *	@sa currentStep(), step(), hasStep(), steps()
			 *  @retval Matching @a id if any.
			 *  @retval 0 otherwise.
			 */
			Q_INVOKABLE WorkflowStep* step(const QString& id) const;
			/*!
			 *	@brief  Returns whether or not we can go forward.
			 *  		If no step is given, then the workflow's current step will be used.
			 */
			Q_INVOKABLE bool canGoForward(WorkflowStep* step=0) const;
			/*!
			 *	@brief  Returns whether or not we can go backward.
			 *  		If no step is given, then the workflow's current step will be used.
			 */
			Q_INVOKABLE bool canGoBackward(WorkflowStep* step=0) const;
			/*!
			 *	@brief  Returns whether or not we can go to the goal step from the origin step.
			 *  		there is a path in the workflow from the current step to the given step.
			 *          If no step is designated as the 'origin', then the workflow's current step will be used.
			 *  @warn   Does not currently work in branching workflows if the origin and target steps are not on the same branch
			 */
			Q_INVOKABLE bool canGoToStep(const QString& targetId, WorkflowStep* step = 0) const;
			/*!
			 *	@brief  Get the steps that directly preceed the given step.
			 *  		The returned list of steps will be the origin steps for which
			 *			addTransition() has been called with the given step as the destination step and directionality
			 *			set to Workflow::Bidirectional or Workflow::Forward.
			 *  		If no step is given, then the workflow's current step will be used.
			 */
			Q_INVOKABLE QList<WorkflowStep*> forwardSteps(WorkflowStep* step=0)const;
			/*!
			 *	@brief  Get the steps that directly preceed the given step.
			 *  		The returned list of steps will be the origin steps for which
			 *			addTransition() has been called with the given step as the destination step and directionality
			 *			set to Workflow::Bidirectional or Workflow::Backward.
			 *  		If no step is given, then the workflow's current step will be used.
			 */
			Q_INVOKABLE QList<WorkflowStep*> backwardSteps(WorkflowStep* step=0)const;
			/*!
			 *	@brief  Get the steps that are 'finish' steps (i.e. have no step following them).
			 */
			Q_INVOKABLE QList<WorkflowStep*> finishSteps()const;
			/*!
			 *	@brief  Returns list of steps managed by the workflow.
			 */
			Q_INVOKABLE QList<WorkflowStep*> steps()const;
			/*!
			 *	@brief  Returns the distance of a given to step to another step.
			 */
			Q_INVOKABLE int backwardDistanceToStep(WorkflowStep* fromStep = 0, WorkflowStep* origin = 0) const;
			/*!
			 *	@brief  Configures the behavior of goToStep(targetId).
			 *          If set to true, goToStep(targetId) goes back to the origin step after
			 *          the attempt of going to the target step succeeded.
			 *          If set to false, goToStep(targetId) stays at the target step when the attempt succeeded.
			 */
			bool goBackToOriginStepUponSuccess()const;
			void setGoBackToOriginStepUponSuccess(bool flag);
			/*!
			 *	@brief  If set debug messages will be displayed on standard output.
			 */
			bool verbose()const;
			void setVerbose(bool value);

			// enum TransitionDirectionality
			// {
				// BIDIRECTIONAL = 0,
				// FORWARD,
				// BACKWARD
			// };

		public Q_SLOTS:
			/*!
			 *	@brief  Use this to trigger evaluation of the processing state of the current step, and subsequent
			 *          conditional transition to the next step.
			 */
			virtual void goForward(const QString& desiredBranchId = QString());
			/*!
			 *	@brief  Trigger transition to the previous step (does not require validation).
			 */
			virtual void goBackward(const QString& desiredBranchId = QString());
			/*!
			 *	@brief  Go to the given step by iteratively calling goForward() until we reach it.
			 */
			virtual void goToStep(const QString& targetId);
			/*!
			 *	@brief  Receives the result of a step's validate(const QString&) function.
			 *          If the validation is successful, then this slot begins the transition to the next step.
			 */
			virtual void evaluateValidationResults(bool validationSucceeded, const QString& branchId);

		protected:
			/*!
			 *	@brief  
			 */
			void goToNextStepAfterSuccessfulValidation(const QString& branchId);
			/*!
			 *	@brief 
			 */
			void goToProcessingStateAfterValidationFailed();
			/*!
			 *	@brief  Processing that occurs after the attempt to go to a 'goTo' step succeeds.
			 */
			virtual void goToStepSucceeded();
			/*!
			 *	@brief Processing that occurs after the attempt to go to a 'goTo' step fails.
			 */
			virtual void goToStepFailed();
			/*!
			 *	@brief  Goes to the step from which the attempt to go to the 'goTo' step was initiated.
			 */
			void goFromGoToStepToStartingStep();

		protected Q_SLOTS:
			/*!
			 *	@brief  On an attempt to go to the next step, calls the current step's
			 *          validate(const QString&) function to validate the processing step.
			 */
			void attemptToGoToNextStep();
			/*!
			 *	@brief  Called when transitioning to the next step upon successful validation, or
			 *          when transitioning to the previous step.
			 *          Calls onExit() of the transition's origin step and then onEntry() of
			 *          the transition's destination step.
			 *  @note   Must be sent by a WorkflowTransition.
			 */
			void performTransitionBetweenSteps();


		Q_SIGNALS:
			/*!
			 *	@brief  Emitted when the current step has changed, after the step's onEntry() has completed.
			 *  @note This signal is not emitted in the process of going to a goToStep.
			 */
			void currentStepChanged(WorkflowStep* currentStep);
			/*!
			 *	@brief  Emitted when a step is registered with this workflow.
			 *  @sa addTransition.
			 */
			void stepRegistered(WorkflowStep* step);

		protected:
			QScopedPointer<osgi::core::WorkflowPrivate> d_ptr;

		private:
			Q_DECLARE_PRIVATE(Workflow);
			Q_DISABLE_COPY(Workflow);
		};		
	}
}
#endif
