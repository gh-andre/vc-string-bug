#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <new>
#include <memory>

#include "make-temp-string.h"

namespace vc_tmp_str_bug {
   
struct info_t {
   const char *abc;
   const char *xyz;
   int i;
} info[] = {{"Image", "XYZ1", 1}, {"Thumbnail", "XYZ2", 2}};

__declspec(noinline) const char *get_s(void)
{
  return info[1].abc;
}

__declspec(noinline) void *filler(void)
{
   volatile char fil[128];
   for(size_t i = 0; i < sizeof(fil); i++)
      *(fil+i) = '<';
   return (void*) fil;
}

__declspec(noinline) void copier(const std::string& s, char buf[128])
{
    strcpy(buf, s.c_str());
    return s.c_str();
}

X::X(const std::string& s, char buf[128]) : sptr(s.c_str())
{
   copier(s, buf);
}
   
__declspec(noinline) const char *printer_caller(char buf[128])
{
   volatile char fil[32];
   for(size_t i = 0; i < sizeof(fil); i++)
      *(fil+i) = '>';
   X x(get_s(), buf);
   return x.sptr;
}

int make_temp_string(void)
{
    std::unique_ptr<char[]> buf(new char[128]);
    std::unique_ptr<char[]> filcpy(new char[128]);

    const void *fil = filler();

    const char *s = printer_caller(buf.get());

    memcpy(filcpy.get(), fil, 128);

    for(size_t i = 0; i < 128; i++) {
       if(i % 16 == 0)
          printf("\n%08p: ", (filcpy.get() + i));
     printf("%02hhx ", *(filcpy.get() + i));
    }
    printf("\n");

    printf("Thumbnail: %08p (%s)\n", s, buf.get());

    return EXIT_SUCCESS;
}

}
