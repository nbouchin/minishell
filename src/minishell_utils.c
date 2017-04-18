/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:49:00 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 11:55:24 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**do_bin(char **swap_path, char **env, char **cmd)
{
	swap_path = split_path(env);
	use_bin(swap_path, cmd, env);
	print_prompt();
	(swap_path) ? free_tab(swap_path) : 0;
	return (env);
}

void			do_exit(char **swap_env, char **swap_path)
{
	swap_env ? free_tab(swap_env) : 0;
	swap_path ? free_tab(swap_path) : 0;
	exit(0);
}

char			**try_print(char **env)
{
	print_prompt();
	return (env);
}

void			quit(char **cmd, char *str, char **swap_env,
		char **swap_path)
{
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(str);
	else if (!ft_strcmp(cmd[0], "exit"))
		do_exit(swap_env, swap_path);
}

t_check			*init_data(t_check *s)
{
	s->swap_env = NULL;
	s->swap_path = NULL;
	s->swap = NULL;
	return (s);
}
