/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:15:40 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 16:26:07 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_oldpwd(char **envp)
{
	int		i;
	char	*swap;
	char	*ret;

	i = 0;
	ret = NULL;
	swap = ft_strdup("OLDPWD=");
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], swap, (ft_strchr(envp[i], '=') - envp[i]) + 1))
		{
			ft_strdel(&swap);
			return (ret = ft_strdup(ft_strchr(envp[i], '=') + 1));
		}
		i++;
	}
	ft_putendl_fd("sh: cd: OLDPWD not set", 2);
	print_prompt();
	(swap) ? ft_strdel(&swap) : 0;
	return (NULL);
}

char	*get_home(char **envp)
{
	int		i;
	char	*swap;
	char	*ret;

	i = 0;
	ret = NULL;
	swap = ft_strdup("HOME=");
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], swap, (ft_strchr(envp[i], '=') - envp[i]) + 1))
		{
			ft_strdel(&swap);
			return (ret = ft_strdup(ft_strchr(envp[i], '=') + 1));
		}
		i++;
	}
	ft_strdel(&swap);
	return (NULL);
}

int		cd_error(char *cmd)
{
	if (!cmd)
	{
		print_prompt();
		return (1);
	}
	if (access(cmd, F_OK))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (access(cmd, X_OK))
	{
		ft_putstr_fd("cd: premission denied: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	print_prompt();
	return (1);
}

char	**test(char **env_ret, char **env)
{
	(env_ret) ? free_tab(env_ret) : 0;
	return (env);
}

char	**ft_cd(char **cmd, char **env)
{
	char	**env_ret;

	env_ret = NULL;
	if (count_cmd(cmd) == 1 || !ft_strcmp(cmd[1], "~"))
		if (!no_param(env, &env_ret))
			return (test(env_ret, env));
		else
			return (env_ret);
	else if (ft_strcmp(cmd[1], "-"))
		if (!regular_param(cmd, env, &env_ret))
			return (env);
		else
			return (env_ret);
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (!recover(cmd, env, &env_ret))
			return (env);
		else
			return (env_ret);
	}
	(env_ret) ? free_tab(env_ret) : 0;
	print_prompt();
	return (env);
}
