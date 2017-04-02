#ifndef ARKHE_OSGI_SCOPEDCURRENTDIR_HPP
#define ARKHE_OSGI_SCOPEDCURRENTDIR_HPP

#include <QScopedPointer>

#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core 
	{
		class ScopedCurrentDir
		{
		public:
			class ARKHE_CORE_EXPORT ScopedCurrentDirPrivate
			{
			public:
				ScopedCurrentDirPrivate()
				{
				}
				QString SavedCurrentPath;
			};

			explicit ScopedCurrentDir(const QString& path);
			virtual ~ScopedCurrentDir();

			QString currentPath()const;
			QString savedCurrentPath()const;

		protected:
			QScopedPointer<ScopedCurrentDirPrivate> d_ptr;
		private:
			Q_DECLARE_PRIVATE(ScopedCurrentDir)
			Q_DISABLE_COPY(ScopedCurrentDir)
		};
	}
}
#endif
