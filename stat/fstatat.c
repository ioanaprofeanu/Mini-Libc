// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/types.h>
#include <unistd.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

#define makedev(x, y) ( \
		(((x)&0xfffff000ULL) << 32) | \
	(((x)&0x00000fffULL) << 8) | \
		(((y)&0xffffff00ULL) << 12) | \
	(((y)&0x000000ffULL)) \
	)

/* Structure describing file characteristics as defined in linux/stat.h */
struct statx {
	uint32_t stx_mask;
	uint32_t stx_blksize;
	uint64_t stx_attributes;
	uint32_t stx_nlink;
	uint32_t stx_uid;
	uint32_t stx_gid;
	uint16_t stx_mode;
	uint16_t pad1;
	uint64_t stx_ino;
	uint64_t stx_size;
	uint64_t stx_blocks;
	uint64_t stx_attributes_mask;
	struct {
		int64_t tv_sec;
		uint32_t tv_nsec;
		int32_t pad;
	} stx_atime, stx_btime, stx_ctime, stx_mtime;
	uint32_t stx_rdev_major;
	uint32_t stx_rdev_minor;
	uint32_t stx_dev_major;
	uint32_t stx_dev_minor;
	uint64_t spare[14];
};

int fstatat_statx(int fd, const char *restrict path, struct stat *restrict st, int flag) {
	struct statx statbuf;
	long syscall_result = syscall(SYS_STATX, fd, path, flag, 2048, &statbuf);

	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	// convert statx to stat in the structure
	st->st_dev = makedev(statbuf.stx_dev_major, statbuf.stx_dev_minor);
	st->st_ino = statbuf.stx_ino;
	st->st_mode = statbuf.stx_mode;
	st->st_nlink = statbuf.stx_nlink;
	st->st_uid = statbuf.stx_uid;
	st->st_gid = statbuf.stx_gid;
	st->st_rdev = makedev(statbuf.stx_rdev_major, statbuf.stx_rdev_minor);
	st->st_size = statbuf.stx_size;
	st->st_blksize = statbuf.stx_blksize;
	st->st_blocks = statbuf.stx_blocks;
	st->st_atime = statbuf.stx_atime.tv_sec;
	st->st_mtime = statbuf.stx_mtime.tv_sec;
	st->st_ctime = statbuf.stx_ctime.tv_sec;

	return 0;
}

int fstatat(int fd, const char *restrict path, struct stat *restrict st, int flag)
{
	// use the fstatat_statx function
	long syscall_result = fstatat_statx(fd, path, st, flag);

	// check for errors
	if (syscall_result < 0) {
		errno = -syscall_result;
		return -1;
	}

	return 0;
}
