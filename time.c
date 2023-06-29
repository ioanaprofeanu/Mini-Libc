// SPDX-License-Identifier: BSD-3-Clause

#include <time.h>
#include <errno.h>
#include <internal/syscall.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	// make the system call
	long syscall_result = syscall(SYS_NANOSLEEP, req, rem);

	// check for errors
	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return 0;
}

unsigned int sleep(unsigned int seconds)
{
	struct timespec ts = { seconds, 0 };
	struct timespec rem;

	// call the nanosleep function
	int nanosleep_result = nanosleep(&ts, &rem);
	// if it failed, return the remaining time
	if (nanosleep_result == -1)
		return rem.tv_sec;

	return 0;
}
