// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <internal/io.h>

int puts(const char *str)
{
	// write the string to stdout and add a newline
	size_t ret = write(1, str, strlen(str)) + write(1, "\n", 1);

	// check if the write was successful
	if (ret == strlen(str) + 1)
		return ret;
	else
		return -1;
}
