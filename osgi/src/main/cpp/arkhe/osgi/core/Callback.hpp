#ifndef ARKHE_OSGI_CALLBACK_HPP
#define ARKHE_OSGI_CALLBACK_HPP

#include <QObject>
#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core 
	{

		class ARKHE_CORE_EXPORT Callback : public QObject
		{
			Q_OBJECT
		public:
			Callback(QObject * parentObject = 0);
			Callback(void (*callback)(void * data), QObject * parentObject = 0);
			virtual ~Callback();

			void (*callback()const)(void*);
			void setCallback(void (*callback)(void * data));
			void * callbackData() const;
			void setCallbackData(void * data);

		public Q_SLOTS:

			virtual void invoke();

		protected:

		private:
			void (*aCallback)(void * data);
			void * CallbackData;
		};
	}
		
}
#endif
