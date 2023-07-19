/*
% gcc -Wall -fPIC -shared -o libtrace.so trace.c
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "trace.h"

static char fmt_i64[] = "C|%d|%s|%d";
static char fmt_e[] = "E";

int trace_init(trace_handle_t *handle)
{
	/*
	if ( (handle->fd_on = open("/sys/kernel/debug/tracing/tracing_on", O_RDONLY | O_CLOEXEC)) == -1) {
		perror("trace_init: failed to open tracing_on");
		return -1;
	}
	*/

	if ( (handle->fd_marker = open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY | O_CLOEXEC)) == -1) {
		perror("trace_init: failed to open trace_marker");
	}
	return handle->fd_marker;
}

int trace_write_int64(trace_handle_t *handle, const char *name, int64_t value)
{
	char buf[TRACING_MSG_LEN];
	int len;

	//if (trace_check_on(handle) <= 0) return -1;
 	len	= snprintf(buf, sizeof(buf), fmt_i64, getpid(), name, value);
	return write(handle->fd_marker, buf, len);
}

int trace_write_end(trace_handle_t *handle)
{
	//if (trace_check_on(handle) <= 0) return -1;
	return write(handle->fd_marker, fmt_e, 1);
}

