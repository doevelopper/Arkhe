#ifndef ARKHE_OSGI_WORKFLOW_HPP
#define ARKHE_OSGI_WORKFLOW_HPP

#include <QDebug>
#include <QStateMachine>
#include <QState>
#include <QQueue>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class WorkflowStep;
		class WorkflowPrivate;
		class QAbstractState;

		class ARKHE_CORE_EXPORT Workflow
		{

		public:
			Workflow();
			virtual ~Workflow();
 
		protected:

		private:

		};		
	}
}
#endif
