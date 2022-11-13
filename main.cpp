#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <new>
#include <memory.h>

const char *get_s(void)
{
  return "Thumbnail";
}

__declspec(noinline) void *filler(void)
{
   volatile char fil[128];
   for(size_t i = 0; i < sizeof(fil); i++)
      *(fil+i) = '\xff';
   return (void*) fil;
}

__declspec(noinline) const char * copier(const std::string& s, char buf[128])
{
    strcpy(buf, s.c_str());
    return s.c_str();
}

__declspec(noinline) const char *printer_caller(char buf[128])
{
   volatile char fil[32];
   for(size_t i = 0; i < sizeof(fil); i++)
      *(fil+i) = '\xaa';
   return copier(get_s(), buf);
}

int main(void)
{
    std::unique_ptr<char[]> buf(new char[128]);
    std::unique_ptr<char[]> filcpy(new char[128]);

    const void *fil = filler();

    const char *s = printer_caller(buf.get());

    memcpy(filcpy.get(), fil, 128);

    for(size_t i = 0; i < 128; i++) {
     if(i && i % 16 == 0)
        printf("\n%08p: ", (filcpy.get() + i));
     printf("%02hhx ", *(filcpy.get() + i));
    }
    printf("\n");

    printf("Thumbnail: %08p (%s)\n", s, buf.get());

    return EXIT_SUCCESS;
}
