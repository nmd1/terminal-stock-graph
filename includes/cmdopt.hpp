#ifndef COMMAND_OPTIONS_H
#define COMMAND_OPTIONS_H

#include <getopt.h>
#include <iostream>
#include <vector>
#include <iomanip>

#include "log.hpp"

typedef struct __options_enhanced {
    std::string name;
    int has_arg;
    int *flag;
    int val;

    std::string argument_type;
    std::string help_message;

} option_enh;

typedef struct __globalOptions {

    std::string stock = "AMD";
    std::string update_freq;                    // Not implimented
    bool minimize;                              // Not implimented
    bool transparent = false; 
    long int maxupdates = 0;                    // Not implimented

    Level leveloption = l_DEBUG;
    std::string ttyout = "";                    

    bool saveStockJSONs = false;
    std::string loadStockJSON = "";
} glob_opt; 

extern glob_opt globaloptions;

void set_options(int, char*[]);
void optexample(int, char*[]);


#endif