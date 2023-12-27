#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int ncount; //쓰레드간 공유되는 자원 -> 쓰레드의 스택을 제외한 영역
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*do_loop(void *data) //쓰레드1에 대한 함수
{
	int i;
	data = 0;
	for (i = 0; i < 10; i ++)
	{
		pthread_mutex_lock(&mutex); //잠금을 설정한다
		printf("loop1 : %d\n",ncount++);
		if (i == 10)
			break;
		pthread_mutex_unlock(&mutex); //잠금을 해제한다
		sleep(1); //sleep한 시간동안 다른 쓰레드를 실행하는 원리?
	}
	return (NULL);
}

void	*do_loop2(void *data) //쓰레드2에 대한 함수
{
	//잠금을 얻으려고 하지만 do_loop에서 이미 잠금을 얻은 상황
	//잠금이 해제될때까지 기다린다
	data = 0;
	for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mutex);
		printf("loop2 : %d\n", ncount++);
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
	return (NULL);
}

int main()
{
	int thr_id;
	pthread_t p_thread[2];
	int status;
	int a = 1;

	ncount = 0;
	thr_id = pthread_create(p_thread, NULL, do_loop, (void *)&a);
	sleep(1);
	thr_id = pthread_create(p_thread + 1, NULL, do_loop2, (void *)&status);

	pthread_join(p_thread[0], (void*)&status);
	pthread_join(p_thread[1], (void *)&status);
	//메인스레드가 위의 두 스레드가  끝날때까지 join에서 대기
	status = pthread_mutex_destroy(&mutex); //뮤텍스 파괴
	printf("code = %d\n",status);
	printf("programing is end\n");
}
