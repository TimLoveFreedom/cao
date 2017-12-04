cmake_minimum_required(VERSION 3.8)
project(cao VERSION 1.0.1 LANGUAGES CXX )
set(CMAKE_CXX_STANDARD 11)


include(GNUInstallDirs)
add_library(cao SHARED lib/log.cpp lib/os.cpp
        lib/random.cpp lib/str_util.cpp)
set_target_properties(cao PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER "include/colors.h;include/log.h;include/os.h;include/random.h;include/str_util.h")

set(BUILD_SHARED_LIBS OFF)

configure_file(cao.pc.in cao.pc.in @ONLY)
target_include_directories(cao PRIVATE .)

install(TARGETS cao
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cao)

# install pc for pkg-config configuration
install(FILES include/cao.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
