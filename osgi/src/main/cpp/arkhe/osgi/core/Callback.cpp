#include <arkhe/osgi/core/Callback.hpp>


osgi::core::Callback::Callback(QObject * parent) 
: QObject(parent)
{
	this->CallbackData = this;
	this->setCallback(0);  
}

osgi::core::Callback::Callback(void (*newCallback)(void * data), QObject * parent) 
: QObject(parent)
{
  this->CallbackData = this;
  this->setCallback(newCallback);
}

osgi::core::Callback::~Callback()
{
   
}

void (*osgi::core::Callback::callback() const) (void*)
{
  return this->aCallback;
}
  
  
void osgi::core::Callback::setCallback(void (*newCallback)(void * data))
{
  this->aCallback = newCallback;
}

void * osgi::core::Callback::callbackData()const
{
  return this->CallbackData;
}


void osgi::core::Callback::setCallbackData(void * data)
{
  this->CallbackData = data;
}


void osgi::core::Callback::invoke()
{
	if (!this->aCallback)
    {
		return;
    }

	(*this->aCallback)(this->CallbackData);
}
