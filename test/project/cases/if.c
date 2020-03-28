void foo() {}
int main() {
  int x;
  if (x || x & 0xff)
    x = 1 + 3 + 4 + 5;  // should be optimized
  else {
    ++x;
  }

  if (1) {
    x = 1 && 2 || 3 ^ 0xabcd;
  } else
    foo();

  return 0;
}
