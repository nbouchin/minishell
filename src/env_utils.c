/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:55:37 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 12:30:29 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**init_deftp(char **deftp)
{
	deftp = (char**)ft_memalloc(sizeof(char*) * 3);
	deftp[0] = ft_strdup("/bin");
	deftp[1] = ft_strdup("/usr/bin");
	return (deftp);
}

int				count_cmd(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

t_deft			*init_struct(t_deft *s)
{
	s->pwd = NULL;
	s->swap = NULL;
	s->swap_nb = NULL;
	s->first_param = NULL;
	s->first_param = getcwd(s->first_param, 2042);
	s->pwd = getcwd(s->pwd, 2048);
	return (s);
}

void			free_struct(t_deft *s)
{
	(s->swap_nb) ? ft_strdel(&s->swap_nb) : 0;
	(s->swap) ? ft_strdel(&s->swap) : 0;
	(s->pwd) ? ft_strdel(&s->pwd) : 0;
	(s->first_param) ? ft_strdel(&s->first_param) : 0;
	(s->spwd) ? ft_strdel(&s->spwd) : 0;
	free(s);
}

char			**init_deft_env(char **deft_env, char *str)
{
	t_deft	*s;

	s = malloc(sizeof(t_deft));
	s = init_struct(s);
	s->spwd = ft_memalloc(sizeof(char) * (ft_strlen(s->pwd) + 2 +
				ft_strlen(str)));
	s->spwd = ft_strcat(s->spwd, s->pwd);
	s->spwd = ft_strcat(s->spwd, "/");
	s->spwd = ft_strcat(s->spwd, str);
	s->swap = ft_strdup("PWD");
	deft_env = set_env(deft_env, s->swap, s->first_param);
	(s->swap) ? ft_strdel(&s->swap) : 0;
	(s->first_param) ? ft_strdel(&s->first_param) : 0;
	s->swap = ft_strdup("SHLVL");
	s->swap_nb = ft_strdup("1");
	deft_env = set_env(deft_env, s->swap, s->swap_nb);
	(s->swap) ? ft_strdel(&s->swap) : 0;
	s->swap_nb ? ft_strdel(&s->swap_nb) : 0;
	s->swap = ft_strdup("_");
	deft_env = set_env(deft_env, s->swap, s->spwd);
	free_struct(s);
	return (deft_env);
}
