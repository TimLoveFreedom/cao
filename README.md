![](http://wx4.sinaimg.cn/large/006fVPCvly1fmn2sdxspkj30zm0go7n8.jpg)

# cao [![Travis Status](https://travis-ci.org/davisking/dlib.svg?branch=master)](https://travis-ci.org/davisking/dlib)

> **cao** is a C++ library contains various Python like APIs. It named as Cpp Assist Oar. Which means it's like the paddle helps you boating in C++. Mostly **cao** is just do the things **like boost**, but it is *more python-like* and *simpler*, and more clear to use.

## Installation

**cao** is a library, install cao to system is very simple:

```
git clone https://github.com/jinfagang/cao
cd cao
mkdir build
cd build
cmake ..
make all -j8
sudo make install
```

so you can have cao library in your system.

## Usage

**cao** has a very clean and easy-to-use API, it consist of many parts. All parts can be listed as follow:

- *files*;
- *random*;
- *color*;
- *more*;

before using **cao**, you should find library in CMakeLists first:

```$xslt
# this is path to found cao library
find_package( PkgConfig )
pkg_check_modules( CAO REQUIRED cao )
if (CAO_FOUND)
    message(STATUS "[cao] we just found cao library")
endif ()

set(BUILD_SHARED_LIBS OFF)
target_link_libraries(main ${CAO_LIBS})
```

above is the standard way to found **cao** from your system. 

all these feature has the same namespace of **cao**. so it can be called like this:

```
#include "cao/os.h"
#include "cao/colors.h"
#include "cao/random.h"

int main() {
    if (cao::os::exists(argv[1])) {
            cout << "- exist.\n";
            if (cao::os::isdir(argv[1])) {
                cout << colors::blue << "and this is a " << colors::bold << colors::yellow << "dir.\n";
            } else {
                cout << colors::blue << "this is a file, and file name is: \n";
                cout << "- file name is: " << colors::bold << colors::yellow << cao::os::filename(argv[1]) << endl;
            }
        } else {
            cout << "can not found.\n";
     }
}

```

Tada!! you just find a very tiny and easy-to-use assist APIs of C++!!



## Copyright

**cao** are released under Apache License 2.0, all rights reserved by *Jin Fagang*. Please use it under Apache License 2.0.