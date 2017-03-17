__attribute__((noinline)) int test_1()
{
  return 42;
}

__attribute__((noinline)) int test_2()
{
  return 24;
}

int main()
{
  test_1();
  test_2();
}
