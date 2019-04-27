#include <unistd.h>
#include <sys/syscall.h>

void foo(char const* ptr, size_t len) noexcept
{
    register unsigned long long rax asm("rax");
    register unsigned long long rdi asm("rdi");
    register void const* rsi asm("rsi");
    register unsigned long long rdx asm("rdx");

    rax = SYS_write;
    rdi = 1;
    rsi = ptr;
    rdx = len;
    asm("syscall");
}
