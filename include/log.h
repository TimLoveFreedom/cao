//
// Created by jintian on 17-8-5.
//

#ifndef _T_LOG_H
#define _T_LOG_H

#include <iostream>
#include <string>
#include <vector>


void LogInfo(int msg);
void LogInfo(const std::string& msg);

void LogFatal(std::string msg);


// log normal message
void Log(int msg);
void Log(const std::string& msg);

#endif //_T_LOG_H
