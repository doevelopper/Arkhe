#ifndef ARKHE_OSGI_TEST_HPP
#define ARKHE_OSGI_TEST_HPP

#include <QtWidgets/QApplication>
#include <vector>
#include <arkhe/osgi/osgi.hpp>
#include <gmock/gmock.h>
namespace osgi 
{
	namespace test
	{
        extern int run (const std::string & suite , int argc = 0 , char * argv[] = NULL, unsigned int iteration = 1);
        extern int run (int argc , char * argv[], const std::string & testOuputPath = NULL);
	}
}
#endif

