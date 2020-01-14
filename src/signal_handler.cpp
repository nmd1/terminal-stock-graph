#include "signal_handler.hpp"

void segfaultbackTrace(int sig) {
  LOG_FILE(logfile, l_ERROR)<<"Segfault! Leaving"<<std::endl;

  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, fileno(logfile));
  exit(1);
}

void sigintDefault(int sig) {
  LOG_FILE(logfile, l_INFO)<<"Caught a sigint!"<<std::endl;
}

// Call in main
void signal_setup() {
  // install our signal handlers
  signal(SIGSEGV, segfaultbackTrace);   
  signal(SIGINT, sigintDefault);   
}