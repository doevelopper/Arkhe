#include <arkhe/osgi/core/BooleanMapper.hpp>

osgi::core::BooleanMapperPrivate::BooleanMapperPrivate()
{
  this->TrueValue = QVariant(true);
  this->FalseValue = QVariant(false);
}

osgi::core::BooleanMapper::BooleanMapper(QObject* targetObject, const QByteArray& property, const char* signal)
  : QObject(targetObject)
  , d_ptr(new BooleanMapperPrivate)
{
    Q_ASSERT(property.isEmpty() != true);
    Q_ASSERT(targetObject != 0);
    Q_D(BooleanMapper);
    d->PropertyName = property;
    if (signal)
    {
        connect(targetObject, signal, this, SLOT(emitValueChanged()));
    }
}

osgi::core::BooleanMapper::~BooleanMapper()
{
}

QByteArray osgi::core::BooleanMapper::propertyName()const
{
    Q_D(const BooleanMapper);
    return (d->PropertyName);
}

QObject* osgi::core::BooleanMapper::targetObject()const
{
    return (this->parent());
}

QVariant osgi::core::BooleanMapper::trueValue()const
{
    Q_D(const BooleanMapper);
    return (d->TrueValue);
}

QVariant osgi::core::BooleanMapper::falseValue()const
{
    Q_D(const BooleanMapper);
    return (d->FalseValue);
}

void osgi::core::BooleanMapper::setTrueValue(const QVariant& trueValue)
{
    Q_D(BooleanMapper);
    if (d->TrueValue == trueValue)
    {
        return;
    }

    d->TrueValue = trueValue;
    this->emitValueAsChanged();
}

void osgi::core::BooleanMapper::setFalseValue(const QVariant& falseValue)
{
    Q_D(BooleanMapper);
    if (d->FalseValue == falseValue)
    {
        return;
    }

    d->FalseValue = falseValue;
    this->emitValueAsChanged();
}

bool osgi::core::BooleanMapper::value()const
{
    return (this->targetObject()->property(this->propertyName()).toBool());
}

bool osgi::core::BooleanMapper::complement()const
{
    return (!this->value());
}

int osgi::core::BooleanMapper::valueAsInt()const
{
    Q_D(const BooleanMapper);
    return (this->value() ? d->TrueValue.toInt() : d->FalseValue.toInt());
}

QString osgi::core::BooleanMapper::valueAsString()const
{
    Q_D(const BooleanMapper);
    return (this->value() ? d->TrueValue.toString() : d->FalseValue.toString());
}

void osgi::core::BooleanMapper::setValue(bool value)
{
    this->targetObject()->setProperty(this->propertyName(), QVariant(value));
}

void osgi::core::BooleanMapper::setComplement(bool value)
{
    this->setValue(!value);
}

void osgi::core::BooleanMapper::setValueAsInt(int intValue)
{
    Q_D(BooleanMapper);
    this->setValue( QVariant(intValue) == d->TrueValue);
}

void osgi::core::BooleanMapper::setValueAsString(const QString& stringValue)
{
    Q_D(BooleanMapper);
    this->setValue( QVariant(stringValue) == d->TrueValue );
}

void osgi::core::BooleanMapper::toggle()
{
    this->setValue(this->complement());
}

void osgi::core::BooleanMapper::emitValueChanged()
{
    emit valueChanged(this->value());
    emit complementChanged(this->complement());
    this->emitValueAsChanged();
}

void osgi::core::BooleanMapper::emitValueAsChanged()
{
    emit valueAsIntChanged(this->valueAsInt());
    emit valueAsStringChanged(this->valueAsString());
}
