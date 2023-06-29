// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	// make the system call
	long syscall_result = syscall(SYS_TRUNCATE, path, length);

	// check for errors
	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return 0;
}
