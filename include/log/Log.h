#ifndef LOG_INFO_H
#define LOG_INFO_H

#include <string>
#include <cstdarg>
#include <ostream>

void OpenLog( std::string fileName );
void CloseLog();

void LogInfo( std::string str );
void LogError( std::string str );

#endif //LOG_INFO_H
