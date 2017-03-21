#ifndef ARKHE_OSGI_FORWARD_AND_BACKWARDSTEPS_HPP
#define ARKHE_OSGI_FORWARD_AND_BACKWARDSTEPS_HPP

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/workflow/WorkflowStep.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT ForwardAndBackwardSteps
		{
		public:

			ForwardAndBackwardSteps();
			virtual ~ForwardAndBackwardSteps();
			
			QList<WorkflowStep*> forwardSteps();
			QString forwardBranchId(WorkflowStep* step);
			QString backwardBranchId(WorkflowStep* step);
			WorkflowStep* forwardStep(QString branchId);
			QString firstForwardBranchId();
			QList<QString> backwardBranchIds();
			QList<QString> forwardBranchIds();
			void appendBackwardStep(WorkflowStep* step, QString id);
			void appendForwardStep(WorkflowStep* step, QString id);
			QList<WorkflowStep*> backwardSteps();

		protected:


		private:
			QList<WorkflowStep*> ForwardSteps;
			QList<WorkflowStep*> BackwardSteps;

			QList<QString> ForwardBranchIds;
			QList<QString> BackwardBranchIds;
		};		
	}
}
#endif
