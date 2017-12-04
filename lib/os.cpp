//
// Created by jintian on 7/14/17.
//
// this library provider some function to
// judge a directory is exist or not
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <valarray>
#include <include/log.h>

#include "include/str_util.h"

#include "include/os.h"


struct stat info;
using namespace std;

bool cao::os::exists(char *path) {
    // if path exists, return true else return false
    if (stat(path, &info) != 0) {
        // path not exist
        return false;
    } else {
        // this is a file
        return true;
    }
}

bool cao::os::isdir(char *path) {
    // judge is directory or file, if dir return true, if file return false
    if (stat(path, &info) != 0) {
        // path not exist
        return false;
    } else if (info.st_mode & S_IFDIR) {
        // this is a directory
        return true;
    } else {
        return false;
    }

}

bool cao::os::isfile(char *path) {
    // return a path is file or not
    if (stat(path, &info) != 0) {
        // path not exist
        return false;
    } else if (info.st_mode & S_IFDIR) {
        // this is a directory
        return false;
    } else {
        return true;
    }
}

vector<string> cao::os::list_files(char *path) {
    DIR *dp;
    struct dirent *dirP;
    vector<string> files;
    if ((dp = opendir(path)) == NULL) {
        cout << "dir not exist." << endl;
    }

    while ((dirP = readdir(dp)) != NULL) {
        if (dirP->d_type == DT_REG) {
            files.push_back(path + string("/") + string(dirP->d_name));
        }
    }

    closedir(dp);
    return files;
}

vector<string> cao::os::list_dirs(char *path) {
    DIR *dp;
    struct dirent *dirP;
    vector<string> files;
    if ((dp = opendir(path)) == NULL) {
        cout << "dir not exist." << endl;
    }

    while ((dirP = readdir(dp)) != NULL) {
        if (dirP->d_type == DT_REG) {
            files.push_back(path + string("/") + string(dirP->d_name));
        }
    }

    closedir(dp);
    return files;
}


/**
 * list all files contains file and folders
 * @param path
 * @return
 */
vector<string> cao::os::list_all(char *path) {
    DIR *dp;
    struct dirent *dirP;
    vector<string> files;
    if ((dp = opendir(path)) == NULL) {
        cout << "dir not exist." << endl;
    }

    while ((dirP = readdir(dp)) != NULL) {
        if (dirP->d_type == DT_REG) {
            files.push_back(path + string("/") + string(dirP->d_name));
        }
    }

    closedir(dp);
    return files;
}

string cao::os::join(char *path, string filename) {
    // path maybe /home/jin/doc1 or /home/jin/doc1/
    // make sure drop the last '/'
    string path_string = string(path);
    string joiner = "/";
#ifdef __WIN32
    joiner = "\\";
#endif

#ifdef _UNIX
    // unix machine
    joiner = "/";
#endif

#ifdef __APPLE__
    joiner = "/";
#endif
    vector<string> split_r;

    cao::str_util::SplitString(path_string, split_r, joiner);
    cao::str_util::StripString(split_r, "");
    string path_s = cao::str_util::JoinString(joiner, split_r);
    string joined_path = path_string + joiner + filename;
    return joined_path;
}

string cao::os::parent_path(char *path) {
    // get dir name of a path
    string joiner = "/";
#ifdef __WIN32
    joiner = "\\";
#endif

#ifdef __unix__
    // unix machine
    joiner = "/";
#endif

#ifdef __APPLE__
    joiner = "/";
#endif
    Log("get parent path, this is original " + (string) path);
    vector<string> split_r;
    cao::str_util::SplitString(path, split_r, joiner);
    vector<string> split_drop_file_name(split_r.begin(), split_r.end() - 1);
    string dir = cao::str_util::JoinString(joiner, split_drop_file_name);
    LogInfo("to see is the parent path is right. " + dir);
    return dir;
}


/**
 * this method will return the filename of a path
 * @param path
 * @return
 */
string cao::os::filename(char *path){
    return "";
}


/**
 * this method will create a folder
 * @param path
 */
void cao::os::mkdir(char *path) {

}

/**
 * this method will create a folder recursive
 * @param path
 */
void cao::os::makedirs(char *path) {

}