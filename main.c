/*
% gcc -Wall -o trace_marker main.c -ltrace -L. -Wl,-rpath=`pwd`
*/
#include "trace.h"

#include <unistd.h>

TRACE_PREPARE();

int main()
{
	int cnt = 0;
	int64_t v1 = 1, v2 = 2;

	TRACE_INIT();

	while(1) {
		TRACE_WRITE_BEGIN("trace_marker.c: cnt=%d", cnt++);
		TRACE_WRITE_I64("value1", v1);
		sleep(1);
		TRACE_WRITE_END();
		TRACE_WRITE_I64("value2", v2);
		sleep(1);
		v1 += 1;
		v2 += 2;
	}

	return 0;
}
