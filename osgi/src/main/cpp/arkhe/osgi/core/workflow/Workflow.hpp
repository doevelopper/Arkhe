#ifndef ARKHE_OSGI_WORKFLOW_HPP
#define ARKHE_OSGI_WORKFLOW_HPP

#include <QDebug>
#include <QStateMachine>
#include <QState>
#include <QQueue>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class WorkflowStep;
		class WorkflowPrivate;
		class QAbstractState;

		class ARKHE_CORE_EXPORT Workflow : public QObject
		{
			Q_OBJECT
			Q_ENUMS(TransitionDirectionality)
			Q_PROPERTY(bool isRunning READ isRunning DESIGNABLE false)
			Q_PROPERTY(bool goBackToOriginStepUponSuccess READ goBackToOriginStepUponSuccess WRITE setGoBackToOriginStepUponSuccess)
			Q_PROPERTY(bool verbose READ verbose WRITE setVerbose)

		public:

			using Superclass = QObject ;

			explicit Workflow(QObject* parent = 0);
			virtual ~Workflow();

			Q_INVOKABLE virtual void start();
			bool isRunning()const;
			Q_INVOKABLE virtual void stop();

			enum TransitionDirectionality
			{
				Bidirectional = 0,
				Forward,
				Backward
			};

			Q_INVOKABLE virtual bool addTransition(WorkflowStep* origin, WorkflowStep* destination,
                                         const QString& branchId = QString(),
                                         const Workflow::TransitionDirectionality directionality
                                         = Workflow::Bidirectional);

			Q_INVOKABLE bool hasTransition(WorkflowStep* origin, WorkflowStep* destination,
                                 const QString& branchId = QString(),
                                 const Workflow::TransitionDirectionality directionality
                                 = Workflow::Bidirectional);
								 
			Q_INVOKABLE WorkflowStep* initialStep()const;
			Q_INVOKABLE virtual void setInitialStep(WorkflowStep* step);
			Q_INVOKABLE WorkflowStep* currentStep()const;
			Q_INVOKABLE bool hasStep(const QString& id)const;
			Q_INVOKABLE WorkflowStep* step(const QString& id)const;
			Q_INVOKABLE bool canGoForward(WorkflowStep* step=0)const;
			Q_INVOKABLE bool canGoBackward(WorkflowStep* step=0)const;
			Q_INVOKABLE bool canGoToStep(const QString& targetId, WorkflowStep* step=0)const;
			Q_INVOKABLE QList<WorkflowStep*> forwardSteps(WorkflowStep* step=0)const;
			Q_INVOKABLE QList<WorkflowStep*> backwardSteps(WorkflowStep* step=0)const;
			Q_INVOKABLE QList<WorkflowStep*> finishSteps()const;
			Q_INVOKABLE QList<WorkflowStep*> steps()const;
			Q_INVOKABLE int backwardDistanceToStep(WorkflowStep* fromStep = 0, WorkflowStep* origin = 0)const;

			bool goBackToOriginStepUponSuccess()const;
			void setGoBackToOriginStepUponSuccess(bool flag);

			bool verbose()const;
			void setVerbose(bool value);

		public Q_SLOTS:

			/*! 
			 * @brief Use this to trigger evaluation of the processing state of the current step, and subsequent
			 *        conditional transition to the next step.
			 */
			virtual void goForward(const QString& desiredBranchId = QString());

			/*! 
			 * @brief Use this to trigger transition to the previous step (does not require validation)
			 */
			virtual void goBackward(const QString& desiredBranchId = QString());

			/*! 
			 * @brief Go to the given step by iteratively calling goForward() until we reach it.
			 */
			virtual void goToStep(const QString& targetId);

			/*! 
			 * @brief Receives the result of a step's validate(const QString&) function.
             *        If the validation is successful, then this slot begins the transition to the next step.
			 */
			virtual void evaluateValidationResults(bool validationSucceeded, const QString& branchId);
  
		protected:

			void goToNextStepAfterSuccessfulValidation(const QString& branchId);

			void goToProcessingStateAfterValidationFailed();

			/*! 
			 * @brief Processing that occurs after the attempt to go to a 'goTo' step succeeds
			 */
			virtual void goToStepSucceeded();

			/*! 
			 * @brief Processing that occurs after the attempt to go to a 'goTo' step fails
			 */
			virtual void goToStepFailed();

			/*! 
			 * @brief Goes to the step from which the attempt to go to the 'goTo' step was initiated
			 */
			void goFromGoToStepToStartingStep();

		protected Q_SLOTS:

			/*! 
			 * @brief On an attempt to go to the next step, calls the current step's
			 *        validate(const QString&) function to validate the processing step.
			 */
			void attemptToGoToNextStep();

			/*! 
			 * @brief Called when transitioning to the next step upon successful validation, or
			 *		  when transitioning to the previous step.
			 *        Calls onExit() of the transition's origin step and then onEntry() of
			 *        the transition's destination step.
			 * @note  Must be sent by a WorkflowTransition.
			 */

			void performTransitionBetweenSteps();

		Q_SIGNALS:
		   /*! 
			* @brief Emitted when the current step has changed, after the step's onEntry() has completed.
			* @note This signal is not emitted in the process of going to a goToStep
			*/
			void currentStepChanged(WorkflowStep* currentStep);

			/*! 
			 * @brief Emitted when a step is registered with this workflow
			 * @sa addTransition
			 */
			void stepRegistered(WorkflowStep* step);
  
		protected:

			QScopedPointer<WorkflowPrivate> d_ptr;

		private:

			Q_DECLARE_PRIVATE(Workflow);
			Q_DISABLE_COPY(Workflow);
		};		
	}
}
#endif
