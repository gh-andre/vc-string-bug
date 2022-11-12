#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <new>

std::string get_s(void)
{
    return "Thumbnail";
}

int main(void)
{
    char buf[64];
    memset(buf, 0xff, sizeof(buf));

    std::string* s = new (buf) std::string(get_s());
    printf("%s\n", s->c_str());

    for(size_t i = 0; i < sizeof(buf); i++) {
       if(i && i % 16 == 0)
          printf("\n");
       printf("%02hhx ", buf[i]);
    }
    printf("\n");

    s->std::string::~string();
    return EXIT_SUCCESS;
}
