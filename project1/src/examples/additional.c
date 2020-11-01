#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>

int main(int argc, char **argv) {
	int a, b, c, d, _fibo, _max;

	if (argc != 5) {
		printf("Input form is not vaild!\n");
		printf("Usage : additional a b c d\n");
		return EXIT_FAILURE;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = atoi(argv[3]);
	d = atoi(argv[4]);

	_fibo = fibonacci(a);
	_max = max_of_four_int(a, b, c, d);

	printf("%d %d\n", _fibo, _max);

	return EXIT_SUCCESS;
}