#include <stdio.h>
#include <stdlib.h>

#include "type.h"
#include "fuzzy.h"

int main(int argc, char *argv[])
{
	int16 in1, in2;

	if (argc < 3)
	{
		printf("Usage: %s <input1> <input2>\n", argv[0]);
		exit(1);
	}

    in1 = atoi(argv[1]);
    in2 = atoi(argv[2]);

    printf("%u\n", fuzzy_controller(in1, in2));
    
    return 0;
}
