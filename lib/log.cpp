//
// Created by jintian on 17-8-5.
//

#include "include/log.h"
#include "include/colors.h"


using namespace std;


void LogInfo(int msg){
    cout << colors::blue << "[info] " <<  colors::reset << __TIME__ << ": " <<  msg << colors::reset << endl;
}


void LogInfo(const std::string& msg){
    cout << colors::blue << "[info] " <<  colors::reset << __TIME__ << ": "<< msg << colors::reset << endl;
}

/**
 * this method is used for logging errors
 * @param msg
 */
void LogFatal(std::string msg) {
    cout << colors::red << "[error] " << colors::yellow << msg << colors::reset << endl;
}

void LogFatal(int msg) {
    cout << colors::red << "[error] " << colors::yellow << msg << colors::reset << endl;
}

void Log(int msg){
    cout << colors::green << "message: " <<  colors::reset << __TIME__ << " " <<  msg << colors::reset << endl;
}


void Log(const std::string& msg){
    cout << colors::green << "message: " <<  colors::reset << __TIME__ << " " <<  msg << colors::reset << endl;
}



