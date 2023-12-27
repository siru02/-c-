/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:16:53 by hgu               #+#    #+#             */
/*   Updated: 2023/04/05 11:59:53 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	plusminus(int nb, int fd)
{
	if (nb > 0)
	{
		return (nb);
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		return (nb * (-1));
	}
	else
	{
		return (0);
	}
}

static int	digits(int nb)
{
	int	digit;

	digit = 0;
	while (1)
	{
		if (nb != 0)
		{
			nb /= 10;
			digit += 1;
		}
		else
		{
			return (digit);
		}
	}
}

static int	divnum(int digit)
{
	int	ten;

	ten = 1;
	while (digit > 1)
	{
		ten *= 10;
		digit--;
	}
	return (ten);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	digit;
	int	pnum;

	if (n == 0)
		write(fd, "0", 1);
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		n = plusminus(n, fd);
		digit = digits(n);
		while (digit > 0)
		{
			pnum = n / divnum(digit);
			n = n % divnum(digit);
			pnum = pnum + 48;
			write(fd, &pnum, 1);
			digit--;
		}
	}
}
