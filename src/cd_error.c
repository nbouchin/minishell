/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:47:13 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 16:23:39 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			no_pwd(t_cd *s, char **cmd, char *pwd, char *oldpwd)
{
	if (!s->oldpwd_swap)
	{
		(pwd) ? ft_strdel(&pwd) : 0;
		(oldpwd) ? ft_strdel(&oldpwd) : 0;
		free_cd_data(s);
		free(s);
		return (0);
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	(pwd) ? ft_strdel(&pwd) : 0;
	(oldpwd) ? ft_strdel(&oldpwd) : 0;
	free_cd_data(s);
	free(s);
	print_prompt();
	return (0);
}

int			no_home(t_cd *s, char *pwd, char *oldpwd)
{
	ft_putstr_fd("cd: HOME not set", 2);
	(pwd) ? ft_strdel(&pwd) : 0;
	(oldpwd) ? ft_strdel(&oldpwd) : 0;
	free_cd_data(s);
	free(s);
	print_prompt();
	return (0);
}

static void	free_all_data(t_cd *s, char *pwd, char *oldpwd)
{
	(pwd) ? ft_strdel(&pwd) : 0;
	(oldpwd) ? ft_strdel(&oldpwd) : 0;
	free_cd_data(s);
	(s->home) ? ft_strdel(&s->home) : 0;
	free(s);
}

static t_cd	*init_all_data(t_cd *s, char **pwd, char **oldpwd, char **env)
{
	*pwd = ft_strdup("PWD");
	*oldpwd = ft_strdup("OLDPWD");
	s = malloc(sizeof(t_cd));
	s = init_struct_cd(s);
	s->home = get_home(env);
	return (s);
}

int			no_param(char **env, char ***env_ret)
{
	t_cd	*s;
	char	*pwd;
	char	*oldpwd;

	s = NULL;
	s = init_all_data(s, &pwd, &oldpwd, env);
	if (!s->home)
		return (no_home(s, pwd, oldpwd));
	s->oldpwd = getcwd(s->oldpwd, 2048);
	if (access(s->home, X_OK) != -1)
		chdir(s->home);
	else
	{
		cd_error(s->home);
		free_cd_data(s);
		(s->home) ? ft_strdel(&s->home) : 0;
		free(s);
		return (0);
	}
	s->pwd = getcwd(s->pwd, 2048);
	s->swap_env = set_env(env, pwd, s->pwd);
	*env_ret = set_env(s->swap_env, oldpwd, s->oldpwd);
	free_all_data(s, pwd, oldpwd);
	print_prompt();
	return (1);
}
