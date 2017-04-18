/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 17:37:07 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 13:00:33 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char ***envp)
{
	int i;

	i = 0;
	while ((*envp)[i])
		ft_strdel(&(*envp)[i++]);
	free(*envp);
	envp = NULL;
}

char	**expand_env(char **envp, char *env_name, char *env_data)
{
	char	**ret;
	char	*swap_env_name;
	int		i;
	int		y;
	int		size;

	i = 0;
	y = 0;
	swap_env_name = ft_strdup(env_name);
	size = tab_count(envp);
	ret = (char**)ft_memalloc(sizeof(char*) * (size + 2));
	while (envp[i])
		ret[y++] = ft_strdup(envp[i++]);
	swap_env_name = join_env(swap_env_name, env_data);
	ret[y] = ft_strdup(swap_env_name);
	(swap_env_name) ? ft_strdel(&swap_env_name) : 0;
	(envp) ? free_tab(envp) : 0;
	envp = tab_copy(ret);
	(ret) ? free_tab(ret) : 0;
	return (envp);
}
