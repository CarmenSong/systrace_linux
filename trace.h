#ifndef TRACE__H
#define TRACE__H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <sys/types.h>
#include <stdio.h>

#define TRACING_MSG_LEN (1024)

typedef struct {
	int fd_marker;
	//int fd_on;
} trace_handle_t;

int trace_init(trace_handle_t *handle);
int trace_write_int64(trace_handle_t *handle, const char *name, int64_t value);
int trace_write_end(trace_handle_t *handle);

#define TRACE_PREPARE() \
	trace_handle_t trace_handle_instance;

#define TRACE_INIT() \
	if ( trace_init(&trace_handle_instance) < 0 ) { \
		return 1; \
	}

#define TRACE_WRITE_BEGIN(FMT, ...) \
{ \
	char buf[TRACING_MSG_LEN]; \
	int len = snprintf(buf, sizeof(buf), "B|%d|" FMT, getpid(), __VA_ARGS__); \
	write(trace_handle_instance.fd_marker, buf, len); \
}

#define TRACE_WRITE_I64(name, value) \
	trace_write_int64(&trace_handle_instance, name, value)

#define TRACE_WRITE_END() \
	trace_write_end(&trace_handle_instance)

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // TRACE__H
