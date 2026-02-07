#
#  Project:  Kionix driver demo
#
#  SPDX-License-Identifiers: Apache-2.0, MIT license
#

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(kx132_demo)

target_sources(app PRIVATE
    src/main.c
)

## 2021-11-11
## https://stackoverflow.com/questions/31343813/displaying-cmake-variables

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

#print_all_variables()
