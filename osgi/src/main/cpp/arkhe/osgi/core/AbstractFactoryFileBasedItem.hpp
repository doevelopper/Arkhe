#ifndef ARKHE_OSGI_ABSTRACTFACTORYFILEBASEDITEM_HPP
#define ARKHE_OSGI_ABSTRACTFACTORYFILEBASEDITEM_HPP

#include <QFileInfo>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFactoryItem.hpp>

/*!
 * @brief .
 */
namespace osgi
{

	template<typename BaseClassType>
	class AbstractFactoryFileBasedItem : public AbstractFactoryItem<BaseClassType>
	{
	public:
        AbstractFactoryFileBasedItem();
        virtual ~AbstractFactoryFileBasedItem();
        void path(const QString& path);
        QString path()const;
	protected:
	  
	private:
        QString  m_path;
	};
		
}
#endif