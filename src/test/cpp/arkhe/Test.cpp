#include <QApplication>

int runTests (int iteration)
{
    switch (iteration)
    {
    case 1 :
        ::testing::GTEST_FLAG(filter) = "*first*:*second*";
        break;

    case 2 :
        ::testing::GTEST_FLAG(filter) = "*third*:*fourth*";
        break;

    default :
        ::testing::GTEST_FLAG(filter) = "*";
        break;
    }

    ::testing::GTEST_FLAG(repeat) = iteration;
}

int launch (const std::string & suite ,
                             int argc ,
                             char * argv[])
{

    ::testing::GTEST_FLAG(output) = "xml:Report.xml"; // GTEST_FLAG(output) = "xml:" + path;
    ::testing::FLAGS_gmock_verbose = "verbose";

    //    ::testing::GTEST_FLAG(print_time) = false;
    
    try
    {
        LOG4CXX_TRACE(didactics::test::logger , "Innitializing google mock");
        ::testing::InitGoogleTest(&argc , argv);
        ::testing::InitGoogleMock(&argc , argv);
    }
    catch (std::exception & e)
    {
        LOG4CXX_ERROR(didactics::test::logger ,
                      "Issues while innitializing test environment" << typeid (e).name () << ": " << e.what () );
    }
    catch (...)
    {
        LOG4CXX_FATAL(didactics::test::logger , "Unhandled exception");
    }

    const ::testing::TestInfo * const testInfo = ::testing::UnitTest::GetInstance()->current_test_info();
    //    LOG4CXX_TRACE(didactics::test::logger , ">>>>>>>>!!!!Test Name!!!!>>>>>>>> ("
    //                << testInfo->name() <<")");
    //
    //    LOG4CXX_TRACE(didactics::test::logger , ">>>>>>>>!!!!Test Case Name!!!!>>>>>>>> ("
    //                << testInfo->test_case_name() <<")");

    //    LOG4CXX_TRACE(didactics::test::logger , ">>>>>>>>!!!!Star running unit test!!!!>>>>>>>> ("
    //                << ::testing::UnitTest::GetInstance()->test_case_to_run_count() <<")");
    //    LOG4CXX_TRACE(didactics::test::logger , "Running unit test" <<  ::testing::UnitTest::GetInstance()->current_test_info());
    return RUN_ALL_TESTS();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    return a.exec();
}
