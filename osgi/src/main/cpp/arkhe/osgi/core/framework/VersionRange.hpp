#ifndef ARKHE_OSGI_CORE_FRAMEWORK_VERSIONRANGE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_VERSIONRANGE_HPP

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/framework/Version.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT VersionRange
		{

		public:

			VersionRange();
			VersionRange(const QString& vr);
			virtual ~VersionRange();

			static VersionRange defaultVersionRange();
			bool isSpecified() const;
			bool withinRange(const Version& ver) const;
			bool withinRange(const VersionRange& range) const;
			int compare(const VersionRange& obj) const;
			QString toString() const;
			bool operator==(const VersionRange& r) const;

		protected:

		private:
			Version low;
			Version high;
			bool lowIncluded;
			bool highIncluded;
		};		
	}
}
#endif
