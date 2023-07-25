//  pipe를 fork할때마다 진행하는 코드.
// 그래도 이게 그나마 제일 잘 됨.
// execve(cmd)는 자식에서만 진행하고
// 부모에서는 바로 outfile에만 담기게하는게 더 나을 듯?
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
    int fd1[2], fd2[2];
    char buffer[BUFSIZ];
    pid_t pid1, pid2;

    in = open("infile", O_RDONLY);
    if (in == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // 자식 프로세스 1
        close(fd1[READ]);
        dup2(in, STDIN_FILENO);
        dup2(fd1[WRITE], STDOUT_FILENO);
        close(fd1[WRITE]);

        // 실행할 명령어
        char *cmd1[] = {"cat", "-e", NULL};
        execve("/bin/cat", cmd1, NULL);

        // execve 호출이 실패한 경우
        perror("execve");
        exit(EXIT_FAILURE);
    }

    if (pipe(fd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // 자식 프로세스 2
        close(fd1[WRITE]);
        close(fd2[READ]);
        dup2(fd1[READ], STDIN_FILENO);
        dup2(fd2[WRITE], STDOUT_FILENO);
        close(fd1[READ]);
        close(fd2[WRITE]);

        // 실행할 명령어
        char *cmd2[] = {"cat", "-e", NULL};
        execve("/bin/cat", cmd2, NULL);

        // execve 호출이 실패한 경우
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // 부모 프로세스
    close(fd1[READ]);
    close(fd1[WRITE]);
    close(fd2[WRITE]);

    // outfile 열기
    outfile_fd = open("outfile4", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 자식 프로세스 2에서 읽은 결과를 부모 프로세스에서 outfile에 쓰기
    // ssize_t nread;
    // while ((nread = read(fd2[READ], buffer, BUFSIZ)) > 0) {
    //     write(outfile_fd, buffer, nread);
    // }

	dup2(fd2[READ], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(fd2[READ]);
	char *cmd[] = {"cat", "-e", NULL};
	execve("/bin/cat", cmd, NULL);
    // 파일 닫기
    close(outfile_fd);
    // close(fd2[READ]);

    return 0;
}
