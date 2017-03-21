#ifndef ARKHE_OSGI_CORE_ABSTRACTFACTORY_HPP
#define ARKHE_OSGI_CORE_ABSTRACTFACTORY_HPP

#include <gtest/gtest.h>
#include <QScopedPointer>
#include <QString>

#include <arkhe/osgi/osgi.hpp>

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


			private :
				BackTrace * objectToTest;

			};
	}
}
#endif
