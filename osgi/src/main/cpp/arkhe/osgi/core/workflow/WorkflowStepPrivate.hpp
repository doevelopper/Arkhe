#ifndef ARKHE_OSGI_WORKFLOWSTEPPRIVATE_HPP
#define ARKHE_OSGI_WORKFLOWSTEPPRIVATE_HPP

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/workflow/WorkflowInterstepTransition.hpp>
#include <arkhe/osgi/core/workflow/WorkflowIntrastepTransition.hpp>

#include <QObject>
#include <QPointer>

class QString;
class QState;


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class WorkflowStep;
		class Workflow;

		class ARKHE_CORE_EXPORT WorkflowStepPrivate : public QObject
		{
			Q_OBJECT
			Q_DECLARE_PUBLIC(WorkflowStep);
		public:

			
			WorkflowStepPrivate();
			WorkflowStepPrivate(WorkflowStep& object);
			virtual ~WorkflowStepPrivate();

			WorkflowStep* q_ptr;

		protected:

			Workflow* _workflow;

			bool WidgetType;

			QString      Id;
			QString      Name;
			QString      Description;
			QString      StatusText;

			QPointer<QState> ProcessingState;
			QPointer<QState> ValidationState;

			WorkflowIntrastepTransition* ValidationTransition;
			WorkflowIntrastepTransition* ValidationFailedTransition;

			bool HasValidateCommand;
			bool HasOnEntryCommand;
			bool HasOnExitCommand;

			void invokeValidateCommandInternal(const QString& desiredBranchId)const;
			void validationCompleteInternal(bool validationSuceeded, const QString& branchId)const;
			void invokeOnEntryCommandInternal(const WorkflowStep* comingFrom, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const;
			void onEntryCompleteInternal()const;
			void invokeOnExitCommandInternal(const WorkflowStep* goingTo, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const;
			void onExitCompleteInternal()const;

		Q_SIGNALS:

			void invokeValidateCommand(const QString& desiredBranchId)const;
			void validationComplete(bool validationSuceeded, const QString& branchId)const;
			void invokeOnEntryCommand(const WorkflowStep* comingFrom, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const;
			void onEntryComplete()const;
			void invokeOnExitCommand(const WorkflowStep* goingTo, const WorkflowInterstepTransition::InterstepTransitionType transitionType)const;
			void onExitComplete()const;

		private:

			friend class WorkflowPrivate;
		};		
	}
}
#endif
