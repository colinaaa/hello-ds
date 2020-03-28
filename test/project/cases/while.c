void foo() {
	return;
}
int main()
{
	int x;
	int* y;
	while(!!x && --y || x & 0xff) {
		++x;
		if (x)
			continue;
		else {
			++x;
			x = *--y ^ 0xcf;
		}
		x = x + *++y;
	}

	while(1)
		foo();
	return 0;
}
