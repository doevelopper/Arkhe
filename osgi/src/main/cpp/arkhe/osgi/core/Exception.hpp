#ifndef ARKHE_OSGI_EXCEPTION_HPP
#define ARKHE_OSGI_EXCEPTION_HPP

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/BackTrace.hpp>

/**
 * \ingroup Core
 *
 * \brief Quickly declare a ctkException sub-class.
 * \param API The export macro.
 * \param CLS The class name for the ctkException sub-class.
 * \param BASE The class name of the actual super class.
 */
#define DECLARE_EXCEPTION(API, CLS, BASE)             \
  class API CLS : public BASE                         \
  {                                                   \
  public:                                             \
    explicit CLS(const QString& msg);                 \
    CLS(const QString& msg, const ctkException& exc); \
    CLS(const CLS& exc);                              \
    ~CLS() throw();                                   \
    CLS& operator = (const CLS& exc);                 \
    const char* name() const throw();                 \
    CLS* clone() const;                               \
    void rethrow() const ;                            \
  };

#define IMPLEMENT_EXCEPTION(CLS, BASE, NAME)                         \
  CLS::CLS(const QString& msg) : BASE(msg)                               \
  { }                                                                    \
  CLS::CLS(const QString& msg, const ctkException& exc) : BASE(msg, exc) \
  { }                                                                    \
  CLS::CLS(const CLS& exc) : BASE(exc)                                   \
  { }                                                                    \
  CLS::~CLS() throw()                                                    \
  { }                                                                    \
  CLS& CLS::operator = (const CLS& exc)                                  \
  {                                                                      \
    BASE::operator = (exc);                                              \
    return *this;                                                        \
  }                                                                      \
  const char* CLS::name() const throw()                                  \
  {                                                                      \
    return NAME;                                                         \
  }                                                                      \
  CLS* CLS::clone() const                                                \
  {                                                                      \
    return new CLS(*this);                                               \
  }                                                                      \
  void CLS::rethrow() const                                              \
  {                                                                      \
    throw *this;                                                         \
  }

DECLARE_EXCEPTION(ARKHE_CORE_EXPORT, osgi::core::UnsupportedOperationException, osgi::core::Exception)
DECLARE_EXCEPTION(ARKHE_CORE_EXPORT, osgi::core::RuntimeException, osgi::core::Exception)
DECLARE_EXCEPTION(ARKHE_CORE_EXPORT, osgi::core::InvalidArgumentException, osgi::core::RuntimeException)
DECLARE_EXCEPTION(ARKHE_CORE_EXPORT, osgi::core::IllegalStateException, osgi::core::RuntimeException)

IMPLEMENT_EXCEPTION(osgi::core::UnsupportedOperationException, osgi::core::Exception, "UnsupportedOperationException")
IMPLEMENT_EXCEPTION(osgi::core::RuntimeException, osgi::core::Exception, "RuntimeException")
IMPLEMENT_EXCEPTION(osgi::core::InvalidArgumentException, osgi::core::RuntimeException, "InvalidArgumentException")
IMPLEMENT_EXCEPTION(osgi::core::IllegalStateException, osgi::core::RuntimeException, "IllegalStateException")

/*!
 * @brief .
 */
namespace osgi
{
	namespace core 
	{
		class ARKHE_CORE_EXPORT Exception : public std::exception , public osgi::core::BackTrace
		{
		public:
			class TraceManipulator
			{
			public:
			  
				  TraceManipulator(const Exception* e);
				  QDebug print(QDebug dbg) const;
			  
			private:
			  
				  const Exception* Exc;
			};
			explicit Exception(const QString& msg);
			virtual ~Exception() throw();
			/**
			 * @brief Create a new ctkException containing another exception as the cause.
			 * @param msg The exception message.
			 * @param cause The nested exception causing this exception.
			 */
			Exception(const QString& msg, const Exception& cause);
		  
			/**
			 * @brief Copy constructor.
			 * @param o The exception to copy.
			 */
			Exception(const Exception& o);
			/**
			 * @brief Assignment operator.
			 * @param o The exception to assign to this exception.
			 * @return
			 */
			Exception& operator=(const Exception& o);
		  
			/**
			 * @brief Gets the nested exception which caused this exception.
			 * @return The nested exception, or <code>NULL</code> if there is none.
			 */
			const Exception* cause() const throw();
		  
			/**
			 * @brief Sets the cause for this exception.
			 * @param cause The exception causing this exception.
			 */
			void setCause(const Exception& cause);
		  
			/**
			 * @brief Returns the name for this exception.
			 * @return The exception name.
			 */
			virtual const char* name() const throw();
		  
			/**
			 * @brief Returns the class name for this exception.
			 * @return The exception class name.
			 */
			virtual const char* className() const throw();
		  
			/**
			 * @brief Returns a static string describing this exception.
			 * @return The exception description.
			 */
			virtual const char* what() const throw();
		  
			/**
			 * @brief Returns the detail message string of this exception.
			 * @return The detail exception message.
			 */
			QString message() const throw();
		  
			/**
			 * @brief Returns an object suitable for printing this executable
			 * and its backtrace via qDebug().
			 *
			 * Example usage:
			 * \code
			 * ctkException exc("My error");
			 * qDebug() << exc.printStackTrace();
			 * \endcode
			 *
			 * @return A helper object for streaming to qDebug().
			 */
			TraceManipulator printStackTrace() const;
		  
			/**
			 * @brief Creates a copy of this exception. Use rethrow() to throw the
			 * copy again.
			 * @return A copy of this exception.
			 */
			virtual Exception* clone() const;
		  
			/**
			 * @brief (Re)Throws this exception.
			 */
			virtual void rethrow() const;
		protected:
			friend class TraceManipulator;

			/**
			 * @brief Print the stack trace of this exception using the given QDebug object.
			 * @param dbg
			 * @return
			 */
			virtual QDebug printStackTrace(QDebug dbg) const;
		private:

			//Exception(const Exception &);  /// Not implemented
			//void operator=(const Exception&); /// Not implemented
			
			QString Msg;
			mutable std::string WhatMsg;
			Exception* NestedException;

			void printEnclosedStackTrace(QDebug dbg, const QList<QString>& enclosingTrace,
								   const QString& caption, const QString& prefix,
								   QSet<const Exception*>& dejaVu);
		};

		ARKHE_CORE_EXPORT QDebug operator<<(QDebug dbg, const Exception& exc);
		ARKHE_CORE_EXPORT QDebug operator<<(QDebug dbg, const Exception::TraceManipulator& trace);
	}
}
#endif
