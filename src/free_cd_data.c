/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cd_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:43:27 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 14:46:37 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cd_data(t_cd *s)
{
	(s->pwd) ? ft_strdel(&s->pwd) : 0;
	(s->oldpwd) ? ft_strdel(&s->oldpwd) : 0;
	(s->oldpwd_swap) ? ft_strdel(&s->oldpwd_swap) : 0;
}
