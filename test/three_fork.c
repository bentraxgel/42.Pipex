// dup2로 outfile만드는 코드이긴한데... 뭐 아무것도 안됨.
// 근데 이거 참고해서 내가 짜보면 해결될것같아
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main() {
    int in, outfile_fd;
    int fd[2];
    pid_t pid[3];

    // infile 열기
    in = open("infile", O_RDONLY);
    if (in == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 파이프 생성
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 자식 프로세스 생성
    for (int i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid[i] == 0) {
            // 자식 프로세스
            close(fd[READ]);
            if (i < 2) {
                // 출력을 파이프에 연결
                dup2(fd[WRITE], STDOUT_FILENO);
            } else {
                // 출력을 outfile_fd에 연결
                outfile_fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (outfile_fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(outfile_fd, STDOUT_FILENO);
                close(outfile_fd);
            }

            // 자식 프로세스의 입력을 infile으로 리디렉션
            dup2(in, STDIN_FILENO);

            // 실행할 명령어
            char *cmd[] = {"cat", "-e", NULL};
            execve("/bin/cat", cmd, NULL);

            // execve 호출이 실패한 경우
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }

    // 파이프와 infile을 닫기
    close(fd[WRITE]);
    close(fd[READ]);
    close(in);

    // 자식 프로세스들의 종료를 기다리기
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}
