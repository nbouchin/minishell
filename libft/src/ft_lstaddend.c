/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:41:07 by nbouchin          #+#    #+#             */
/*   Updated: 2017/03/15 19:10:07 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **list, t_list *new)
{
	if (*list)
	{
		while (*list)
			list = &(*list)->next;
		*list = new;
	}
	else
		*list = new;
}
