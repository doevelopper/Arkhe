#ifndef ARKHE_OSGI_CORE_FRAMEWORK_RUNNABLE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_RUNNABLE_HPP

#include <QDebug>
#include <arkhe/osgi/osgi.hpp>

class QVariant;
/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT Runnable
		{

		public:
			Runnable();
			virtual ~Runnable();
			virtual QVariant run(const QVariant& context) = 0;
			virtual void stop() = 0;
		protected:

		private:

		};		
	}
}
#endif
