//
// Created by jintian on 7/14/17.
//

#ifndef _T_OS_H
#define _T_OS_H

#include <iostream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

namespace cao{

    namespace os{
        bool exists(char *path);
        bool isdir(char *path);
        bool isfile(char *path);

        vector<string> list_files(char *path, bool full_path);
        vector<string> list_dirs(char *path, bool full_path);
        vector<string> list_all(char *path, bool full_path);

        string join(char *path, string filename);

        string parent_path(char *path);
        string filename(char *path);

        int do_mkdir(char *path, mode_t mode);
        int makedirs(char *path, mode_t mode);

        string abs_path(char *path);
    }
}

#endif //_OS_H
