/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:20:10 by hgu               #+#    #+#             */
/*   Updated: 2023/04/04 21:58:44 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (lst == 0)
		return ;
	else if (tmp == 0)
		ft_lstadd_front(lst, new);
	else
	{
		while (tmp->next)
		{
			tmp = tmp -> next;
		}
		tmp->next = new;
	}
}
