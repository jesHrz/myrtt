#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

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
    return 0;
}
