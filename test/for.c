#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    int fd[2]; // 파이프용 파일 디스크립터 배열
    int outfile_fd; // 출력 파일 디스크립터
    pid_t pid; // 프로세스 ID 저장용 변수

    if (pipe(fd) == -1) // 파이프 생성
    {
        perror("pipe"); // 에러 메시지 출력
        exit(EXIT_FAILURE); // 프로세스 종료
    }

    for (int i = 1; i < argc; i++)
    {
        pid = fork(); // 자식 프로세스 생성
        if (pid == -1) // fork 실패시
        {
            perror("fork"); // 에러 메시지 출력
            exit(EXIT_FAILURE); // 프로세스 종료
        }

        if (pid == 0) // 자식 프로세스
        {
            close(fd[READ]); // 읽기용 파이프 닫기
            dup2(fd[WRITE], STDOUT_FILENO); // 표준 출력을 파이프로 리다이렉트
            close(fd[WRITE]); // 쓰기용 파이프 닫기

            // 실행할 명령어와 인수 설정
            char *cmd[] = {argv[i], NULL};
            execve(cmd[0], cmd, envp);

            // execve 실패시 에러 메시지 출력하고 프로세스 종료
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }

    close(fd[WRITE]); // 쓰기용 파이프 닫기

    // 부모 프로세스는 자식 프로세스들이 종료될 때까지 기다림
    for (int i = 1; i < argc; i++)
    {
        wait(NULL);
    }

    // 이제 출력 파일에 결과값을 담음
    outfile_fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(outfile_fd, STDOUT_FILENO);

    // cat 명령어를 실행하여 결과값을 출력 파일에 저장
    char *cmd[] = {"cat", NULL};
    execve("/bin/cat", cmd, envp);

    // execve 실패시 에러 메시지 출력하고 프로세스 종료
    perror("execve");
    exit(EXIT_FAILURE);

    return 0;
}
