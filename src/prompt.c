/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:46:11 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 16:46:39 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_prompt(char *str)
{
	int		i;
	int		count_slash;
	char	*ret;

	count_slash = 0;
	i = ft_strlen(str);
	while (count_slash != 2 && i--)
	{
		if (str[i] == '/')
			count_slash += 1;
	}
	ret = ft_strsub(str, i + 1, ft_strlen(str));
	(str) ? ft_strdel(&str) : 0;
	return (ret);
}

int		print_prompt(void)
{
	char			*str;
	char			*pwd;
	char			*swap;
	char			*hostname;

	str = NULL;
	pwd = NULL;
	hostname = NULL;
	swap = ft_memalloc(sizeof(char) * 256);
	str = getcwd(str, 2048);
	pwd = split_prompt(str);
	ft_putstr_fd("\x1B[32;1mnboushell@", 2);
	gethostname(swap, 255);
	hostname = ft_strsub(swap, 0, ft_strlen(swap) - 6);
	(swap) ? ft_strdel(&swap) : 0;
	ft_putstr_fd(hostname, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd("\x1B[36;0m\x1B[34;1m", 2);
	ft_putstr_fd(pwd, 2);
	ft_putstr_fd("\x1B[36;0m", 2);
	ft_putstr_fd(" >> ", 2);
	(hostname) ? ft_strdel(&hostname) : 0;
	(pwd) ? ft_strdel(&pwd) : 0;
	return (1);
}
