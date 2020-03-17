#ifndef LOGGER_H
#define LOGGER_H
#include <ctime>
#include <iostream>
#include <sstream>

#define LOG(level)                                                             \
  if (level > Log::ReportingLevel)                                             \
    ;                                                                          \
  else                                                                         \
    Log().Get(level)

enum LogLevel { ERROR, WARNING, INFO, DEBUG };
inline const char *ToString(LogLevel level) {
  static const char *names[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
  return names[level];
}

class Log {

public:
  Log(){};
  virtual ~Log();
  std::ostringstream &Get(LogLevel level = INFO);

public:
  static LogLevel ReportingLevel;

protected:
  std::ostringstream os;

private:
  Log(const Log &);
  Log &operator=(const Log &);
};
#endif
