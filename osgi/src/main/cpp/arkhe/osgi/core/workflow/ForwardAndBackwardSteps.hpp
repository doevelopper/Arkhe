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
			QList<WorkflowStep*> backwardSteps();
			QList<QString> forwardBranchIds();
			QList<QString> backwardBranchIds();
			void appendForwardStep(WorkflowStep* step, QString id);
			void appendBackwardStep(WorkflowStep* step, QString id);
			QString firstForwardBranchId();
			WorkflowStep* forwardStep(QString branchId);
			QString backwardBranchId(WorkflowStep* step);
			QString forwardBranchId(WorkflowStep* step);

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
