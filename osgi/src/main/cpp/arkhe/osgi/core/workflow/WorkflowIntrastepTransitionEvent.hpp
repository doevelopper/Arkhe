#ifndef ARKHE_OSGI_WORKFLOW_INTRA_STEPTRANSITIONEVENT_HPP
#define ARKHE_OSGI_WORKFLOW_INTRA_STEPTRANSITIONEVENT_HPP

#include <QEvent>

#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT WorkflowIntrastepTransitionEvent : public QEvent
		{
		public:
			WorkflowIntrastepTransitionEvent(int newTransitionType);
			static inline int getWorkflowIntrastepTransitionEventType();
			int EventTransitionType;

		protected:

		private:

		};		
	}
}
#endif
