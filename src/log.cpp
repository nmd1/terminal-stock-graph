#include "log.hpp"

FILE * logfile; 
void log_setup() {
    Log::setReportingLevel(l_DEBUG);
    FILE* err = fopen("/dev/pts/9", "a");
    Log::setGlobalLog(err);
    logfile = fopen("debug.log", "a");
    LOG_FILE(logfile, l_WARN) << "==============[RUN]==============";
}


std::string toString(Level level) {
    if(level == l_TRACE) return "TRACE";
    if(level == l_DEBUG) return "DEBUG";
    if(level == l_INFO)  return "INFO" ;
    if(level == l_WARN)  return "WARN" ;
    if(level == l_ERROR) return "ERROR";

    std::stringstream errormsg;
    errormsg << "Invalid Log level ("<<level<<")"<<std::endl;
    throw std::runtime_error(errormsg.str());


}

bool isValidLogLevel(Level level) {
    return (level >= l_TRACE) && (level < l_NONE);
}


Log::Log() {}
Log::~Log() { Log::flush(); }

void Log::setGlobalLog(FILE* fp) {globalLog = fp;}
void Log::setReportingLevel(Level level) { reportingLevel = level; }
Level Log::getReportingLevel() { return reportingLevel; }
void Log::resetGlobalLog() { globalLog = DEFAULT_LOG_LOCATION; }

std::ostringstream& Log::add(Level level, std::string funcname) {

    if(!isValidLogLevel(level)) {
        std::stringstream errormsg;
        errormsg << "Invalid Log level ("<<level<<")"<<std::endl;
        Log::flush();
        throw std::runtime_error(errormsg.str());
    }
    os <<"[" << toString(level) << "]\t";

    if(level < l_INFO) os << "<" << funcname << "> ";

	auto t = std::time(NULL);
    auto tm = *std::localtime(&t);
    os << "(" << std::put_time(&tm, "%m/%d/%Y_%I:%M:%S_%p") << "):" << "\t";
    return os;
}

std::ostringstream& Log::add(FILE* fp, Level level, bool tee, std::string funcname) {
    localLog = fp;
    log_to_both = tee;
    return add(level, funcname);
}

void Log::flush() {
    os << std::endl;
    FILE* out = (localLog != NULL) ? localLog : globalLog;
    fprintf(out, "%s", os.str().c_str());
    fflush(out);
    if(log_to_both && out != globalLog) {
        fprintf(globalLog, "%s", os.str().c_str());
        fflush(globalLog);
    }
}


Level Log::reportingLevel = DEFAULT_LOG_LEVEL;
FILE* Log::globalLog = DEFAULT_LOG_LOCATION;