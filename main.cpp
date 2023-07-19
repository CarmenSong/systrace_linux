/*
% g++ -Wall -o main_cpp main.cpp -L. -ltrace_helper -ltrace -Wl,-rpath=`pwd` -pthread
*/
#include "trace_helper.h"

#include <unistd.h>
#include <thread>

int main()
{
	TraceRecorder rec1("main");

	std::thread th([](){
		//for (int i = 0; i < 10; ++i) {
		int i = 0;
		while(true) {
			TraceRecorder rec("for: %d", i);
			rec.write_value("i", i++);
			usleep(100);
		}
	});

	th.join();
	return 0;
}
