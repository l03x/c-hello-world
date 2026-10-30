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

int main(void)
{
    print("Hello world\n");
    return 0;
}