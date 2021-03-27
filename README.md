# buflog
This is a simple bufferd logging library using ipc shared memory.
![build status](https://github.com/41nya/buflog/actions/workflows/main.yml/badge.svg)

## Build
```
cmake .
make
```

## Usage
```
#include "buflog.h"


std:string filename("/tmp/hello.log");
buflog::Logger logger(filename, 1024);
std::string log("Hello World!\n");
logger.Log(log);
logger.Flush();
```
