#ifndef ARKHE_OSGI_WORKFLOW_INTER_STEPTRANSITIONEVENT_HPP
#define ARKHE_OSGI_WORKFLOW_INTER_STEPTRANSITIONEVENT_HPP

#include <QEvent>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT WorkflowInterstepTransitionEvent : public QEvent
		{
		public:

			WorkflowInterstepTransitionEvent();
			virtual ~WorkflowInterstepTransitionEvent();
			
			WorkflowInterstepTransitionEvent(int newTransitionType);
			WorkflowInterstepTransitionEvent(int newTransitionType, const QString& newId);

			static inline int getWorkflowInterstepTransitionEventType();

			int     EventTransitionType;
			QString EventId;
		protected:


		private:

		};		
	}
}
#endif
