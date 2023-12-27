/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:12:15 by hgu               #+#    #+#             */
/*   Updated: 2023/04/08 21:32:30 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long	ft_limit(long num, long flag, char ch)
{
	if (num == 922337203685477580 && ch >= '8' && flag == -1)
		return (-9223372036854775807 - 1);
	else if (num >= 9223372036854775800 && flag == -1)
		return (-9223372036854775807 - 1);
	if (num == 922337203685477580 && ch >= '7' && flag == 1)
		return (9223372036854775807);
	else if (num >= 9223372036854775800 && flag == 1)
		return (9223372036854775807);
	return (num = num * 10 + (ch - '0'));
}

static int	ft_break(long num, long flag)
{
	long	max;
	long	min;

	max = 9223372036854775807;
	min = -9223372036854775807;
	if ((flag == -1 && num == min - 1) || (num == max && flag == 1))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	long	flag;

	num = 0;
	flag = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		flag = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		num = ft_limit(num, flag, *str);
		if (ft_break(num, flag))
			return ((int)num);
		str++;
	}
	return ((int)(num * flag));
}
