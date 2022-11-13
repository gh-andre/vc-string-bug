#ifndef VC_TEMP_STR_BUG_MAKE_TEMP_STRING_H
#define VC_TEMP_STR_BUG_MAKE_TEMP_STRING_H

#include <string>

namespace vc_tmp_str_bug {
struct X {
   std::string sx;
   const char *sptr;
   X(const std::string& s, char buf[128]);
};
__declspec(noinline) const char *get_s(void);
int make_temp_string(void);
}

#endif // VC_TEMP_STR_BUG_MAKE_TEMP_STRING_H
