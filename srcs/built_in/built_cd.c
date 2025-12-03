/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:48:48 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/03 16:21:33 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	cd(t_env_table *env, char *path)
{
	char	cwd[256];
	char	*old_pwd;
	char	*home;

	if (!path || !ft_strcmp(path, "~"))
	{
		home = env_get(env, "HOME");
		chdir(home);
		old_pwd = env_get(env, "PWD");
		if (getcwd(cwd, sizeof(cwd)))
		{
			env_set(env, "PWD", cwd);
			env_set(env, "OLDPWD", old_pwd);
		}
		return ;
	}
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		return ;
	}
	old_pwd = env_get(env, "PWD");
	if (getcwd(cwd, sizeof(cwd)))
	{
		env_set(env, "PWD", cwd);
		env_set(env, "OLDPWD", old_pwd);
	}
}
