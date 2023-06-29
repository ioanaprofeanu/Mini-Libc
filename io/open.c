// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	// retrieve mode variable in case of new file creation
	mode_t mode = 0;
	va_list args;

	// if the file does not exist
	if ((O_CREAT & flags) == 0) {
		// retrieve the mode argument
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
	}

	// the return of the syscall is a file descriptor
	long fd = syscall(SYS_OPEN, filename, flags, mode);

	// check for errors
	if (fd < 0) {
		errno = -fd;
		return -1;
	}

	return fd;
}
