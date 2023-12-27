/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:17:12 by hgu               #+#    #+#             */
/*   Updated: 2023/04/04 21:59:15 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = new;
	while (new->next)
		new = new->next;
	if (!lst)
	{
		return ;
	}
	new->next = *lst;
	*lst = tmp;
}
