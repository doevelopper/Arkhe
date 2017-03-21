#ifndef ARKHE_OSGI_ABSTRACTPLUGINFACTORY_HPP
#define ARKHE_OSGI_ABSTRACTPLUGINFACTORY_HPP

#include <QFileInfo>
#include <QPluginLoader>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFileBasedFactory.hpp>

/*!
 * @brief .
 */
namespace osgi
{

	template<typename BaseClassType>
	class AbstractPluginFactory : public AbstractFileBasedFactory<BaseClassType>
	{
	public:
        AbstractPluginFactory();
        virtual ~AbstractPluginFactory();

	protected:

        virtual bool isValidFile(const QFileInfo& file)const;
        virtual AbstractFactoryItem<BaseClassType>* createFactoryFileBasedItem();

	private:

  	};
		
}
#endif
