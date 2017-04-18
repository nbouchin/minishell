/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:26:52 by nbouchin          #+#    #+#             */
/*   Updated: 2017/04/12 15:45:18 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

int				g_is_child;

typedef void	(*t_sig) (int);

typedef struct	s_cd
{
	char		*pwd;
	char		*oldpwd;
	char		*oldpwd_swap;
	char		**swap_env;
	char		*home;
}				t_cd;

typedef struct	s_check
{
	char		**swap_env;
	char		**swap_path;
	char		**swap;
}				t_check;

typedef struct	s_deft
{
	char		*first_param;
	char		*pwd;
	char		*spwd;
	char		*swap;
	char		*swap_nb;
}				t_deft;

typedef struct	s_env
{
	char		**swapp;
	char		**swape;
	char		**deftp;
	char		**basice;
	char		*first_param;
	char		*second_param;
	int			flag;
}				t_env;

/*
**	env function
*/

int				tab_count(char **tab);
char			**tab_copy(char **tab);
int				is_env(char **envp, char *env_name);
char			*join_env(char *env_name, char *env_data);
char			**replace_env(char **envp, char *env_name, char *env_data);
char			**set_env(char **envp, char *env_name, char *env_data);
char			**unset_env(char **envp, char **cmd);
void			free_env(char ***envp);
char			**add_env(char **envp, char *env_name, char *env_data);
char			**expand_env(char **envp, char *env_name, char *env_data);
char			**print_env(char **envp);
char			**split_path(char **envp);
void			use_bin(char **path, char **cmd, char **env);
char			**init_path(char **path, char **cmd);
void			ft_echo(char *str);
char			**ft_env(char **cmd, char **env);
void			free_tab(char **tab);
int				print_prompt(void);
char			**ft_cd(char **cmd, char **env);
int				count_cmd(char **cmd);
char			*get_oldpwd(char **envp);
char			*get_home(char **envp);
int				cd_error(char *cmd);
void			catch_signal(int ctrl);
void			catch_error(int stat_loc, pid_t pid, char *program_name);

/*
**	cd
*/

int				no_param(char **env, char ***ret_env);
int				regular_param(char **cmd, char **env, char ***ret_env);
int				recover(char **cmd, char **env, char ***ret_env);
void			free_cd_data(t_cd *s);
int				no_home(t_cd *s, char *pwd, char *oldpwd);
t_cd			*init_struct_cd(t_cd *s);

/*
**	prompt
*/

char			*split_prompt(char *str);

/*
**	minishell
*/

void			catch_signal(int ctrl);
char			**do_bin(char **swap_path, char **env, char **cmd);
void			do_exit(char **swap_env, char **swap_path);
char			**try_print(char **env);
void			quit(char **cmd, char *str, char **swap_env, char **swap_path);
t_check			*init_data(t_check *s);

/*
**	env_utils
*/

int				error(char *cmd, t_env *s);
int				count_cmd(char **cmd);
t_deft			*init_struct(t_deft *s);
void			free_struct(t_deft *s);
char			**init_deft_env(char **deft_env, char *str);
char			**init_deftp(char **deftp);
int				no_pwd(t_cd *s, char **cmd, char *pwd, char *oldpwd);

#endif
