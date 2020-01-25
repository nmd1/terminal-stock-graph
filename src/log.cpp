#include "log.hpp"

FILE * logfile; 
void log_setup() {
    Log::resetGlobalLog();
    Log::setReportingLevel(globaloptions.leveloption);
    if(!globaloptions.ttyout.empty()) {
        FILE* err = fopen(globaloptions.ttyout.c_str(), "a");
        Log::setGlobalLog(err);
    }
    logfile = fopen("debug.log", "a");
}


std::string logLevelToString(Level level) {
    if(level == l_TRACE) return "TRACE";
    if(level == l_DEBUG) return "DEBUG";
    if(level == l_INFO)  return "INFO" ;
    if(level == l_WARN)  return "WARN" ;
    if(level == l_ERROR) return "ERROR";

    std::stringstream errormsg;
    errormsg << "Invalid Log level ("<<level<<")"<<std::endl;
    throw std::runtime_error(errormsg.str());
}
Level stringToLogLevel(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), ::toupper); 
    if(input.compare("NONE") == 0)      return l_NONE;
    if(input.compare("TRACE") == 0)     return l_TRACE;
    if(input.compare("DEBUG") == 0)     return l_DEBUG;
    if(input.compare("INFO") == 0)      return l_INFO;
    if(input.compare("WARN") == 0)      return l_WARN;
    if(input.compare("WARNING") == 0)   return l_WARN;
    if(input.compare("ERR") == 0)       return l_ERROR;
    if(input.compare("ERROR") == 0)     return l_ERROR;

    std::stringstream errormsg;
    errormsg << "Invalid Log level ("<<input<<")"<<std::endl;
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
void Log::resetGlobalLog() { 
    if( globalLog != DEFAULT_LOG_LOCATION &&
        globalLog != stdout &&
        globalLog != stderr &&
        globalLog != stdin     
    ) 
    fclose(globalLog);
    globalLog = DEFAULT_LOG_LOCATION; 
}


std::ostringstream& Log::add(Level level, std::string funcname) {

    if(!isValidLogLevel(level)) {
        std::stringstream errormsg;
        errormsg << "Invalid Log level ("<<level<<")"<<std::endl;
        Log::flush();
        throw std::runtime_error(errormsg.str());
    }
    os <<"[" << logLevelToString(level) << "]\t";

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
    if(globalLog && log_to_both && out != globalLog) {
        fprintf(globalLog, "%s", os.str().c_str());
        fflush(globalLog);
    }
}


Level Log::reportingLevel = DEFAULT_LOG_LEVEL;
FILE* Log::globalLog = DEFAULT_LOG_LOCATION;