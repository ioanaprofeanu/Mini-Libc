/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __SYSCALL_H__
#define __SYSCALL_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/arch/x86_64/syscall_list.h>

long syscall(long n, ...);

#define SYS_READ 0
#define SYS_WRITE 1
#define SYS_OPEN 2
#define SYS_CLOSE 3
#define SYS_STAT 4
#define SYS_FSTAT 5
#define SYS_LSTAT 6
#define SYS_POLL 7
#define SYS_LSEEK 8
#define SYS_MMAP 9
#define SYS_MPROTECT 10
#define SYS_MUNMAP 11
#define SYS_BRK 12
#define SYS_MREMAP 25
#define SYS_NANOSLEEP 35
#define SYS_TRUNCATE 76
#define SYS_FTRUNCATE 77
#define SYS_STATX 332

#ifdef __cplusplus
}
#endif

#endif
