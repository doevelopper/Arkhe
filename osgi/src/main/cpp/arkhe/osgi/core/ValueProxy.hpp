#ifndef ARKHE_OSGI_VALUEPROXY_HPP
#define ARKHE_OSGI_VALUEPROXY_HPP

#include <QDebug>
#include <QObject>
#include <QScopedPointer>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT ValueProxy : public QObject
		{
			Q_OBJECT

			  /*! The value holds the current value. If the value proxy is
			  
			  /// considered as a function, then this function applied to the value is
			  /// the proxy value.
			  /// The value is updated if the proxy value is changed.
			  */
			Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

			  /// The proxy value holds the value transformed. If the value proxy is
			  /// considered as a function, then the proxy value is the result of
			  /// this function applied to value.
			  /// The proxy value is updated if the value is changed.
			Q_PROPERTY(double proxyValue READ proxyValue WRITE setProxyValue NOTIFY proxyValueChanged)

		public:

				class ARKHE_CORE_EXPORT ValueProxyPrivate
				{
					Q_DECLARE_PUBLIC(ValueProxy);

				public:
				  ValueProxy* q_ptr;
				  ValueProxyPrivate(ValueProxy& object);
				  virtual ~ValueProxyPrivate();

				  double Value;
				  double ProxyValue;
				};

			using Superclass = QObject;

			explicit ValueProxy(QObject* parent = 0);
			virtual ~ValueProxy();

			virtual double proxyValueFromValue(double value) const = 0;
			virtual double valueFromProxyValue(double proxyValue) const = 0;

			double value() const;
			virtual double proxyValue() const;

		public Q_SLOTS:

			void setValue(double newValue);
			void setProxyValue(double newProxyValue);

		Q_SIGNALS:

			void valueChanged(double);
			void proxyValueChanged(double);

			void proxyAboutToBeModified();
			void proxyModified();

		protected:

			QScopedPointer<ValueProxyPrivate> d_ptr;

			/// Utilities function for subclasses.
			/// Can be called to update the value/proxyValue from the proxyValue/value.
			void updateProxyValue();
			void updateValue();

		private:

			Q_DECLARE_PRIVATE(ValueProxy);
			Q_DISABLE_COPY(ValueProxy);
		};
	}
}
#endif
