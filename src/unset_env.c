/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:07:28 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/11 13:23:16 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**delet_env(char **en, char *envn)
{
	char	**ret;
	int		i;
	int		y;
	int		size;

	i = 0;
	y = 0;
	size = tab_count(en);
	ret = (char**)ft_memalloc(sizeof(char*) * (size));
	envn = ft_realloc(envn, 1);
	envn = ft_strcat(envn, "=");
	while (en[i])
	{
		if (!ft_strncmp(envn, en[i], (ft_strchr(en[i], '=') - en[i]) + 1))
			i++;
		else
			ret[y++] = ft_strdup(en[i++]);
	}
	free_env(&en);
	return (ret);
}

char	**unset_env(char **en, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!cmd[i] || !is_env(en, cmd[i]))
			i++;
		else
			en = delet_env(en, cmd[i]);
	}
	print_prompt();
	return (en);
}
