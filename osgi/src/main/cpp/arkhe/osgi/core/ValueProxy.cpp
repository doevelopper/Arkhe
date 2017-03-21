#include <arkhe/osgi/core/ValueProxy.hpp>

osgi::core::ValueProxy::ValueProxyPrivate::ValueProxyPrivate(ValueProxy& object)
  : q_ptr(&object)
{
	this->Value = 0.0;
	this->ProxyValue = 0.0;
}

osgi::core::ValueProxy::ValueProxyPrivate::~ValueProxyPrivate()
{
}

osgi::core::ValueProxy::ValueProxy(QObject* _parent) 
: Superclass(_parent)
, d_ptr(new ValueProxyPrivate(*this))
{
}

osgi::core::ValueProxy::~ValueProxy()
{
}

double osgi::core::ValueProxy::value() const
{
	Q_D(const ValueProxy);
	return d->Value;
}

void osgi::core::ValueProxy::setValue(double newValue)
{
	Q_D(ValueProxy);
	if (d->Value == newValue)
    {
		return;
    }

  d->Value = newValue;
  emit this->valueChanged(d->Value);
  this->updateProxyValue();
}

double osgi::core::ValueProxy::proxyValue() const
{
  Q_D(const ValueProxy);
  return d->ProxyValue;
}

void osgi::core::ValueProxy::setProxyValue(double newProxyValue)
{
	Q_D(ValueProxy);
	if (d->ProxyValue == newProxyValue)
    {
		return;
    }

	d->ProxyValue = newProxyValue;
	emit this->proxyValueChanged(d->ProxyValue);
	this->updateValue();
}

void osgi::core::ValueProxy::updateProxyValue()
{
	Q_D(ValueProxy);
	double newProxyValue = this->proxyValueFromValue(d->Value);
	if (newProxyValue == d->ProxyValue)
    {
		return;
    }

	d->ProxyValue = newProxyValue;
	emit this->proxyValueChanged(d->ProxyValue);
}

void osgi::core::ValueProxy::updateValue()
{
	Q_D(ValueProxy);
	double newValue = this->valueFromProxyValue(d->ProxyValue);

	if (newValue == d->Value)
    {
		return;
    }

	d->Value = newValue;
	emit this->valueChanged(d->Value);
}
