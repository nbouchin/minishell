/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:13:10 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 16:30:04 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_putendl(envp[i++]);
	print_prompt();
	return (envp);
}

int		is_env(char **envp, char *env_name)
{
	int		i;
	char	*swap;

	i = 0;
	swap = ft_strdup(env_name);
	swap = ft_realloc(swap, 1);
	swap = ft_strcat(swap, "=");
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], swap, (ft_strchr(envp[i], '=') - envp[i]) + 1))
		{
			(swap) ? ft_strdel(&swap) : 0;
			return (1);
		}
		i++;
	}
	(swap) ? ft_strdel(&swap) : 0;
	return (0);
}

char	*join_env(char *env_name, char *env_data)
{
	if (env_data)
	{
		env_name = ft_realloc(env_name, 1 + ft_strlen(env_data));
		env_name = ft_strcat(env_name, "=");
		env_name = ft_strcat(env_name, env_data);
	}
	else
	{
		env_name = ft_realloc(env_name, 1);
		env_name = ft_strcat(env_name, "=");
	}
	return (env_name);
}

char	**replace_env(char **envp, char *env_name, char *env_data)
{
	int		i;
	char	*swap;
	char	*env_name_swap;

	i = 0;
	swap = ft_strdup(env_name);
	swap = ft_realloc(swap, 1);
	swap = ft_strcat(swap, "=");
	env_name_swap = ft_strdup(env_name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], swap, (ft_strchr(envp[i], '=') - envp[i]) + 1))
		{
			ft_strdel(&envp[i]);
			envp[i] = join_env(env_name_swap, env_data);
			(swap) ? ft_strdel(&swap) : 0;
			return (envp);
		}
		i++;
	}
	(swap) ? ft_strdel(&swap) : 0;
	(env_name_swap) ? ft_strdel(&env_name_swap) : 0;
	return (envp);
}

char	**set_env(char **envp, char *env_name, char *env_data)
{
	char	**swap_env;

	swap_env = NULL;
	if (!env_name || ft_strchr(env_name, '='))
	{
		ft_putendl_fd("usage: setenv [name] [value]", 2);
		return (envp);
	}
	if (!is_env(envp, env_name))
	{
		swap_env = expand_env(envp, env_name, env_data);
		return (swap_env);
	}
	else
		return (replace_env(envp, env_name, env_data));
	return (swap_env);
}
