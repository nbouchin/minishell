/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:59:10 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 16:27:57 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_is_child = 0;

char		**split_path(char **en)
{
	int		i;
	char	*path;
	char	**path_tab;
	long	path_index;

	i = 0;
	path_index = 0;
	while (en[i])
	{
		if (!ft_strncmp(en[i], "PATH=", (ft_strchr(en[i], '=') - en[i]) + 1))
		{
			path_index = ft_strchr(en[i], '=') - en[i] + 1;
			path = ft_strsub(en[i], path_index, ft_strlen(en[i]));
			path_tab = ft_strsplit(path, ':');
			ft_strdel(&path);
			return (path_tab);
		}
		i++;
	}
	return (NULL);
}

char		**init_path(char **path, char **cmd)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_realloc(path[i], ft_strlen(cmd[0]) + 1);
		path[i] = ft_strcat(path[i], "/");
		path[i] = ft_strcat(path[i], cmd[0]);
		i++;
	}
	return (path);
}

void		if_path(char **path, char **cmd, char **env)
{
	int		i;
	int		stat_loc;
	pid_t	child_pid;

	i = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		if (ft_strchr(cmd[0], '/'))
			execve(cmd[0], cmd, env);
		else
		{
			path = init_path(path, cmd);
			while (path[i])
				execve(path[i++], cmd, env);
		}
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(0);
	}
	else
	{
		waitpid(child_pid, &stat_loc, WUNTRACED);
		catch_error(stat_loc, child_pid, cmd[0]);
	}
}

void		if_npath(char **cmd, char **env)
{
	pid_t		child_pid;
	int			stat_loc;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (ft_strchr(cmd[0], '/'))
			execve(cmd[0], cmd, env);
		else
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(0);
		}
	}
	else
	{
		waitpid(child_pid, &stat_loc, WUNTRACED);
		catch_error(stat_loc, child_pid, cmd[0]);
	}
}

void		use_bin(char **path, char **cmd, char **env)
{
	int		i;

	i = 0;
	if (path)
	{
		g_is_child = 1;
		if_path(path, cmd, env);
		g_is_child = 0;
	}
	else
		if_npath(cmd, env);
}
