#include "cmdopt.hpp"
__globalOptions globaloptions;
void set_options(int argc, char *argv[]) {
    /* Options
     * -D --debug [Log Level]       Sets log level
     * -S --save                    Saves jsons to disk
     * -L --load [name]             Load json from disk
     * -m --mini                    Makes chart small
     * --transparent                Makes chart transparent
     * --tty                        Set a tty for log output
    */ 

    int transparent = 0;

    std::vector<option_enh> optiondict = {
        /*  {logoptname, arguments?, flag, opt,
            [argument description],
            flag description},
        */
        {"help",no_argument,  0, 'h', 
        "",
        "Display this help page"},

        {"debug",  required_argument,  0,  'D',
        "[TRACE/DEBUG/INFO/WARN/ERR]",
        "Change Logging level"},

        {"transparent",    no_argument, &transparent, 1,
        "",
        "makes charts transparent"},

        {"save",    no_argument,  0, 'S',
        "",
        "Saves data shown in chart to disk"},

        {"load",    required_argument,  0, 'L',
        "[Filename].stock",
        "Load saved data to be displayed in a chart"},


        {"security",    required_argument,  0, 's',
        "[Stock ticker name]",
        "Displays price chart of a company"},

		{"mini",    no_argument,  0, 'm',
        "",
        "Makes chart very small"},

		{"tty",    required_argument,  0, 0,
        "[tty number]",
        "Prints out log data to a specified /dev/pts/"},

        {"",0,0,0,
        "",
        ""}

    };

    // Convert to longopt so that getopt_long can process the options.
    struct option longopts[optiondict.size()];
    auto it = optiondict.begin();
    for (unsigned int i = 0; i < optiondict.size(); i++, it++) {
        longopts[i] = {it->name.c_str(), it->has_arg, it->flag, it->val};
    }


    int opt; 
    int longoptindex;
    // put ':' in the starting of the 
    // string so that program can  
    //distinguish between '?' and ':'  
    std::ostringstream os;
    while((opt = getopt_long(argc, argv, ":D:SL:s:m", longopts, &longoptindex)) != -1)  
    {  
        switch(opt)  
        {  
            case 0:
                if (longopts[longoptindex].flag != 0) break;

                if(std::string("tty").compare(std::string(longopts[longoptindex].name)) == 0) {
                    os << "/dev/pts/" << optarg;
                    globaloptions.ttyout = os.str();
                }

                break;
            case 'h':
                {
                    using namespace std;

                    const char  sep    = ' ';
                    const short optw   = 6;
                    const short loptw  = 18;
                    const short argw   = 29;
                    const short desw   = 2;
                    for(auto p = optiondict.begin(); p != optiondict.end(); p++) {
                        if(p->name == "\0" or p->name == "") continue;

                        cout<< left << setw(optw) << setfill(sep);
                        if(isalpha(p->val)) {
                            char in[3] = {'-' , (char)p->val , 0};
                            cout<<in;
                        } else {
                            cout<<"";
                        }
                        //

                        cout<< left << setw(loptw) << setfill(sep);
                        if(!p->name.empty()) {
                            string in = "--" + p->name + "";
                            cout<<in;
                        } else {
                            cout<<"";
                        }

                        cout<< left << setw(argw) << setfill(sep);
                        if(p->has_arg == required_argument) {
                            cout<<p->argument_type<<"";
                        } else {
                            cout<<"";
                        }

                        cout<< left << setw(desw) << setfill(sep);
                        cout<<p->help_message<<endl;
                    }
                }
                exit(0);
            case 'D': 
                globaloptions.leveloption = stringToLogLevel(optarg);
                break;

            case 'S': 
                globaloptions.saveStockJSONs = true;
                break;

            case 'L': 
                globaloptions.loadStockJSON = optarg;
                break;

            case 's': 
                globaloptions.stock = optarg;
                break;

            case 'm': 
                globaloptions.minimize = true;
                break;

            case ':':  
                os <<optopt<<" needs a value"<<std::endl;
                throw std::runtime_error(os.str());  

            case '?':  
                std::cout<<"Unknown option: -"<<(char)optopt<<std::endl; 
                break;  

            default:
                os << "fatal getopt error! ["<<opt<<"] doesn't exist!"<<std::endl;
                throw std::runtime_error(os.str());
        }  
    }  

    globaloptions.transparent = (bool)transparent;

    // optind is for the extra arguments 
    // which are not parsed 
    for(; optind < argc; optind++){      
        LOG_BOTH(logfile, l_DEBUG)<<"extra arguments: "<<argv[optind]<<std::endl;  
    } 

    LOG_BOTH(logfile, l_DEBUG) << "---------Options---------";
    LOG_BOTH(logfile, l_DEBUG) << "stock: "             <<globaloptions.stock;
    LOG_BOTH(logfile, l_DEBUG) << "update_freq: "       <<globaloptions.update_freq;
    LOG_BOTH(logfile, l_DEBUG) << "minimize: "          <<globaloptions.minimize;
    LOG_BOTH(logfile, l_DEBUG) << "transparent: "       <<globaloptions.transparent;
    LOG_BOTH(logfile, l_DEBUG) << "maxupdates: "        <<globaloptions.maxupdates;
    LOG_BOTH(logfile, l_DEBUG) << "leveloption: "       <<logLevelToString(globaloptions.leveloption);
    LOG_BOTH(logfile, l_DEBUG) << "ttyout: "            <<globaloptions.ttyout;
    LOG_BOTH(logfile, l_DEBUG) << "saveStockJSONs: "    <<globaloptions.saveStockJSONs;
    LOG_BOTH(logfile, l_DEBUG) << "loadStockJSON: "     <<globaloptions.loadStockJSON;
    LOG_BOTH(logfile, l_DEBUG) << "---------/Options---------";

}


// Just a reference
void optexample(int argc, char *argv[]) {
    int verbose_flag = 0;
	const struct option longopts[] = {
		{"verbose", no_argument,       &verbose_flag, 3},
		{"index",   no_argument,        0, 'i', },
		{"long",      no_argument,        0, 'l'},
		{"rock",     required_argument,  0, '\0'},
        {"test",     required_argument,  0, '\0'},
		{0,0,0,0},
	};
    int opt; 
    int longoptindex;
    // put ':' in the starting of the 
    // string so that program can  
    //distinguish between '?' and ':'  
    while((opt = getopt_long(argc, argv, ":if:lrx", longopts, &longoptindex)) != -1)  
    {  
        switch(opt)  
        {  
            case 'i':  
            case 'l':  
            case 'r':  
                printf("option: %c\n", opt);  
                break;  
            case 'f':  
                printf("filename: %s\n", optarg);  
                break;  
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }  

    // optind is for the extra arguments 
    // which are not parsed 
    for(; optind < argc; optind++){      
        printf("extra arguments: %s\n", argv[optind]);  
    } 
      
    globaloptions.stock = "AMD";
	std::cout<<verbose_flag<<std::endl;
}