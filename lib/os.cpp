//
// Created by jintian on 7/14/17.
//
// this library provider some function to
// judge a directory is exist or not
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <valarray>
#include <include/log.h>

#include "include/str_util.h"

#include "include/os.h"


struct stat info;
typedef struct stat Stat;

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

vector<string> cao::os::list_files(char *path, bool full_path) {
    DIR *dp;
    struct dirent *dirP;
    vector<string> files;
    if ((dp = opendir(path)) == NULL) {
        cout << "dir not exist." << endl;
    }

    while ((dirP = readdir(dp)) != NULL) {
        if (dirP->d_type == DT_REG) {
            if (full_path) {
                files.push_back(path + string("/") + string(dirP->d_name));
            } else {
                files.push_back(string(dirP->d_name));
            }
        }
    }

    closedir(dp);
    return files;
}

vector<string> cao::os::list_dirs(char *path, bool full_path) {
    DIR *dp;
    struct dirent *dirP;
    vector<string> files;
    if ((dp = opendir(path)) == NULL) {
        cout << "dir not exist." << endl;
    }

    while ((dirP = readdir(dp)) != NULL) {
        if (dirP->d_type == DT_DIR) {
            if (full_path) {
                files.push_back(path + string("/") + string(dirP->d_name));
            } else {
                files.push_back(string(dirP->d_name));
            }
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
vector<string> cao::os::list_all(char *path, bool full_path) {
    DIR *dp;
    struct dirent *dirP;
    vector<string> files;
    if ((dp = opendir(path)) == NULL) {
        cout << "dir not exist." << endl;
    }

    while ((dirP = readdir(dp)) != NULL) {
        if (dirP->d_type == DT_REG) {
            if (full_path) {
                files.push_back(path + string("/") + string(dirP->d_name));
            } else {
                files.push_back(string(dirP->d_name));
            }
        } else if (dirP->d_type == DT_DIR) {
            if (full_path) {
                files.push_back(path + string("/") + string(dirP->d_name));
            } else {
                files.push_back(string(dirP->d_name));
            }
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
//    Log("get parent path, this is original " + (string) path);
    vector<string> split_r;
    cao::str_util::SplitString(path, split_r, joiner);
    vector<string> split_drop_file_name(split_r.begin(), split_r.end() - 1);
    string dir = cao::str_util::JoinString(joiner, split_drop_file_name);
//    LogInfo("to see is the parent path is right. " + dir);
    return dir;
}


/**
 * this method will return the filename of a path
 * @param path
 * @return
 */
string cao::os::filename(char *path) {
    string path_str = path;
    if (cao::os::exists(path)) {
        if (cao::os::isdir(path)) {
            // if dir, return directly
            return path_str;
        } else {
            string joiner ("/");
            string joiner_win ("\\");

            std::size_t found = path_str.find(joiner);
            std::size_t found_win = path_str.find(joiner_win);

            if (found != std::string::npos) {
                // this is a path from unix
                vector<string> split_r;
                cao::str_util::SplitString(path_str, split_r, joiner);
                return split_r[split_r.size() - 1];
            } else if (found_win != std::string::npos) {
                // this is path from windows
                vector<string> split_r;
                cao::str_util::SplitString(path_str, split_r, joiner_win);
                return split_r[split_r.size() - 1];
            } else {
                // this is exactly a file
                return path_str;
            }
        }
    } else {
        LogFatal("can not found path or file: " + path_str);
        return "";
    }
}


/**
 * this method will create a folder
 * @param path
 */
int cao::os::do_mkdir(char *path, mode_t mode) {

    Stat st;
    int status = 0;
    if (stat(path, &st) != 0) {
        /* Directory does not exist. EEXIST for race condition */
        if (mkdir(path, mode) != 0 && errno != EEXIST)
            status = -1;
    } else if (!S_ISDIR(st.st_mode)) {
        errno = ENOTDIR;
        status = -1;
    }
    return status;
}

/**
 * this method will create a folder recursive
 * @param path
 */
int cao::os::makedirs(char *path, mode_t mode) {
    return 0;
}