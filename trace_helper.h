#ifndef TRACE_HELPER__H
#define TRACE_HELPER__H
#include "trace.h"

#include <utility>
#include <string.h>
#include <unistd.h>

class TraceManager
{
public:
	static TraceManager &get_instance();
	~TraceManager() = default;

	trace_handle_t *get_handle() {
		return &handle;
	}

private:
	TraceManager();

	trace_handle_t handle;
};

class TraceRecorder
{
public:
	template <typename... Args>
	TraceRecorder(const char *fmt, Args&&... args) {
		char buf[TRACING_MSG_LEN];
		int len = snprintf(buf, sizeof(buf), "B|%d|", getpid());
		len += snprintf(buf+len, sizeof(buf), fmt, std::forward<Args>(args)...);
		write_record(buf, len);
	}

	template <typename... Args>
	TraceRecorder(const char *str) {
		char buf[TRACING_MSG_LEN];
		int len = snprintf(buf, sizeof(buf), "B|%d|%s", getpid(), str);
		write_record(buf, len);
	}

	~TraceRecorder();

	int write_value(const char *name, int64_t value);

private:
	void write_record(const char *p, size_t len);
};

#endif // TRACE_HELPER__H
