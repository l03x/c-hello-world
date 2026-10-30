long print(const char *str);

int main(void)
{
    print("Hello world\n");
    return 0;
}

#if defined(__x86_64__)

// x86-64 Linux
long print(const char *str)
{
    long ret;
    long len;
    for (len = 0; str[len] != '\0'; len++)
    {
    }

    __asm__ volatile(
        "syscall"
        : "=a"(ret)
        : "a"(1),
          "D"(1),
          "S"(str),
          "d"(len)
        : "rcx", "r11", "memory");
    return ret;
}

#elif defined(__i386__)

// x86 32-bit Linux
long print(const char *str)
{
    long ret;
    long len;
    for (len = 0; str[len] != '\0'; len++)
    {
    }

    __asm__ volatile(
        "int $0x80"
        : "=a"(ret)
        : "a"(4),
          "b"(1),
          "c"(str),
          "d"(len)
        : "memory");
    return ret;
}

#elif defined(__aarch64__)

// ARM64 Linux
long print(const char *str)
{
    long len;
    for (len = 0; str[len] != '\0'; len++)
    {
    }

    register long x0 __asm__("x0") = 1;
    register long x1 __asm__("x1") = (long)str;
    register long x2 __asm__("x2") = len;
    register long x8 __asm__("x8") = 64;
    __asm__ volatile(
        "svc #0"
        : "+r"(x0)
        : "r"(x1),
          "r"(x2),
          "r"(x8)
        : "memory");
    return x0;
}

#elif defined(__arm__)

// ARM 32-bit Linux (EABI)
long print(const char *str)
{
    long len;
    for (len = 0; str[len] != '\0'; len++)
    {
    }

    register long r0 __asm__("r0") = 1;
    register long r1 __asm__("r1") = (long)str;
    register long r2 __asm__("r2") = len;
    __asm__ volatile(
        "push {r7}\n"
        "mov r7, #4\n"
        "svc #0\n"
        "pop {r7}"
        : "+r"(r0)
        : "r"(r1),
          "r"(r2)
        : "memory");
    return r0;
}

#elif defined(__riscv) && __riscv_xlen == 64

// RISC-V 64-bit Linux
long print(const char *str)
{
    long len;
    for (len = 0; str[len] != '\0'; len++)
    {
    }

    register long a0 __asm__("a0") = 1;
    register long a1 __asm__("a1") = (long)str;
    register long a2 __asm__("a2") = len;
    register long a7 __asm__("a7") = 64;
    __asm__ volatile(
        "ecall"
        : "+r"(a0)
        : "r"(a1),
          "r"(a2),
          "r"(a7)
        : "memory");
    return a0;
}

#else
#error "unsupported architecture"
#endif
