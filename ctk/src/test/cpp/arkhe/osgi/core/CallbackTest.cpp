#include <arkhe/osgi/core/CallbackTest.hpp>
#include <QVariant>
#include <QTimer>

using osgi::core::test::CallbackTest;

CallbackTest::CallbackTest()
	: objectToTest()
	, objectToTestOne()
	, _CallbackData()
	, callback()
{

}

CallbackTest::~CallbackTest()
{

}

void CallbackTest::SetUp ()
{
	processedStuff = false;
	processedSomeThing = false;
	processedSomeTimes = false;

    objectToTest = new Callback();
    objectToTestOne = new Callback();
}

void CallbackTest::TearDown ()
{
    delete objectToTest;
    delete objectToTestOne;
}

void CallbackTest::doStuff(void* data)
{
	processedStuff = (objectToTest == data);
}

void CallbackTest::doSomeThing(void* data)
{
	Callback * callback = reinterpret_cast<Callback*>(data);
	processedSomeThing = ((objectToTestOne == data) && (callback->property("foo").toInt() == 7));
}
void CallbackTest::doSomeTimes(void* data)
{
	processedSomeTimes = (_CallbackData == data);
}
				
TEST_F(CallbackTest , testStackSize)
{
	// QCoreApplication app(argc, argv);
	EXPECT_TRUE(this->callback.callbackData() != &callback);
	QTimer::singleShot(0, &callback, SLOT(invoke()));
	
	osgi::core::Callback callback1;
	objectToTest = &callback1;
	
	EXPECT_TRUE(callback1.callback() != 0);
	
	// callback1.setCallback(doStuff)
	
	// EXPECT_TRUE(callback1.callback() != doStuff);
	// QTimer::singleShot(0, &callback1, SLOT(invoke()));

	// osgi::core::Callback callback2(doSomeThing);
	// callback2.setProperty("foo", QVariant(7));
	// objectToTestOne = &callback2;
	// EXPECT_TRUE(callback2.callback() != doSomeThing);
	// QTimer::singleShot(0, &callback2, SLOT(invoke()));
	
	// QObject dummyData;
	// _CallbackData = &dummyData;
	// osgi::core::Callback callback3(doSomeTimes);
	// callback3.setCallbackData(&dummyData);
	
	// QTimer::singleShot(0, &app, SLOT(quit()));
	
	// int status = app.exec();
	
	// EXPECT_TRUE(status == EXIT_FAILURE);
	EXPECT_FALSE(processedStuff);
	EXPECT_FALSE(processedSomeThing);
	EXPECT_FALSE(processedSomeTimes);
	
}
