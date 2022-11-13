#ifndef VC_TEMP_STR_BUG_MAKE_TEMP_STRING_H
#define VC_TEMP_STR_BUG_MAKE_TEMP_STRING_H

#include <string>

namespace vc_tmp_str_bug {
struct X {
   // address of the string argument, which is a temporary in this test, created by the caller
   const char *sptr;
   
   X(const std::string& s, char buf[128]);
};

// mimics a real-life function that returns a static string
__declspec(noinline) const char *get_s(void);

// calls test functions that create a string temporary
void make_temp_string(void);
}

#endif // VC_TEMP_STR_BUG_MAKE_TEMP_STRING_H
