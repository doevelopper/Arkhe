#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEEXCEPTION_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEEXCEPTION_HPP

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
		class ARKHE_CORE_PLUGIN_FW_EXPORT ServiceException
		{

		public:
			ServiceException();
			virtual ~ServiceException();
		protected:

		private:

		};		
	}
}
#endif
