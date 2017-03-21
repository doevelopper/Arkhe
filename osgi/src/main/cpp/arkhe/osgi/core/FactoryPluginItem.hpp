#ifndef ARKHE_OSGI_FACTORYPLUGINITEM_HPP
#define ARKHE_OSGI_FACTORYPLUGINITEM_HPP

#include <QFileInfo>
#include <QPluginLoader>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFactoryFileBasedItem.hpp>

/*!
 * @brief .
 */
namespace osgi
{

	template<typename BaseClassType>
	class FactoryPluginItem : public AbstractFactoryFileBasedItem<BaseClassType>
	{
	public:
        FactoryPluginItem();
        virtual ~FactoryPluginItem();
        
        virtual bool load();
        virtual QString loadErrorString()const;

	protected:

        virtual BaseClassType* instanciator();

	private:

        QPluginLoader    Loader;

	};
		
}
#endif
