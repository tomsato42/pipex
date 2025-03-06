#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    char *argv[] = {"/bin/ls", "-l", NULL};
    char *envp[] = {NULL};
    pid_t pid;

    printf("元のプログラム開始: PID = %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // 子プロセスの処理
        printf("子プロセス実行中: PID = %d\n", getpid());
        printf("子プロセスでこれから execve() を実行します\n");
        printf("*** この下の行は execve が失敗した場合だけ表示されます ***\n");

        if (execve("/bin/ls", argv, envp) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }

        printf("この行は絶対に実行されません！\n");
        printf("なぜなら、execve が成功すると制御が戻ってこないからです\n");
        return 42; // この return も実行されません
    }
    else {
        // 親プロセスの処理
        int status;
        printf("親プロセス: 子プロセス (PID = %d) の終了を待機中...\n", pid);

        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("子プロセスは終了コード %d で終了しました\n", WEXITSTATUS(status));
        }

        printf("親プロセスの処理が続行します\n");
    }

    printf("元のプログラム終了\n");
    return 0;
}
