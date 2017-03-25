#ifndef ARKHE_OSGI_SERVICES_ATTRIBUTEDEFINITION_HPP
#define ARKHE_OSGI_SERVICES_ATTRIBUTEDEFINITION_HPP

#include <arkhe/osgi/osgi.hpp>



class ApplicationHandle;

/*!
 * @brief 
 * 
 */
namespace osgi
{
	namespace svc
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT AttributeDefinition
		{

		public:
			AttributeDefinition();
			virtual ~AttributeDefinition();
			virtual QString getApplicationId() const = 0;

		protected:

		private:
		};		
	}
}
#endif
