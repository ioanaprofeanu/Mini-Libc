// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *malloc(size_t size)
{
	// allocate memory for the new memory block
	void *new_address = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_address == MAP_FAILED) {
		return NULL;
	}

	// initialize list if it is empty
	if (mem_list_num_items() == 0) {
		mem_list_init();
	}

	// add the new memory block to the list
	int result = mem_list_add(new_address, size);
	if (result == -1) {
		return NULL;
	}

	return new_address;
}

void *calloc(size_t nmemb, size_t size)
{
	// call the malloc function
	return malloc(nmemb * size);
}

void free(void *ptr)
{
	// delete the memory (both the memory block and the list element)
	mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	// find the memory block in the list
	struct mem_list *find_element = mem_list_find(ptr);

	// reallocate memory for the block
	void *new_address = mremap(ptr, find_element->len, size, MREMAP_MAYMOVE);
	if (new_address == MAP_FAILED) {
		return NULL;
	}

	// update the list element
	find_element->len = size;
	find_element->start = new_address;
	return new_address;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	// call the realloc function
	return realloc(ptr, nmemb * size);
}
