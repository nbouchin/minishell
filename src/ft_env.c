/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:41:35 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 12:05:30 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_free(t_env *s)
{
	(s->swapp) ? free_tab(s->swapp) : 0;
	(s->deftp) ? free_tab(s->deftp) : 0;
	(s->basice) ? free_tab(s->basice) : 0;
	(s->swape) ? free_tab(s->swape) : 0;
	(s->first_param) ? ft_strdel(&s->first_param) : 0;
	(s->second_param) ? ft_strdel(&s->second_param) : 0;
	free(s);
	return (1);
}

t_env			*init_env_struct(t_env *s, char **env)
{
	s->basice = NULL;
	s->basice = ft_memalloc(sizeof(char*) * 1);
	s->deftp = NULL;
	s->deftp = init_deftp(s->deftp);
	s->swape = NULL;
	s->swape = tab_copy(env);
	s->swapp = split_path(env);
	s->first_param = 0;
	s->second_param = 0;
	s->flag = 0;
	return (s);
}

static void		ft_test(t_env *s, int i, char **cmd, size_t *test)
{
	*test = ft_strchr(cmd[i], '=') - cmd[i];
	s->first_param = ft_strsub(cmd[i], 0, *test);
	s->second_param = ft_strdup(ft_strstr(cmd[i], "=") + 1);
	s->swape = set_env(s->swape, s->first_param, s->second_param);
	s->basice = set_env(s->basice, s->first_param, s->second_param);
	(s->first_param) ? ft_strdel(&s->first_param) : 0;
	(s->second_param) ? ft_strdel(&s->second_param) : 0;
}

static char		**ft_env_bin(t_env *s, char **cmd, int i, char **env)
{
	if (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "cd") && ft_free(s))
			return (ft_cd(cmd + i, env));
		if (s->flag == 0)
			use_bin(s->swapp, cmd + i, s->swape);
		else
			use_bin(s->deftp, cmd + i, s->basice);
	}
	else if (s->flag && print_env(s->basice) && ft_free(s))
		return (env);
	else
	{
		print_env(s->swape);
		ft_free(s);
		return (env);
	}
	ft_free(s);
	print_prompt();
	return (env);
}

char			**ft_env(char **cmd, char **env)
{
	t_env	*s;
	size_t	test;
	int		i;

	i = 1;
	test = 0;
	s = malloc(sizeof(t_env));
	s = init_env_struct(s, env);
	if (count_cmd(cmd) == 1 && print_env(s->swape) && ft_free(s))
		return (env);
	if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "-i") && error(cmd[1], s))
		return (env);
	else if (cmd[1][0] == '-' && !ft_strcmp(cmd[1], "-i") && (s->flag = 1))
		i++;
	while (cmd[i])
		if (ft_strchr(cmd[i], '='))
			ft_test(s, i++, cmd, &test);
		else
			break ;
	return (ft_env_bin(s, cmd, i, env));
}
