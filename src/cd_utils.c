/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 08:42:15 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 15:28:07 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all_data(t_cd *s, char *pwd, char *oldpwd)
{
	(void)oldpwd;
	(pwd) ? ft_strdel(&pwd) : 0;
	(oldpwd) ? ft_strdel(&oldpwd) : 0;
	free_cd_data(s);
	free(s);
}

t_cd		*init_struct_cd(t_cd *s)
{
	s->pwd = NULL;
	s->home = NULL;
	s->oldpwd = NULL;
	s->swap_env = NULL;
	s->oldpwd_swap = NULL;
	return (s);
}

int			regular_param(char **cmd, char **env, char ***env_ret)
{
	t_cd	*s;
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup("PWD");
	oldpwd = ft_strdup("OLDPWD");
	s = malloc(sizeof(t_cd));
	s = init_struct_cd(s);
	s->oldpwd = getcwd(s->oldpwd, 2048);
	if (access(cmd[1], X_OK) != -1)
		chdir(cmd[1]);
	else
	{
		cd_error(cmd[1]);
		free_all_data(s, pwd, oldpwd);
		return (0);
	}
	s->pwd = getcwd(s->pwd, 2048);
	s->swap_env = set_env(env, pwd, s->pwd);
	*env_ret = set_env(s->swap_env, oldpwd, s->oldpwd);
	free_all_data(s, pwd, oldpwd);
	return (print_prompt());
}

int			recover(char **cmd, char **env, char ***env_ret)
{
	t_cd	*s;
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup("PWD");
	oldpwd = ft_strdup("OLDPWD");
	s = malloc(sizeof(t_cd));
	s = init_struct_cd(s);
	s->oldpwd_swap = get_oldpwd(env);
	s->oldpwd = getcwd(s->oldpwd, 2048);
	if (access(s->oldpwd_swap, X_OK) != -1)
		chdir(s->oldpwd_swap);
	else
		return (no_pwd(s, cmd, pwd, oldpwd));
	s->pwd = getcwd(s->pwd, 2048);
	s->swap_env = set_env(env, pwd, s->pwd);
	*env_ret = set_env(s->swap_env, oldpwd, s->oldpwd);
	free_all_data(s, pwd, oldpwd);
	print_prompt();
	return (1);
}
