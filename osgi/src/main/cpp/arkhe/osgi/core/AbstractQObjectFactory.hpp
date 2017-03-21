#ifndef ARKHE_OSGI_ABSTRACTQOBJECTFACTORY_HPP
#define ARKHE_OSGI_ABSTRACTQOBJECTFACTORY_HPP

#include <QDebug>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractObjectFactory.hpp>

/*!
 * @brief .
 */
namespace osgi
{

	template<typename BaseClassType>
	class AbstractQObjectFactory : public AbstractObjectFactory<BaseClassType>
	{
	public:
        explicit AbstractQObjectFactory();
        virtual ~AbstractQObjectFactory();

        virtual QString objectNameToKey(const QString& objectName);

	protected:

	private:
        template<typename ClassType>
        bool registerQObject(QString& key);

        AbstractQObjectFactory(const AbstractQObjectFactory &);  /// Not implemented
        void operator=(const AbstractQObjectFactory&); /// Not implemented

	};
		
}
#endif
