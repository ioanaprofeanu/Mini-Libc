// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	// make the system call
	long syscall_result = syscall(SYS_MMAP, addr, length, prot, flags, fd, offset);

	// check for errors
	if (syscall_result < 0) {
		errno = -syscall_result;
		return MAP_FAILED;
	}

	return (void *)syscall_result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	// make the system call
	long syscall_result = syscall(SYS_MREMAP, old_address, old_size, new_size, flags);

	// check for errors
	if (syscall_result < 0) {
		errno = -syscall_result;
		return MAP_FAILED;
	}

	return (void *)syscall_result;
}

int munmap(void *addr, size_t length)
{
	// make the system call
	long syscall_result = syscall(SYS_MUNMAP, addr, length);

	// check for errors
	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return 0;
}
