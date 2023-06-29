// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	// make the system call
	long syscall_result = syscall(SYS_LSEEK, fd, offset, whence);

	// check for errors
	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return (off_t)syscall_result;
}
