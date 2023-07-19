#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
 
int main()
{
    int pid;
    int status;
 
    pid = fork();
 
    if (pid < 0)
    {
        perror("fork error : ");
        exit(0);
    }
    if (pid == 0)
    {
        printf("Im Child\n");
        sleep(10);
        return 2;
    }
    else
    {
        printf("Parent: wait (%d)\n", pid);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            printf("정상종료\n");
            printf("리턴값 %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("신호받았음\n");
            printf("신호번호 %d\n", WTERMSIG(status));
        }
    }
    exit(0);
}
		
위 프로그램을 자식이 정상종료할때까지 기다리거나, 신호를 줘서 자식을 강제 종료시킨후의 결과값을 테스트 해보기 바란다.
Recent Posts
AWS Support Plan의 이해
AWS Certified Solutions Architect 문제 - 1 일차
Amazon S3 Glacier Deep Archive
SRE의 개념과 DevOps와의 차이
지식근로자의 생산성
20년 소프트웨어 엔지니어를 하면서 배운 것들
클라우드는 온프레미스에 비해서 비싸다 ?
Minikube 와 함께하는 Kubernetes Study - Istio Service Mesh
NON TITLE
Create MSA Based Delivery Apps Using Docker
Archive Posts
2023 (49)
2022 (56)
2021 (39)
2020 (71)
2019 (97)
2018 (93)
2017 (136)
2016 (2237)
2015 (21)
Tags
linux
 
system programming
  
0

About
Joinc proposes educational computer-engineering contents. Especially, the contents focus on recently popular and meaningful topics, technically helpful for those who already work or to-be developers in the computer industry and theoretical or typical topics covered in undergraduate courses.

Get in Touch
joinc.help@gmail.com
Categories
Education
DevOps
Architecture
Front/Backend
Basic
BlockChain
Blog
Subscribe
Subscribe to our mailing list to get the latest updates.

joinc.help@gmail.com
 
Copyrights © - Joinc, All Rights Reserved.
Inherited From - Yundream Rebranded By - Joonphil

 
