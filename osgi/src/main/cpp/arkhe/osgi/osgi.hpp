#ifndef ARKHE_OSGI_HPP
#define ARKHE_OSGI_HPP

#include <QDebug>
#include <QtGlobal>
#include <QStringList>
#include <QDateTime>
#include <vector>

#define ARKHE_CORE_EXPORT


#define CONSTRUCTOR_NO_ARG_CPP(PUB)      \
  PUB::PUB(): d_ptr(new PUB##Private)    \
    {                                    \
    }

#define CONSTRUCTOR_1_ARG_CPP(PUB, _ARG1)   \
  PUB::PUB(_ARG1 _parent)                       \
    : Superclass( _parent )                     \
    , d_ptr(new PUB##Private)                   \
    {                                           \
    }

#define SET_CPP(PUB, _TYPE, _NAME, _VARNAME)    \
  void PUB::_NAME(_TYPE var)                        \
  {                                                 \
    Q_D(PUB);                                       \
    d->_VARNAME =  var;                             \
  }
#define GET_CPP(PUB, _TYPE, _NAME, _VARNAME)   \
  _TYPE PUB::_NAME()const                          \
  {                                                \
    Q_D(const PUB);                                \
    return d->_VARNAME;                            \
  }

namespace osgi 
{
    void ARKHE_CORE_EXPORT qListToSTLVector(const QStringList& list, std::vector<char*>& vector);
    void ARKHE_CORE_EXPORT qListToSTLVector(const QStringList& list, std::vector<std::string>& vector);
    void ARKHE_CORE_EXPORT stlVectorToQList(const std::vector<std::string>& vector, QStringList& list);
    QStringList ARKHE_CORE_EXPORT nameFilterToExtensions(const QString& nameFilter);
    QStringList ARKHE_CORE_EXPORT nameFiltersToExtensions(const QStringList& nameFilters);
    QString ARKHE_CORE_EXPORT extensionToRegExp(const QString& extension);
    QRegExp ARKHE_CORE_EXPORT nameFiltersToRegExp(const QStringList& nameFilters);
    int ARKHE_CORE_EXPORT significantDecimals(double value, int defaultDecimals = -1);
    int ARKHE_CORE_EXPORT orderOfMagnitude(double value);
    double ARKHE_CORE_EXPORT closestPowerOfTen(double value);
    bool ARKHE_CORE_EXPORT removeDirRecursively(const QString & dirName);
    bool ARKHE_CORE_EXPORT copyDirRecursively(const QString &srcPath, const QString &dstPath);
    QString ARKHE_CORE_EXPORT qtHandleToString(Qt::HANDLE handle);
    qint64 ARKHE_CORE_EXPORT msecsTo(const QDateTime& t1, const QDateTime& t2);
    
    namespace
    {
		struct ARKHE_CORE_EXPORT SetName
		{	
			SetName(const QString& Name);
			const QString Name;
		};
		/// Sets a Qt object's name  ie menu->addAction("Open") << ctkSetName("FileOpenMenu");
		template<typename T>
		T* operator<<(T* LHS, const SetName& RHS)
		{
		  LHS->setObjectName(RHS.Name);
		  return LHS;
		}
        template<typename BaseClassType, typename ClassType>
        BaseClassType *instantiateObject()
        {
            return new ClassType;
        }
    }
}
#endif

