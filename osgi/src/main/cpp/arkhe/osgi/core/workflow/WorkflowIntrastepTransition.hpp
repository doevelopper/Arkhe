#ifndef ARKHE_OSGI_WORKFLOW_INTRA_STEPTRANSITION_HPP
#define ARKHE_OSGI_WORKFLOW_INTRA_STEPTRANSITION_HPP

#include <QAbstractTransition>
#include <QEvent>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT WorkflowIntrastepTransition : public QAbstractTransition
		{

		  Q_OBJECT

		public:
			enum IntrastepTransitionType
			{
				ValidationTransition = 0,
				ValidationFailedTransition
			};
			WorkflowIntrastepTransition();
			WorkflowIntrastepTransition(IntrastepTransitionType newTransitionType);
			virtual ~WorkflowIntrastepTransition();

			IntrastepTransitionType transitionType();
		protected:
			virtual bool eventTest(QEvent* e);
			void onTransition(QEvent*);

		private:
			IntrastepTransitionType TransitionType;
		};		
	}
}
#endif
