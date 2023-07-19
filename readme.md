# systrace_on_linux

Equivalent tool to systrace, tracing tool in Android Open Source Project, for PC-Linux.

## how to build

```
$ git clone https://XT-SDI-WG-ba42002zz@dev.azure.com/XT-SDI-WG-ba42002zz/linux_performance_engineering_Confidential/_git/systrace_on_linux
$ cd systrace_on_linux
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## run sample apps
There's two sample applications; main, written in C and main_cpp, written in C++.
Both of them loop infinitely, and write some trace_marker messages in each loop.
```
$ cd systrace_on_linux/build
# ./main

or

# ./main_cpp
```

## how to get a trace

```
$ cd systrace_on_linux
# ./get_trace 5 > trace.txt
```

## how to see the trace
1. Go to [Perfetto UI](https://ui.perfetto.dev/)
2. Select "Open trace file" in the left-hand side and specify the trace file.

