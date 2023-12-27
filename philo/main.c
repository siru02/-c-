/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:30:09 by hgu               #+#    #+#             */
/*   Updated: 2023/12/27 20:29:59 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*thread_function(void *data)
// {
// 	pid_t		pid;
// 	pthread_t	tid;
// 	struct timeval mytime;

// 	char	*thread_name = (char *)data;
// 	pid = getpid();
// 	tid = pthread_self();

// 	for (int i = 0; i < 3; i++)
// 	{
// 		gettimeofday(&mytime, NULL);
// 		printf("[%s] pid : %u, time : %d, tid : %x --- %d\n", thread_name, pid, mytime.tv_usec, (unsigned int)tid, i);
// 		sleep(1);
// 	}
// 	return (NULL);
// }

void	free_all(t_philo *philo, t_arg arg)
{
	int	idx;

	idx = 0;
	while (idx < arg.num_of_philo)
		free(philo);
	return ;
}

void	*create_thread(void *data) //1227
{ //data로 t_philo구조체를 넘겨준다
	int	i;

	i = 0;
	while (i < ((t_philo *)data)->arg->eat_num)
	{ //한 철학자가 먹어야하는 횟수만큼 먹고 자기를 반복해야하므로
		pthread_mutex_lock((t_philo *)data)->)
		printf("%d philosopher, eat_cnt : %d, status : %d\n", \
		((t_philo *)data)->num, ((t_philo *)data)->eat_cnt, \
		((t_philo *)data)->status);
		((t_philo *)data)->eat_cnt = i++;
	}
	return (NULL);
}

void	case_eat_cnt(t_philo **philo, t_arg arg, pthread_t *thread)
{
	int	idx;

	idx = 0;
	while (idx < arg.num_of_philo) //철학자 수만큼 스레드를 생성한다
	{
		philo[idx]->thread = pthread_create(thread, NULL, create_thread, philo + idx);
		idx++;
	}
}

int	main(int argc, char *argv[])
{//철학자수, 수명, 먹는시간, 자는 시간, [먹어야하는 횟수]
	t_arg			arg;
	t_philo			*philo;
	int				*fork_status; //포크가 사용중인지 확인하는 배열 //뮤텍스를 포크로 사용하지 않는다
	pthread_mutex_t	*mutex; //포크를 뮤텍스로 사용하지 않고 배열에 저장하여 접근가능한지 검사
	pthread_t		*thread;

	init_arg(&arg, argc, argv); //arg초기화
	init_fork(&mutex, &fork_status, &arg);
	init_philo(philo, arg, mutex); //각 philo[idx]마다 arg를 모두 가지고 있다
	if (argc == 6)//먹어야하는 횟수까지 입력
		case_eat_cnt(philo, arg, thread);
// 	else if (argc == 5) //먹어야하는 횟수 미입력
// 	{
		
// 	}
	while (--argc > 1)
		pthread_join(philo[argc - 1].thread, NULL);
	free_all(philo, arg);
}

//[1,1,1,1] 포크가져가는지를 배열로 만들어 확인
//포크개수없이 하나만가지고 구현
/*
struct _opaque_pthread_mutex_t {
	long __sig;
	char __opaque[__PTHREAD_MUTEX_SIZE__];
};
*/