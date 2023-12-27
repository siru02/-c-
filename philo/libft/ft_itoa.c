/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:10:52 by hgu               #+#    #+#             */
/*   Updated: 2023/04/05 11:41:20 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit(int n)
{
	int		digit;

	digit = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		digit += 1;
	}
	while (n)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

static void	ft_recursive(int digit, long tmp, char *a)
{
	if (!tmp)
		return ;
	ft_recursive(digit - 1, tmp / 10, a);
	a[digit] = tmp % 10 + '0';
	return ;
}

char	*ft_itoa(int n)
{
	int		digit;
	char	*a;
	long	tmp;

	digit = ft_digit(n);
	tmp = (long)n;
	a = (char *)malloc(digit + 1);
	if (!a)
		return (0);
	if (!n)
		a[0] = '0';
	if (n < 0)
	{
		a[0] = '-';
		a[digit] = 0;
		tmp *= -1;
	}
	else
	{
		a[digit] = 0;
	}
	ft_recursive(digit - 1, tmp, a);
	return (a);
}
