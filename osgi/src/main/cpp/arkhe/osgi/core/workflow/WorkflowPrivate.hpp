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
		class WorkflowPrivate
		{
			
		public:
			WorkflowPrivate();
			virtual ~WorkflowPrivate();
		protected:
		};		
	}
}
#endif
