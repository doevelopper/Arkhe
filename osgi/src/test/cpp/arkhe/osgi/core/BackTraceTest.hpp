#ifndef ARKHE_OSGI_CORE_BACKTRACETEST_HPP
#define ARKHE_OSGI_CORE_BACKTRACETEST_HPP

#include <arkhe/osgi/core/BackTrace.hpp>
#include <arkhe/osgi/osgi.hpp>
#include <gtest/gtest.h>

namespace osgi
{
	namespace core
	{
		namespace test
		{
			class BackTraceTest : public ::testing::Test
			{
			public:
				BackTraceTest();
				BackTraceTest(const BackTraceTest & orig);
				virtual ~BackTraceTest();
				/*!
				 * @brief Test set up.
				 */
				virtual void SetUp ();
				/*!
				 * @brief Test tear down.
				 */
				virtual void TearDown ();

			protected:

				BackTrace * objectToTest;

			private :

			};
		}
	}
}
#endif
