//
// Created by jintian on 7/14/17.
//

#ifndef _T_OS_H
#define _T_OS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace cao{

    namespace os{
        bool exists(char *path);
        bool isdir(char *path);
        bool isfile(char *path);

        vector<string> list_files(char *path);
        vector<string> list_dirs(char *path);
        string join(char *path, string filename);

        string parent_path(char *path);
        string filename(char *path);

        void mkdir(char *path);
        void makedirs(char *path);

        string abs_path(char *path);
    }
}

#endif //_OS_H
