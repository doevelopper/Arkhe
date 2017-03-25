#ifndef ARKHE_OSGI_WORKFLOWSTEPPRIVATE_HPP
#define ARKHE_OSGI_WORKFLOWSTEPPRIVATE_HPP

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/workflow/WorkflowInterstepTransition.hpp>
#include <arkhe/osgi/core/workflow/WorkflowIntrastepTransition.hpp>

#include <QObject>
#include <QPointer>

class QString;
class QState;

class WorkflowStep;
class Workflow;

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT WorkflowStepPrivate
		{

		public:

			
			WorkflowStepPrivate();
			virtual ~WorkflowStepPrivate();

		protected:

		private:

		};		
	}
}
#endif
