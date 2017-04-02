#ifndef ARKHE_OSGI_CORE_CALLBACKTEST_HPP
#define ARKHE_OSGI_CORE_CALLBACKTEST_HPP

#include <arkhe/osgi/core/Callback.hpp>
#include <arkhe/osgi/osgi.hpp>
#include <gtest/gtest.h>

namespace osgi
{
	namespace core
	{
		namespace test
		{
			class CallbackTest : public ::testing::Test
			{
			public:
				CallbackTest();
				CallbackTest(const CallbackTest & orig);
				virtual ~CallbackTest();
				/*!
				 * @brief Test set up.
				 */
				virtual void SetUp ();
				/*!
				 * @brief Test tear down.
				 */
				virtual void TearDown ();
				void doStuff(void* data);
				void doSomeThing(void* data);
				void doSomeTimes(void* data);
			protected:

				Callback * objectToTest;
				Callback * objectToTestOne;
				void* _CallbackData;
				Callback callback;
				bool processedStuff;
				bool processedSomeThing;
				bool processedSomeTimes;
			private :
			};
		}
	}
}
#endif
