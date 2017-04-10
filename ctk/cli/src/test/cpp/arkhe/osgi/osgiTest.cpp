#include <arkhe/osgi/osgiTest.hpp>

int osgi::test::run (const std::string & suite , int argc, char * argv[], unsigned int iteration)
{
	std::string testname(suite);
	const std::string name = !testname.empty() ? testname : "AllTests";
	if( iteration > 0)
	{
		::testing::GTEST_FLAG(repeat) = iteration;
	}

	::testing::GTEST_FLAG(filter) = suite;

	osgi::test::run (argc ,argv);
}


int osgi::test::run (int argc , char * argv[], const std::string & testOuputPath)
{
	 // GTEST_FLAG(output) = "xml:" + testOuputPath;

    ::testing::GTEST_FLAG(output) = "xml:Report.xml";
    // ::testing::FLAGS_gmock_verbose = "verbose";
    //    ::testing::GTEST_FLAG(print_time) = false;


    try
    {

        // ::testing::InitGoogleTest(&argc , argv);
        // ::testing::InitGoogleMock(&argc , argv);
    }
    catch (std::exception & e)
    {
        // LOG4CXX_ERROR(didactics::test::logger , "Issues while innitializing test environment" << typeid (e).name () << ": " << e.what () );
		std::cerr << "Issues while innitializing test environment" << typeid (e).name () << ": " << e.what () <<std::endl;
    }
    catch (...)
    {
        std::cerr << "Unhandled exception" <<std::endl;
    }

    // const ::testing::TestInfo * const testInfo = ::testing::UnitTest::GetInstance()->current_test_info();
    //    LOG4CXX_TRACE(didactics::test::logger , ">>>>>>>>!!!!Test Name!!!!>>>>>>>> ("    //                << testInfo->name() <<")");
    //
    //    LOG4CXX_TRACE(didactics::test::logger , ">>>>>>>>!!!!Test Case Name!!!!>>>>>>>> ("   //                << testInfo->test_case_name() <<")");

    //    LOG4CXX_TRACE(didactics::test::logger , ">>>>>>>>!!!!Star running unit test!!!!>>>>>>>> ("
    //                << ::testing::UnitTest::GetInstance()->test_case_to_run_count() <<")");
    //    LOG4CXX_TRACE(didactics::test::logger , "Running unit test" <<  ::testing::UnitTest::GetInstance()->current_test_info());
    return RUN_ALL_TESTS();
}

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
	int numberOfTestFailure = osgi::test::run(argc , argv);
    // return a.exec();
}
