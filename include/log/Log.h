#ifndef LOG_INFO_H
#define LOG_INFO_H

#include <string>
#include <cstdarg>
#include <ostream>

#include <stdexcept>
#include <exception>
#include <sstream>
#include <iostream>
#include <errno.h>
#include <string.h>

//TODO: UNIX ONLY!
#include <syslog.h>

#define STR(ostream_expr) \
    (static_cast<std::ostringstream&>(std::ostringstream() << std::flush << ostream_expr)).str()

#define CSTR(ostream_expr) STR(ostream_expr).c_str()

#define _SYSLOG_IMPL(level, prefix, msg, file, line) \
    syslog(level, "%s", CSTR(prefix << ": " << msg << " (" << file << ":" << line))

#define SRC_MSG " (" << __SRC__ << ")"

#define _SYSLOG_DEBUG(msg, file, line)   _SYSLOG_IMPL(LOG_DEBUG,   "DEBUG",  msg, file, line)
#define _SYSLOG_INFO(msg, file, line)    _SYSLOG_IMPL(LOG_INFO,    "INFO",   msg, file, line)
#define _SYSLOG_NOTICE(msg, file, line)  _SYSLOG_IMPL(LOG_NOTICE,  "NOTICE", msg, file, line)
#define _SYSLOG_WARNING(msg, file, line) _SYSLOG_IMPL(LOG_WARNING, "WARN",   msg, file, line)
#define _SYSLOG_ERR(msg, file, line)     _SYSLOG_IMPL(LOG_ERR,     "ERROR",  msg, file, line)
#define _SYSLOG_CRIT(msg, file, line)    _SYSLOG_IMPL(LOG_CRIT,    "CRIT",   msg, file, line)
#define _SYSLOG_ALERT(msg, file, line)   _SYSLOG_IMPL(LOG_ALERT,   "ALERT",  msg, file, line)
#define _SYSLOG_EMERG(msg, file, line)   _SYSLOG_IMPL(LOG_EMERG,   "EMERG",  msg, file, line)

#define _LOG_DEBUG(msg)    _SYSLOG_DEBUG(msg, __FILE__, __LINE__)
#define _LOG_INFO(msg)     _SYSLOG_INFO(msg, __FILE__, __LINE__)
#define _LOG_NOTICE(msg)   _SYSLOG_NOTICE(msg, __FILE__, __LINE__)
#define _LOG_WARNING(msg)  _SYSLOG_WARNING(msg, __FILE__, __LINE__)
#define _LOG_ERR(msg)      _SYSLOG_ERR(msg, __FILE__, __LINE__)
#define _LOG_CRIT(msg)     _SYSLOG_CRIT(msg, __FILE__, __LINE__)
#define _LOG_ALERT(msg)    _SYSLOG_ALERT(msg, __FILE__, __LINE__)
#define _LOG_EMERG(msg)    _SYSLOG_EMERG(msg, __FILE__, __LINE__)

#define _DBG() _LOG_ERR("#")
#define _DBG2(msg) _LOG_INFO(msg)



#endif //LOG_INFO_H
