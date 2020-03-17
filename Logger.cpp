#include "Logger.h"
LogLevel Log::ReportingLevel;

std::ostringstream &Log::Get(LogLevel level) {
  os << ToString(level) << ":\t";
  return os;
}

Log::~Log() {
  os << std::endl;
  fprintf(stderr, "%s", os.str().c_str());
  fflush(stderr);
}
