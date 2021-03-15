#include <syscall.h>
#include <string.h>

#define RT_ARG_MAX  8

extern int main(int argc, char *argv[]);

__attribute__((noreturn))
void _start(void)
{
    int argc;
    char *argv[RT_ARG_MAX];

    memset(argv, 0, sizeof(argv));

    sys_dlmodule_init(&argc, argv);
    main(argc, argv);
    sys_dlmodule_cleanup();
    sys_exit();

    /* !!! should not reach there !!! */
    while(1);
}