int _X;
int Y;

#include <stdio.h>

#define N 4
#define ADD(x, y) ((x) + (y))

int foo(int x) {
	x = x | 0xcd ^ 0xab << 31;
	x = x >> 0x10;
	return ++x;
}

int main()
{
	int x;
	int y;
	int *p;
	x = 0xff & -1; // some comment
	y = -x || (x + 4);

	y = (int)(x + sizeof(int**));

	Y = x - sizeof(char);

	p[1] = !30 >> -0777;

	// other  loooooooooooooooooooooooong comment
	x = !x - ~y / (y * x);
	return 0;
}
