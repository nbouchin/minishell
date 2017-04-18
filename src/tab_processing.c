/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:06:41 by nbouchin          #+#    #+#             */
/*   Updated: 2017/03/31 10:28:35 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			tab_count(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char		**tab_copy(char **tab)
{
	char	**ret;
	int		i;
	int		y;
	int		size;

	i = 0;
	y = 0;
	size = tab_count(tab);
	ret = (char**)ft_memalloc(sizeof(char*) * (size + 1));
	while (tab[i])
		ret[i++] = ft_strdup(tab[y++]);
	return (ret);
}
