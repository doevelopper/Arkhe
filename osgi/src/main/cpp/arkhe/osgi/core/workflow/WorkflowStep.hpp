#ifndef ARKHE_OSGI_WORKFLOWSTEP_HPP
#define ARKHE_OSGI_WORKFLOWSTEP_HPP

#include <QState>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/workflow/WorkflowInterstepTransition.hpp>
#include <arkhe/osgi/core/workflow/WorkflowIntrastepTransition.hpp>
#include <arkhe/osgi/core/workflow/WorkflowStepPrivate.hpp>
class Workflow;

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT WorkflowStep
		{
		public:

			explicit WorkflowStep();
			explicit WorkflowStep(const QString& newId);
			virtual ~WorkflowStep();

			Workflow* workflow()const;
			QString id()const;
			void setId(const QString& newStepId);
			QString name()const;
			void setName(const QString& newName);
			QString description()const;
			void setDescription(const QString& newDescription);
			QString statusText()const;
			bool hasValidateCommand()const;
			void setHasValidateCommand(bool newHasValidateCommand);
			bool hasOnEntryCommand()const;
			void setHasOnEntryCommand(bool newHasOnEntryCommand);
			bool hasOnExitCommand()const;
			void setHasOnExitCommand(bool newHasOnExitCommand);
			bool isWidgetType()const;
			QObject* WorkflowStepQObject();

		protected:

			explicit WorkflowStep(osgi::core::WorkflowStepPrivate * pimpl, const QString& newId);
			void setWorkflow(Workflow* newWorkflow);
			void setStatusText(const QString& newText);
			QState* processingState()const;
			QState* validationState()const;
			WorkflowIntrastepTransition* validationTransition()const;
			WorkflowIntrastepTransition* validationFailedTransition()const;
			virtual void onEntry(const WorkflowStep* comingFrom, const WorkflowInterstepTransition::InterstepTransitionType transitionType);
			virtual void onExit(const WorkflowStep* goingTo, const WorkflowInterstepTransition::InterstepTransitionType transitionType);
			virtual void validate(const QString& desiredBranchId = QString());
			void invokeValidateCommand(const QString& desiredBranchId = QString())const;
			void validationComplete(bool validationSuceeded, const QString& branchId = QString())const;
			void invokeOnEntryCommand(const WorkflowStep* comingFrom, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const;
			void invokeOnExitCommand(const WorkflowStep* goingTo, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const;
			void onEntryComplete()const;
			void onExitComplete()const;
			
		protected:
			QScopedPointer<WorkflowStepPrivate> d_ptr;

		private:
			Q_DECLARE_PRIVATE(WorkflowStep);
			Q_DISABLE_COPY(WorkflowStep);
			friend class Workflow;        // For access to processingState, validationState, setWorkflow, validate
			friend class WorkflowPrivate; // For access to invokeOn{Entry,Exit}Command, on{Entry,Exit}
		};		
	}
}
#endif
