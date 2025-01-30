#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "halde.h"

int main(int argc, char *argv[]) {
	halde_print();
	//char* m1 = halde_malloc(200*1024);
	char *m2 = halde_malloc(1024*1024 - 16);
	halde_print();
	//halde_free(m1);
	//char *m3 = halde_malloc(0);
	halde_print();

	exit(EXIT_SUCCESS);
}
