#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdint>

void print_s(uint16_t i, const std::string& s)
{
  printf("%s\n", s.c_str());
}

const char *get_s(void)
{
  return "Thumbnail";
}

int main(void)
{
  uint16_t i = 123;
  print_s(i, get_s());

  return EXIT_SUCCESS;
}
