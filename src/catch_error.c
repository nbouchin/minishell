/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:10:08 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 16:29:32 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_error(int stat_loc, pid_t pid, char *program_name)
{
	if (WIFSIGNALED(stat_loc))
	{
		if (WTERMSIG(stat_loc) == SIGSEGV)
		{
			ft_putnbr_fd((int)pid, 2);
			ft_putstr_fd(" segmentation fault ", 2);
			ft_putendl_fd(program_name, 2);
		}
		else if (WTERMSIG(stat_loc) == SIGABRT)
		{
			ft_putnbr_fd((int)pid, 2);
			ft_putstr_fd(" abort ", 2);
			ft_putendl_fd(program_name, 2);
		}
		else if (WTERMSIG(stat_loc) == SIGBUS)
		{
			ft_putnbr_fd((int)pid, 2);
			ft_putstr_fd(" bus error ", 2);
			ft_putendl_fd(program_name, 2);
		}
	}
}

int		error(char *cmd, t_env *s)
{
	int	i;

	i = 1;
	while (cmd[i] == 'i')
		i++;
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(cmd[i], 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: env [-i] [utility [argument ...]]", 2);
	free(s);
	print_prompt();
	return (1);
}
