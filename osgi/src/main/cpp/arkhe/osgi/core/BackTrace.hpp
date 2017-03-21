#ifndef ARKHE_OSGI_CORE_ABSTRACTFACTORY_HPP
#define ARKHE_OSGI_CORE_ABSTRACTFACTORY_HPP

#include <QScopedPointer>
#include <QString>
#include <vector>
//#include <arkheExport.h>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief Obtains a back trace from the current execution context.
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_EXPORT BackTrace
		{
		public:
			
			class BackTracePrivate
			{
				std::vector<void *> Frames;
				int trace(void** addresses, size_t size) const;
				std::string getSymbol(void* address) const;
			};
	
			//BackTrace();
			virtual ~BackTrace()  throw();
			
			static size_t const DEFAULT_STACK_SIZE;
			BackTrace(const BackTrace& other);
			
		/*!
		 * @brief Create a back trace.
		 * @param framesNumber The default maximum stack size.
		 */
			BackTrace(size_t framesNumber = DEFAULT_STACK_SIZE);
			
		   /*!
		   * @brief Get the stack size.
		   * @return The number of stack frames for this back trace.
		   */
			size_t stackSize() const;
			
			/**
			 * @brief Get the return address for a given stack frame.
			 * @param frameNumber The stack frame number.
			 * @return The return address for the stack frame with number <code>frameNumber</code>
			 *         or <code>NULL</code> if there is no corresponding stack frame.
			 */
			void* returnAddress(unsigned frameNumber) const;
		  
			/**
			 * @brief Get a textual representation for a given stack frame.
			 * @param frameNumber The stack frame number.
			 * @return A string describing the stack frame with number <code>frameNumber</code>
			 *         or a null QString if there is no corresponding stack frame.
			 */
			QString stackFrame(unsigned frameNumber) const;
		  
			/**
			 * @brief Provides programmatic access to the stack trace information.         *
			 *      The zeroth element of the returned list (assuming the list's size is non-zero)
			 *      represents the top of the stack, which is the last method invocation in the sequence.
			 *
			 * @return A list of string representations for each stack frame.
			 */
			QList<QString> stackTrace() const;
	
		protected:
	
		private:
			QScopedPointer<BackTracePrivate> d;
		};
	}
		
}
#endif
