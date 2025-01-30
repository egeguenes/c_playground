#include "halde.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>

/// Magic value for occupied memory chunks.
#define MAGIC ((void*)0xbaadf00d)

/// Size of the heap (in bytes).
#define SIZE (1024*1024*1)

/// Memory-chunk structure.
struct mblock {
	struct mblock *next;
	size_t size;
	char memory[];
};

/// Canary wrapper around the memory
struct canary {
	char mem[SIZE];
	int can;
};
struct canary canary = {.mem={0},.can = 0xdeadb33f};

/// Heap-memory area. Due to the conversion sizeof(memory) does not work, sizeof(canary.mem) works.
char *memory = (char *) canary.mem;

/// Pointer to the first element of the free-memory list. head is a pointer!
static struct mblock *head;

/// Helper function to visualise the current state of the free-memory list.
void halde_print(void) {
	struct mblock* lauf = head;

	// Empty list
	if ( head == NULL ) {
		fprintf(stderr, "(empty)\n");
		return;
	}

	// Print each element in the list
	fprintf(stderr, "HEAD:  ");
	while ( lauf ) {
		fprintf(stderr, "(addr: 0x%08zx, off: %7zu, ", (uintptr_t) lauf, (uintptr_t)lauf - (uintptr_t)memory);
		fflush(stderr);
		fprintf(stderr, "size: %7zu)", lauf->size);
		fflush(stderr);

		if ( lauf->next != NULL ) {
			fprintf(stderr, "\n  -->  ");
			fflush(stderr);
		}
		lauf = lauf->next;
	}
	fprintf(stderr, "\n");
	fflush(stderr);
}

// it allocates size bytes for an unknown pointer, if it is not allocated returns NULL otherwise the pointer
void *halde_malloc (size_t size) {
    // TODO: implement me!
    if (size == 0) {
        return NULL;
    }

    // inits the head if it is not inited before
    if (head == NULL) {
        head = (struct mblock *)memory;
        head->size = SIZE - sizeof(struct mblock);
        head->next = NULL;
    }

    size_t total_size = size + sizeof(struct mblock);

    // size to allocate is more than the max size
    if (total_size > SIZE) {
        errno = ENOMEM;
        return NULL;
    }



    // can debug check
    if (canary.can != 0xdeadb33f) {
        errno = ENOMEM;
        return NULL;
    }

    // a pointer to head, to make sure we dont change head by accident
    struct mblock *current = head;

    // as long as we have a current pointer(when it is not NULL)
    while (current) {
        // if we have exactly! amount of size free, then we allocate it all
        if (current->size == size) {
            // current should not be already allocated
            if (current->next == (struct mblock *)MAGIC) {
                errno = ENOMEM;
                return NULL;
            }
            //head = current->next; // head shows the next of current
            //current->size = size; // size of current would be size it is clear
            current->next = (struct mblock *)MAGIC; // current is full now, so magic number will be the next pointer of it
            if (canary.can != 0xdeadb33f) { // debugging
                errno = ENOMEM;
                return NULL;
            }
            return current->memory; // returning memory of current
        }

        // if size of current is more than size and there is plenty room for one more struct mblock
        if (current->size >= size + sizeof(struct mblock)) {
            // struct mblock init, the address of new would be currents adress + totalsize(sizeof struct mblock + actual size)
            struct mblock *new = (struct mblock *)((char *)current + total_size);
            new->size = current->size - total_size; // when we allocate totalsize elements, the not used  size would be the whole - totalsize
            current->size = size; // current is allocated by size memory
            new->next = current->next; // next element of new would be the currents next element
            head = new; // head is now the new mblock
            current->next = (struct mblock *)MAGIC; // new is allocated, so would be marked
            if (canary.can != 0xdeadb33f) { // debugging
                errno = ENOMEM;
                return NULL;
            }
            return current->memory;
        }
        current = current->next; // there couldnt be enough room found in the current element, so check the size of next element
    }
    errno = ENOMEM; // couldnt find any room at all
    return NULL;
}


void halde_free (void *ptr) {
    //MERGE_NOT_IMPLEMENTED_MARKER: remove this line to activate merge related test cases

	// TODO: implement me!
	// if the pointer is not initted or the size of it already more than the SIZE, give error and return nothing
	if (ptr == NULL || sizeof(ptr) > SIZE) {
	    errno = 23;
	    return;
	}

	// create a new block, the size to be freed is the size of ptr element - the size of struct mblock
	struct mblock *data = (struct mblock *)((char *)ptr - sizeof(struct mblock));

	// checking if data is allocated, which means the next of it should be magic number
	if (data->next != (struct mblock *)MAGIC) {
	   abort();
	}

	// as we freed space, the next should be pointing the head and head should be the freed space
	data->next = head;
	head = data;
}
