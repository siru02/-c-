/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:29:49 by hgu               #+#    #+#             */
/*   Updated: 2023/12/27 20:31:12 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "libft/libft.h"

typedef struct s_arg
{
	int				num_of_philo; //철학자수
	int				life_span; //수명
	int				eat_time; //먹는 시간 이 시간동안 철학자는 2개의 포크를 집고 있는다
	int				sleep_time; //자는 시간
	int				eat_num; //먹는 횟수
	int				*fork_status;
	pthread_mutex_t	*mutex;
}t_arg;

typedef struct s_philo
{
	int				status; //철학자 상태
	int				num; //철학자 번호
	int				eat_cnt; //철학자가 먹은 횟수
	int				left; //왼쪽 포크 번호
	int				right; //오른쪽 포크 번호
	int				last_eat_time; //마지막으로 먹은 시간
	int				start_time; //쓰레드의 시작시간
	pthread_t		thread; //쓰레드 번호
	t_arg			*arg; //입력인자값을 저장하는 구조체
}t_philo;