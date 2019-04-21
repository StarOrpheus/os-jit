#include "runtime_function.hpp"

template<size_t N>
constexpr inline size_t _strlen(const char(&str)[N])
{
    return N - 1;
}

constexpr static char const hello_world[] = "Hello world!\n";
constexpr static size_t len = _strlen(hello_world);

constexpr static unsigned char func_code[] =
{
    0x55,                           // push   %rbp
    0x48, 0x89, 0xe5,               // mov    %rsp,%rbp
    0x48, 0x89, 0x7d, 0xf8,         // mov    %rdi,-0x8(%rbp)
    0x48, 0x89, 0x75, 0xf0,         // mov    %rsi,-0x10(%rbp)
    0xb8, 0x01, 0x00, 0x00, 0x00,   // mov    $0x1,%eax
    0xbf, 0x01, 0x00, 0x00, 0x00,   // mov    $0x1,%edi
    0x48, 0x8b, 0x75, 0xf8,         // mov    -0x8(%rbp),%rsi
    0x48, 0x8b, 0x55, 0xf0,         // mov    -0x10(%rbp),%rdx
    0x0f, 0x05,                     // syscall
    0x90,                           // nop
    0x5d,                           // pop %rbp
    0xc3                            // retq
};

constexpr static size_t func_code_len = sizeof (func_code);
using func_t = void(*)(char const*, size_t);

int main()
{
    runtime_function<func_t> f(func_code, func_code_len);

    f.execute(hello_world, len);
    return 0;
}
