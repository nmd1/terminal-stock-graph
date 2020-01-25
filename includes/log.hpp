#ifndef LOG_H
#define LOG_H
#include <ctime>
#include <sstream>
#include <iomanip> //put_time
#include <algorithm>


//enum Level : short;
//class Log;




#ifndef LOG_MIN_LEVEL
#define LOG_MIN_LEVEL l_TRACE
// Use -DLOG_MIN_LEVEL=<Level> to specify log level
#endif

#define DEFAULT_LOG_LEVEL l_INFO
#define DEFAULT_LOG_LOCATION stderr
/* LOGGER, inspired by drdobbs
 * LOG(Level) will log directly to the global log file descriptor.
 * By default this is stderr. This default can be changed and will
 * Apply to all upcoming Log requests.
 * 
 * LOG_FILE(fp, Level) will override the global log fp and log to whatever you 
 * specified 
 * 
 * LOG_BOTH(fp, Level) will log to both your specified fp and global fp
 * 
 * The global reporting level get be get/set using their corresponding functions
 */
#define TRACELOC __FUNCTION__ + std::string(":") + std::to_string(__LINE__)
#define LOG(level) \
if (level < LOG_MIN_LEVEL); \
else if (level < Log::getReportingLevel()); \
else Log().add(level, TRACELOC)

#define LOG_FILE(fp, level) \
if (level < LOG_MIN_LEVEL); \
else if (level < Log::getReportingLevel()); \
else if (fp == NULL); \
else Log().add(fp, level, false, TRACELOC)

#define LOG_BOTH(fp, level) \
if (level < LOG_MIN_LEVEL); \
else if (level < Log::getReportingLevel()); \
else if (fp == NULL); \
else Log().add(fp, level, true, TRACELOC)

enum Level : short{
    l_TRACE = 0,
    l_DEBUG,
    l_INFO,
    l_WARN,
    l_ERROR,
    l_NONE,// 5
};



class Log {

    public:
        Log();
        virtual ~Log();
        std::ostringstream& add(Level, std::string);
        std::ostringstream& add(FILE*, Level, bool, std::string);

        static void setGlobalLog(FILE*);
        static void resetGlobalLog();
        static Level getReportingLevel();
        static void setReportingLevel(Level);
    protected:
        std::ostringstream os;
    private:
        //? Log(const Log&);
        //? Log& operator=(const Log&);
        bool log_to_both;
        void flush(void);
        static Level reportingLevel;
        FILE* localLog = NULL; 
        static FILE* globalLog;
};

extern FILE* logfile;

std::string logLevelToString(Level);
Level stringToLogLevel(std::string);

bool isValidLogLevel(Level);

void log_setup(void);
#include "cmdopt.hpp"
#endif