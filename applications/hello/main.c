#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>

void handler(int signo)
{
    int a;
    scanf("%d", &a);
    printf("handler: signo=%d\n", signo);
    printf("you input a=%d\n", a);
}

int main()
{
    sigset_t mask = 1 << 30;
    sigprocmask(SIG_SETMASK, &mask, NULL);
    signal(SIGUSR1, handler);
    printf("main()\n");
    kill(getpid(), SIGUSR1);
    printf("return to main()\n");
    // sigset_t set = (1 << (SIGUSR1));
    // sys_sigprocmask(SIG_SETMASK, &set, NULL);
    // sys_signal(SIGUSR1, handler);
    // printf("main()\n");
    // sys_kill(sys_getpid(), SIGUSR1);
    // printf("return to main()\n");
    return 0;
}