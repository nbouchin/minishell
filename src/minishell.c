/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:28:30 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 16:30:45 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			catch_signal(int ctrl)
{
	if (ctrl == 2)
	{
		if (g_is_child)
			return ;
		ft_putendl_fd("", 2);
		print_prompt();
	}
}

char			**check_cmd(char **cmd, char **env, char *str, t_check *s)
{
	if (cmd[0])
	{
		if (!ft_strcmp(cmd[0], "env"))
			return (ft_env(cmd, env));
		else if (!ft_strcmp(cmd[0], "setenv"))
		{
			env = set_env(env, cmd[1], cmd[2]);
			print_prompt();
		}
		else if (!ft_strcmp(cmd[0], "unsetenv"))
			return (s->swap_env = unset_env(env, cmd));
		else if (!ft_strcmp(cmd[0], "cd"))
			return (s->swap_env = ft_cd(cmd, env));
		else if (ft_strcmp(cmd[0], "exit"))
			return (do_bin(s->swap_path, env, cmd));
		else
			quit(cmd, str, s->swap_env, s->swap_path);
	}
	else
		return (try_print(env));
	return (env);
}

char			**get_cmd(char *str, char **env)
{
	int		i;
	char	**cmd;
	char	**swap_env;
	t_check	*s;

	s = malloc(sizeof(t_check));
	s = init_data(s);
	cmd = NULL;
	swap_env = NULL;
	i = 0;
	if (!str)
		return (env);
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
	cmd = ft_strsplit(str, ' ');
	swap_env = check_cmd(cmd, env, str, s);
	free(s);
	(cmd) ? free_tab(cmd) : 0;
	return (swap_env);
}

int				main(int argc, char **argv, char **envp)
{
	char		*str;
	char		**env;

	(void)argv;
	(void)argc;
	str = NULL;
	env = tab_copy(envp);
	env = init_deft_env(env, argv[0]);
	print_prompt();
	signal(SIGINT, catch_signal);
	while (1)
	{
		if (get_next_line(0, &str) == 1)
		{
			env = get_cmd(str, env);
			(str) ? ft_strdel(&str) : 0;
		}
		(str) ? free(str) : 0;
	}
}
