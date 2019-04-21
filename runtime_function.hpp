#ifndef RUNTIME_FUNCTION_H
#define RUNTIME_FUNCTION_H

#include <sys/mman.h>

#include <algorithm>

template<typename T>
struct runtime_function
{};

template<typename R, typename... Args>
struct runtime_function<R(*)(Args...)>
{
    using func_t = R(*)(Args...);

    template<typename ConstInputIterator>
    runtime_function(ConstInputIterator it,
                     size_t count) noexcept(noexcept(*it))
        : cnt(count)
    {
        ptr = mmap(nullptr, count, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        if (ptr == MAP_FAILED)
        {
            ptr = nullptr;
            return;
        }

        std::copy_n(it, count, reinterpret_cast<unsigned char*>(ptr));

        mprotect(ptr, count, PROT_READ | PROT_EXEC);
    }

    template<typename... Argv>
    R execute(Argv&&... args) const
    {
        auto f = reinterpret_cast<func_t>(ptr);
        return f(std::forward<Argv>(args)...);
    }

    ~runtime_function() noexcept
    {
        if (ptr != nullptr)
            munmap(ptr, cnt);
    }

private:
    void* ptr;
    size_t cnt;
};

#endif // RUNTIME_FUNCTION_H
