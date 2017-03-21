#ifndef ARKHE_OSGI_BOOLEANMAPPER_HPP
#define ARKHE_OSGI_BOOLEANMAPPER_HPP

#include <QDebug>
#include <QObject>
#include <QVariant>

#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
    class BooleanMapperPrivate
    {
    public:
        BooleanMapperPrivate();
        QByteArray PropertyName;
        QVariant TrueValue;
        QVariant FalseValue;
    };

	class ARKHE_CORE_EXPORT BooleanMapper : public QObject
	{
        Q_OBJECT

        Q_PROPERTY(QByteArray propertyName READ propertyName)

        Q_PROPERTY(bool value READ value WRITE setValue NOTIFY complementChanged STORED false);

        Q_PROPERTY(bool complement READ complement WRITE setComplement NOTIFY complementChanged STORED false)

        Q_PROPERTY(int valueAsInt READ valueAsInt WRITE setValueAsInt NOTIFY valueAsIntChanged STORED false )

        Q_PROPERTY(QString valueAsString READ valueAsString WRITE setValueAsString NOTIFY valueAsStringChanged STORED false )

        Q_PROPERTY(QVariant trueValue READ trueValue WRITE setTrueValue )

        Q_PROPERTY(QVariant falseValue READ falseValue WRITE setFalseValue )

	public:
        BooleanMapper(QObject* targetObject, const QByteArray& propertyName, const char* signal);
        virtual ~BooleanMapper();

        QByteArray propertyName()const;
        QObject* targetObject()const;

        bool value()const;
        bool complement()const;
        int valueAsInt()const;
        QString valueAsString()const;
        QVariant trueValue()const;
        QVariant falseValue()const;
      
        void setTrueValue(const QVariant& value);
        void setFalseValue(const QVariant& value);
        
        public Q_SLOTS:

          void setValue(bool value);
          void setComplement(bool complement);
          void setValueAsInt(int value);
          void setValueAsString(const QString& value);

          void toggle();

        Q_SIGNALS:

          void valueChanged(bool value);
          void complementChanged(bool complement);
          void valueAsIntChanged(int value);
          void valueAsStringChanged(const QString& value);

        protected Q_SLOTS:

          void emitValueChanged();
          void emitValueAsChanged();
        
        protected:
          QScopedPointer<BooleanMapperPrivate> d_ptr;
        
        private:
          Q_DECLARE_PRIVATE(BooleanMapper);
          Q_DISABLE_COPY(BooleanMapper);        
	protected:

	private:
       // BooleanMapper(const BooleanMapper &);  /// Not implemented
      //  void operator=(const BooleanMapper&); /// Not implemented

	};
		
}
#endif
