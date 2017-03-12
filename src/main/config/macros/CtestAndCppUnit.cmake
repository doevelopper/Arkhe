#http://public.kitware.com/pipermail/cmake/2007-March/013361.html
function(SELF_WRITTEN_TESTS_WITH_CTEST MODULE_NAME  TEST_SOURCES_LIST TEST_RUNNER TEST_ENTRY_POINT) #set(TEST_ENTRY_POINT "didactics/Test.cpp")

    add_executable(${MODULE_NAME}.bin ${TEST_ENTRY_POINT} ${TEST_SOURCES_LIST})
    target_link_libraries(UnitTester cppunit)
    FOREACH(test ${TEST_SOURCES_LIST})
        get_filename_component(UnitTestName ${test} NAME_WE)
        add_test(${TestName} ${MODULE_NAME}.bin ${UnitTestName})
        message(STATUS "${test}  added.")
    ENDFOREACH(test)
endfunction(SELF_WRITTEN_TESTS_WITH_CTEST)

























#1. The cmake part, that collects all the files containing a unit test (their 
#name ends in 'Test.cpp' on our build system), i.e. almost straight from the 
#sample in the CMake book:
#
#------8<---------CMakeLists.txt----------8<------------
#FILE(GLOB UnitTests_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*Test.cpp" )
#ADD_EXECUTABLE(UnitTester test_runner.cpp ${UnitTests_SRCS})
#FOREACH(test ${UnitTests_SRCS})
#        GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
#        ADD_TEST(${TestName} UnitTester ${TestName})
#ENDFOREACH(test)
#-------8<------------------8<------------
#
#2. You noticed above there is a stub C++ file 'test_runner.cpp' that simply 
#makes the correct test run given the command line arguments provided by 
#CTest. It roughly looks like this:
#
#---------8<--------test_runner.cpp-------8<-------------
##include <cppunit/extensions/TestFactoryRegistry.h>
##include <cppunit/ui/text/TestRunner.h>
#int main (int argc, char* argv[]) {
#  TextUi::TestRunner runner;
#  TestFactoryRegistry& registry = TestFactoryRegistry::getRegistry();
#
#  // run all tests if none specified on command line 
#  Test* test_to_run = registry.makeTest();
#  if (argc>1)
#        test_to_run = test_to_run->findTest(argv[1]);
#
#  runner.addTest( test_to_run );
#  bool failed = runner.run("", false);
#  return !failed;
#}
#---------8<---------------8<-------------
#
#3. Make sure every unit test case registers with its proper test name. For 
#this, I  used the CPPUNIT_TEST_SUITE_NAMED_REGISTRATION from CppUnit in each 
#of my test classes.  An example is here:
#
#---------8<---------SampleTest.cpp--------8<-----------
##include <cppunit/extensions/HelperMacros.h>
#class SampleTest : public CppUnit::TestFixture {
#  CPPUNIT_TEST_SUITE( SampleTest );
#  CPPUNIT_TEST( testEmpty );
#  CPPUNIT_TEST_SUITE_END();
#public:
#  void testEmpty () { int i = 5; CPPUNIT_ASSERT( i == 5 ); }
#};
#CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( SampleTest, SampleTest );
#-------------------------------------
#
#Note that this is heavily edited, because our stuff contains a lot of other 
#stuff unrelated to CppUnit tests, so there may be a few typos, but I hope the 
#general idea should be clear from this.
#
#One thing I noticed, but it came up on the list recently, is that when you 
#have generated the Makefiles, and you run 'make test', nothing happens.
#If you run 'ctest' instead, it goes through the tests. I have not investigated 
#this further though.