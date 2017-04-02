#ifndef ARKHE_OSGI_WORKFLOW_INTER_STEPTRANSITION_HPP
#define ARKHE_OSGI_WORKFLOW_INTER_STEPTRANSITION_HPP

#include <QAbstractTransition>
#include <QDebug>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT WorkflowInterstepTransition : public QAbstractTransition
		{
			Q_OBJECT
			Q_ENUMS(InterstepTransitionType)

		public:

			enum InterstepTransitionType
			{
				TransitionToNextStep = 0,
				TransitionToPreviousStep,
				StartingWorkflow,
				StoppingWorkflow,
				TransitionToPreviousStartingStepAfterSuccessfulGoToFinishStep
			};
			WorkflowInterstepTransition();
			virtual ~WorkflowInterstepTransition();
			WorkflowInterstepTransition(InterstepTransitionType newTransitionType);
			WorkflowInterstepTransition(InterstepTransitionType newTransitionType, const QString& newId);

			InterstepTransitionType transitionType();
			QString& id();

		protected:
			virtual bool eventTest(QEvent* e);
			void onTransition(QEvent*);

		private:
			InterstepTransitionType TransitionType;
			QString                 Id;

		};		
	}
}
#endif
