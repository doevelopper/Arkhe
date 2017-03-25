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

		protected:

			
		protected:
			QScopedPointer<osgi::core::WorkflowStepPrivate> d_ptr;

		private:

		};		
	}
}
#endif
