#ifndef ARKHE_OSGI_FACTORYOBJECTITEM_HPP
#define ARKHE_OSGI_FACTORYOBJECTITEM_HPP

#include <QFileInfo>
#include <QLibrary>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFactoryItem.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core 
	{
		template<typename BaseClassType, typename ClassType>
		class FactoryObjectItem : public AbstractFactoryItem<BaseClassType>
		{
		public:
			FactoryObjectItem();
			virtual ~FactoryObjectItem();
			virtual bool load();
		protected:
			typedef BaseClassType *(*InstantiateObjectFunc)();
			virtual BaseClassType* instanciator();
		private:
			InstantiateObjectFunc instantiateObjectFunc;
		};
	}
}
#endif