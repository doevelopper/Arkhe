#ifndef ARKHE_OSGI_BINARYFILEDESCRIPTOR_HPP
#define ARKHE_OSGI_BINARYFILEDESCRIPTOR_HPP

#define PACKAGE package
// BinUtils includes
#include <bfd.h>

// STD includes
#include <cstdlib>
#include <utility>
#include <vector>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFactoryFileBasedItem.hpp>

/*!
 * @brief Allows to resolve global symbols contained into an executable.
 *        Implementation valid only for unix-like systems (Linux, Mac, ...)
 */
namespace osgi
{
	namespace core
	{
		
		class BinaryFileDescriptorPrivate
        {
        public:

            using MemorySectionType = std::pair<asection*, void* >;
            using  MemorySectionContainer = std::vector<MemorySectionType> ;
  
            BinaryFileDescriptorPrivate();

            void* resolve(const char * symbol);

            MemorySectionContainer Sections;
            bfd * BFD;
            QString FileName;
        };


		class ARKHE_CORE_EXPORT BinaryFileDescriptor
		{
		public:
			BinaryFileDescriptor();
			virtual ~BinaryFileDescriptor();
			BinaryFileDescriptor(const QString& _fileName);

			QString fileName()const;
			void setFileName(const QString& _fileName);
			bool load();
			bool unload();
			bool isLoaded() const;
			void* resolve(const char * symbol);
		protected:

			QScopedPointer<BinaryFileDescriptorPrivate> d_ptr;

		private:

			Q_DECLARE_PRIVATE(BinaryFileDescriptor)
			Q_DISABLE_COPY(BinaryFileDescriptor)
		};
	}
}
#endif
