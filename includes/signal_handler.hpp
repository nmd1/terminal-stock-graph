#ifndef OUR_SIGNAL_HANDLER_H
#define OUR_SIGNAL_HANDLER_H

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "debug.hpp"
#include "log.hpp"
void segfaultbackTrace(int);
void sigintDefault(int);
void signal_setup();

#endif