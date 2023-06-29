// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>
#include <stdlib.h>

char *strcpy(char *destination, const char *source)
{
	// copy the data from source to destintion,
	// until reaching the null terminator
	while (*source != '\0') {
		*destination = *source;
		source++;
		destination++;
	}
	// add null terminator
	*destination = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t j = 0;
	// copy the data from source to destination (first len characters)
	for (size_t i = 0; i < len; i++) {
		destination[i] = source[i];
		j = i;
		if (source[i + 1] == '\0') {
			break;
		}
	}

	// if there size of the source is less than
	// the size of len, add null terminator
	for (size_t i = j + 1; i < len; i++) {
		destination[i] = '\0';
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	// reach the end of the destination string
	while (*destination != '\0') {
		destination++;
	}

	// copy the data from source at the end of the destination string
	while (*source != '\0') {
		*destination = *source;
		source++;
		destination++;
	}
	// add null terminator
	*destination = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	// reach the end of the destination string
	while (*destination != '\0') {
		destination++;
	}

	// copy the data from source at the end of the
	// destination string (first len characters)
	for (size_t i = 0; i < len; i++) {
		*destination = *source;
		source++;
		destination++;
		if (*source == '\0') {
			break;
		}
	}
	// add null terminator
	*destination = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	// iterate through the two strings until reaching the null terminator
	// while checking if the characters are the same
	while (*str1 != '\0' || *str2 != '\0') {
		if (*str1 > *str2) {
			return 1;
		}
		if (*str1 < *str2) {
			return -1;
		}
		str1++;
		str2++;

		// verify if we reached the end of any of the strings
		if (*str1 == '\0' && *str2 == '\0') {
			return 0;
		}
		if (*str1 != '\0' && *str2 == '\0') {
			return 1;
		}
		if (*str1 == '\0' && *str2 != '\0') {
			return -1;
		}
	}

	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	// iterate through the first len characters of the two strings
	// while checking if the characters are the same
	for (size_t	i = 0; i < len; i++) {
		if (str1[i] > str2[i]) {
			return 1;
		}
		if (str1[i] < str2[i]) {
			return -1;
		}
		if (str1[i] == '\0' && str2[i] == '\0') {
			return 0;
		}
	}
	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	char *aux_str = (char *)str;
	// iterate through str until reaching the c character
	// or the null terminator
	while (*aux_str != '\0') {
		// check if the current character is the c character
		if (*aux_str == c) {
			return aux_str;
		}
		aux_str++;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	// keep a variable with the last occurence of c
	char *c_last_occurence = NULL;
	char *aux_str = (char *)str;

	// iterate through str until reaching the null terminator; if the c
	// character is reached, update the variable with the last occurence
	while (*aux_str != '\0') {
		if (*aux_str == c) {
			c_last_occurence = aux_str;
		}
		aux_str++;
	}

	return c_last_occurence;
}

char *strstr(const char *haystack, const char *needle)
{
	// data about the occurence of the needle
	int found_start_sequence = 0;
	char *start_sequence = NULL;
	int needle_index = 0;

	while (*haystack != '\0') {
		// if the start of the needle has not been found, check if the current
		// haysack character is the first character of the needle
		if (found_start_sequence == 0) {
			if (*haystack == needle[0]) {
				found_start_sequence = 1;
				start_sequence = (char *)haystack;
				needle_index++;
			}
		// otherwise
		} else {
			// check if the current haystack character is current
			// character of the needle
			if (*haystack == needle[needle_index]) {
				needle_index++;
			} else {
				// start over
				found_start_sequence = 0;
				needle_index = 0;
				start_sequence = NULL;
			}
		}

		haystack++;
		// check if we reached the end of the needle
		if (needle[needle_index] == '\0') {
			break;
		}
	}

	return start_sequence;
}

char *strrstr(const char *haystack, const char *needle)
{
	// data about the occurence of the needle
	int found_start_sequence = 0;
	char *start_sequence = NULL;
	char *last_start_sequence = NULL;
	int needle_index = 0;

	while (*haystack != '\0') {
		// if the start of the needle has not been found, check if the current
		// haysack character is the first character of the needle
		if (found_start_sequence == 0) {
			if (*haystack == needle[0]) {
				found_start_sequence = 1;
				start_sequence = (char *)haystack;
				needle_index++;
			}
		// otherwise
		} else {
			// check if the current haystack character is current
			// character of the needle
			if (*haystack == needle[needle_index]) {
				needle_index++;
			// start over
			} else {
				found_start_sequence = 0;
				needle_index = 0;
				start_sequence = NULL;
			}
		}

		haystack++;
		// check if we reached the end of the needle and if so,
		// update the last start sequence and start over
		if (needle[needle_index] == '\0') {
			last_start_sequence = start_sequence;
			found_start_sequence = 0;
			start_sequence = NULL;
			needle_index = 0;
		}
	}

	return last_start_sequence;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	// copy the source to the destination; cast to char* to
	// iterate through the bytes
	for (size_t i = 0; i < num; i++) {
		*((char *)destination + i) = *((char *)source + i);
	}
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	// check if the two are the same
	if ((char *) destination == (char *) source) {
		return destination;
	}

	// if dest is greater than source, iterate forwards
	if ((char *) destination < (char *) source) {
		for (size_t i = 0; i < num; i++) {
			*((char *) destination + i) = *((char *) source + i);
		}
	// if dest is smaller than source, iterate backwards
	} else {
		for (size_t i = num; i > 0; i--) {
			*((char *) destination + i - 1) = *((char *) source + i - 1);
		}
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	// iterate through the first num bytes of the two areas,
	// each interpreted as unsigned char
	for (size_t i = 0; i < num; i++) {
		// if the current first byte is greater than the second one
	   	if (((const unsigned char *)ptr1)[i] > ((const unsigned char *)ptr2)[i]) {
			return 1;
		}
		// if the current first byte is smaller than the second one
		if (((const unsigned char *)ptr1)[i] < ((const unsigned char *)ptr2)[i]) {
			return -1;
		}
	}

	// if the two memory areas are equal
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	// iterate through the first num bytes of the source area
	for (size_t i = 0; i < num; i++) {
		// set the current byte to the value
		((char *)source)[i] = value;
	}

	return source;
}
