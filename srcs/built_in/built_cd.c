/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/01/22 11:39:57 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "built.h"

static void	set_pwd_oldpwd(t_env_table *env, char *pwd, char *old_pwd)
{
	env_set(env, "OLDPWD", old_pwd);
	env_set(env, "PWD", pwd);
}

static void	cd_path(t_env_table *env, char *path)
{
	char	*cwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd"));
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		free(old_pwd);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		free(old_pwd);
		return ;
	}
	set_pwd_oldpwd(env, cwd, old_pwd);
	free(old_pwd);
	free(cwd);
}

static void	cd_dash(t_env_table *env)
{
	char	*cwd;
	char	*old_pwd;
	char	*pwd;

	old_pwd = env_get(env, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return ;
	}
	pwd = env_get(env, "PWD");
	if (chdir(old_pwd) == -1)
	{
		perror("cd");
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		return ;
	}
	printf("%s\n", cwd);
	set_pwd_oldpwd(env, cwd, pwd);
	free(cwd);
}

static void	cd_home(t_env_table *env)
{
	char	*cwd;
	char	*old_pwd;
	char	*home;

	home = env_get(env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		free(old_pwd);
		return (perror("cd"));
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(old_pwd);
		return (perror("cd"));
	}
	set_pwd_oldpwd(env, cwd, old_pwd);
	free(cwd);
	free(old_pwd);
}

void	cd(t_env_table *env, t_cmd *cmd)
{
	if (!cmd->argv[1] || !ft_strcmp(cmd->argv[1], "~"))
		cd_home(env);
	else if (!ft_strcmp(cmd->argv[1], "-"))
		cd_dash(env);
	else
		cd_path(env, cmd->argv[1]);
}
