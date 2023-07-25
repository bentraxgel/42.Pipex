//  비동기적 프로세스에 대해 알아봐서 사용해야함 - wait, waitpid
// 지금은 결과물이 어떤 때마다 터미널, outfile에 따로 나옴.

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
    char buffer[BUFSIZ];
    pid_t pid1, pid2;

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

    // 첫 번째 자식 프로세스 생성
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // 자식 프로세스 1
        close(fd[READ]);
        // 자식 프로세스 1의 입력을 infile로 리디렉션하고, 출력을 파이프에 연결
        dup2(in, STDIN_FILENO);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);

        // 실행할 명령어
        char *cmd1[] = {"cat", "-e", NULL};
        execve("/bin/cat", cmd1, NULL);

        // execve 호출이 실패한 경우
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // 두 번째 자식 프로세스 생성
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // 자식 프로세스 2
        close(fd[WRITE]);
        // 자식 프로세스 2의 입력을 파이프로 리디렉션하고, 출력을 STDOUT에 연결
        dup2(fd[READ], STDIN_FILENO);
        // sleep(2);
		dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[READ]);

        // 실행할 명령어
        char *cmd2[] = {"cat", "-e", NULL};
        execve("/bin/cat", cmd2, NULL);

        // execve 호출이 실패한 경우
        perror("execve");
        exit(EXIT_FAILURE);
    }
    //세번째 자식 프로세스 생성
    // pid2 = fork();
    // if (pid2 == -1) {
    //     perror("fork");
    //     exit(EXIT_FAILURE);
    // }

    // if (pid2 == 0) {
    //     // 자식 프로세스 2
    //     close(fd[WRITE]);
    //     // 자식 프로세스 2의 입력을 파이프로 리디렉션하고, 출력을 STDOUT에 연결
    //     dup2(fd[READ], STDIN_FILENO);
	// 	dup2(fd[WRITE], STDOUT_FILENO);
    //     close(fd[READ]);

    //     // 실행할 명령어
    //     char *cmd2[] = {"cat", "-e", NULL};
    //     execve("/bin/cat", cmd2, NULL);

    //     // execve 호출이 실패한 경우
    //     perror("execve");
    //     exit(EXIT_FAILURE);
    // }

    // 부모 프로세스
    // close(fd[READ]);
    close(fd[WRITE]);
	// waitpid(pid, )

    // outfile 열기
    outfile_fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
	// for (int i = 0; i < 3; i++)
	// 	wait(NULL);
	dup2(fd[READ], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(fd[READ]);
	char *cmd[] = {"cat", "-e", NULL};
	execve("/bin/cat", cmd, NULL);

    // 두 번째 자식 프로세스에서 읽은 결과를 부모 프로세스에서 outfile에 쓰기
    // ssize_t nread;
    // while ((nread = read(STDIN_FILENO, buffer, BUFSIZ)) > 0) {
    //     write(outfile_fd, buffer, nread);
    // }

    // 파일 닫기
    close(outfile_fd);

    return 0;
}
