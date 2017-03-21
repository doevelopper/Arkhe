#include <arkhe/osgi/core/workflow/ForwardAndBackwardSteps.hpp>

osgi::core::ForwardAndBackwardSteps::ForwardAndBackwardSteps()
{
}

osgi::core::ForwardAndBackwardSteps::~ForwardAndBackwardSteps()
{
}

QList<osgi::core::WorkflowStep*> osgi::core::ForwardAndBackwardSteps::forwardSteps()
{
	return this->ForwardSteps;
}

QList<osgi::core::WorkflowStep*> osgi::cor::ForwardAndBackwardStepse::backwardSteps()
{
    return this->BackwardSteps;
}

QList<QString> osgi::core::ForwardAndBackwardSteps::forwardBranchIds()
{
    return this->ForwardBranchIds;
}

QList<QString> osgi::core::ForwardAndBackwardSteps::backwardBranchIds()
{
    return this->BackwardBranchIds;
}

void osgi::core::ForwardAndBackwardSteps::appendForwardStep(WorkflowStep* step, QString id)
{
    this->ForwardSteps.append(step);
    this->ForwardBranchIds.append(id);
}

void osgi::core::ForwardAndBackwardSteps::appendBackwardStep(WorkflowStep* step, QString id)
{
    this->BackwardSteps.append(step);
    this->BackwardBranchIds.append(id);
}

QString osgi::core::ForwardAndBackwardSteps::firstForwardBranchId()
{
    if (this->ForwardBranchIds.isEmpty())
	{
		return QString();
    }
    else
    {
		return this->ForwardBranchIds.first();
    }
}

osgi::core::WorkflowStep* osgi::core::ForwardAndBackwardSteps::forwardStep(QString branchId)
{
    int index = this->ForwardBranchIds.indexOf(branchId);
    if (index != -1)
    {
		return ForwardSteps.at(index);
    }
    else
    {
		return 0;
    }
}

QString osgi::core::ForwardAndBackwardSteps::backwardBranchId(WorkflowStep* step)
{
    int index = this->BackwardSteps.indexOf(step);

    if (index != -1)
	{
		return BackwardBranchIds.at(index);
	}
    else
    {
		return QString();
	}
}

QString osgi::core::ForwardAndBackwardSteps::forwardBranchId(WorkflowStep* step)
{
    int index = this->ForwardSteps.indexOf(step);

    if (index != -1)
	{
		return ForwardBranchIds.at(index);
    }
    else
    {
		return QString();
    }
}