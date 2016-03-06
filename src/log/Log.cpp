#define _CRT_SECURE_NO_WARNINGS
#include "log/Log.h"
#include <ostream>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>


const std::string CurrentDateTime( ) {
	time_t     now = time( 0 );
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime( &now );
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	//strftime( buf, sizeof( buf ), "%Y-%m-%d.%X", &tstruct );
	strftime( buf, sizeof( buf ), "%Y-%m-%d.%X", &tstruct );
	return buf;
}

namespace {
	std::ofstream logFile;
}

void OpenLog( std::string fileName )
{
	logFile.open( fileName );
}

void CloseLog()
{
	logFile.close();
}

void LogInfo( std::string str )
{
	std::time_t t = std::time( nullptr );
	logFile << CurrentDateTime( ) << " [INFO]: " << str << '\n';
}

void LogError( std::string str )
{
	std::time_t t = std::time( nullptr );
	logFile << CurrentDateTime( ) << " [ERROR]: " << str << '\n';
}

#undef _CRT_SECURE_NO_WARNINGS
