# WiP

## Table of Contents
- [1-About](#1-about)
- [2-Usage](#2-usage)
- [3-Technologies](#3-technologies)
- [4-Instalation](#4-instalation)
- [5-Preparation to compilation](#5-preparation-to-compilation)
- [6-Demo](#6-demo)
- [7-TODO](#7-todo)

## 1-About:
WiP - Work in Progress is a Windows application created with Qt framework.

## 2-Usage:
Application designed for organizations (companies) to manage team work in projects.
The main purpose is to control working time for individual tasks.

## 3-Technologies:
Qt Creator 4.14.0 on Windows 10\
with Qt 5.15.2 release

## 4-Instalation:
Download [ZIP](https://github.com/CodeBau/WiP/archive/master.zip)\
after unzipping open file `WiP.pro` with Qt Creator (see Technologies)\
configure project with `Desktop Qt 5.15.2 MSVC2019 64bit` kit


## 5-Preparation to compilation:
Use `Rename` function from Qt Creator and remove `_e` from files:\
`config_e.h`\
`fragile_e.h`\
`hash_e.h`\
`config_e.cpp`\
`hash_e.cpp`

Next uncomment `(/*...*/)` the commented code from these files.

In file: `WiP.pro` remove duplicates.
```diff
SOURCES += \
    ...
    Source/config.cpp \
-   Source/config.cpp \
    Source/hash.cpp \
-   Source/hash.cpp \
   ...
   
HEADERS += \
    ...
    Headers/api_process.h \
    Headers/config.h \
-   Headers/config.h \
    Headers/fragile.h \
-   Headers/fragile.h \
    Headers/hash.h \
-   Headers/hash.h \
    ...
```
to work properly with MySQL, you must enter the appropriate values in the appropriate fields in the `fragile.h` file
```diff
const char DbHost[]{ "localhost" };   //Internet address or IP address of the MySQL server
const char DbUser[]{ "root" };        //DataBase username
const char DbPsw[]{ "passwd" };       //DataBase password
const char DbName[]{ "database" };    //DataBase name
```
## 6-Demo: 
Film z działania aplikacji.

## 7-TODO:

https://github.com/RichardLitt/standard-readme#install
