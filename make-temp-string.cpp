#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <memory>

#include "make-temp-string.h"

namespace vc_tmp_str_bug {

// mimics a real-life structure that supplies a source string
struct info_t {
   const char *abc;
   const char *xyz;
   int i;
} info[] = {{"Image", "XYZ1", 1}, {"Thumbnail", "XYZ2", 2}};

__declspec(noinline) const char *get_s(void)
{
  return info[1].abc;
}

// fills an area of the stack with a visible filler '<'
__declspec(noinline) const void *filler(void)
{
   volatile char fil[128];
   for(size_t i = 0; i < sizeof(fil); i++)
      *(fil+i) = '<';
   // should be used for debuggng only - will be overwritten
   return (const void*) fil;
}

// string s has length 9, but no null terminator and will pick up whatever follows those 9 characters
__declspec(noinline) void copier(const std::string& s, char buf[128])
{
    strcpy(buf, s.c_str());
}

// s is a temporary and its address should be used only for debugging; the string is copied into the buffer for printing
X::X(const std::string& s, char buf[128]) : sptr(s.c_str())
{
   copier(s, buf);
}

// creates an instance of X with a temporary std::string, which is incorrectly initialized
__declspec(noinline) const char *printer_caller(char buf[128])
{
   // fills memory above the original filler to make string initialization visible
   volatile char fil[32];
   
   for(size_t i = 0; i < sizeof(fil); i++)
      *(fil+i) = '>';
   
   // see main.cpp in the attached project for the bug description (not in this repo)
   X x(get_s(), buf);
   
   // should be used for debugging purposes only
   return x.sptr;
}

void make_temp_string(void)
{
   // use dynamic memory to preserve all filler bytes
   std::unique_ptr<char[]> buf(new char[128]);
   std::unique_ptr<char[]> filcpy(new char[128]);

   // can be used to view memory in debugger, as it gets used
   const void *fil = filler();

   // original string memory for debugging purposes - will be overwritten
   const char *s = printer_caller(buf.get());

   // copy the stack memory where the string is located, so printf doesn't trash it
   memcpy(filcpy.get(), fil, 128);

   // hex-dump copied stack to show incorrectly initialized string memory
   for(size_t i = 0; i < 128; i++) {
      if(i % 16 == 0)
         printf("\n%08p: ", (filcpy.get() + i));
      printf("%02hhx ", *(filcpy.get() + i));
   }
   printf("\n");

   // the address is in the original stack and the content is from the copied stack memory
   printf("string address: %08p content: (%s)\n", s, buf.get());
}

}
