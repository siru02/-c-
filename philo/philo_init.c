/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:13:53 by hgu               #+#    #+#             */
/*   Updated: 2023/12/27 20:31:41 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_arg(t_arg *arg, int argc, char **argv)
{ //입력받은 인자들을 저장한 arg구조체를 초기화한다
	arg->eat_num = 0; //먹어야하는 횟수 0으로 초기화
	arg->num_of_philo = ft_atoi(argv[1]); //철학자의 숫자 초기화
	arg->life_span = ft_atoi(argv[2]); //철학자의 수명 초기화
	arg->eat_time = ft_atoi(argv[3]); //먹는데 걸리는 시간 초기화
	arg->sleep_time = ft_atoi(argv[4]); // 수면시간 초기화
	if (argc == 6)
		arg->eat_num = ft_atoi(argv[5]); //인덱스가 6개인경우 먹어야하는 횟수를 초기화한다
}

void	init_philo(t_philo *philo, t_arg arg, pthread_mutex_t *mutex)
{
	int	philo_idx; //철학자 번호

	philo = malloc(sizeof(t_philo) * arg.num_of_philo);
	if (philo == NULL)
		exit(1);
	philo_idx = 0;
	while (philo_idx < arg.num_of_philo)
	{
		philo[philo_idx].arg = &arg; //arg넣어주기
		philo[philo_idx].eat_cnt = 0; //먹은횟수 0회로 초기화
		philo[philo_idx].last_eat_time = 0; //마지막으로 식사한 시간
		philo[philo_idx].start_time = 0; //시작시간 //gettimeofday로 초기화 필요
		philo[philo_idx].left = (philo_idx + 1) % arg.num_of_philo; //철학자의 왼쪽손 포크 인덱스
		philo[philo_idx].right = philo_idx % arg.num_of_philo; //철학자의 오른쪽손 포크 인덱스
		//철학자가 8명인경우 1번의 오른쪽은 8번 8번의 왼쪽은 1번이다
		philo[philo_idx].num = philo_idx + 1;
		//philo[philo_idx]. //여기서 뮤텍스를 어떻게 써야할지...
		philo_idx++;
	}
}

void	init_fork(pthread_mutex_t **mutex, int **fork_status, t_arg *arg)
{
	int	i;

	*mutex = malloc(sizeof(pthread_mutex_t) * arg->num_of_philo);
	if (*mutex == NULL)
		exit(1);
	i = 0;
	while (i < arg->num_of_philo)
		pthread_mutex_init(*mutex + i++, NULL); //뮤텍스 init
	arg->mutex = mutex;
	*fork_status = malloc(sizeof(int) * arg->num_of_philo);
	if (*fork_status == NULL)
		exit(1);
	i = 0;
	while (i < arg->num_of_philo)
		*fork_status[i++] = 0; //0이면 포크를 사용중이지 않은 상태
	arg->fork_status = fork_status;
}

