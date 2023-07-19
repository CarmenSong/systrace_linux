/*
% g++ -Wall -fPIC -shared -o libtrace_helper.so trace_helper.cpp
*/
#include "trace_helper.h"

#include <errno.h>
#include <stdexcept>

TraceManager::TraceManager()
{
	if (trace_init(&handle) < 0) {
		throw std::runtime_error(strerror(errno));
	}
}

TraceManager &TraceManager::get_instance()
{
	static TraceManager instance;
	return instance;
}

int TraceRecorder::write_value(const char *name, int64_t value) {
	return trace_write_int64(TraceManager::get_instance().get_handle(), name, value);
}

TraceRecorder::~TraceRecorder() {
	trace_write_end(TraceManager::get_instance().get_handle());
}

void TraceRecorder::write_record(const char *p, size_t len)
{
	write(TraceManager::get_instance().get_handle()->fd_marker, p, len);
}
