// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <errno.h>
#include <internal/syscall.h>

int fstat(int fd, struct stat *st)
{
	// make the system call
	long syscall_result = syscall(SYS_FSTAT, fd, st);

	// check for errors
	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return 0;
}
