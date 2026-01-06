/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:09:13 by kamys             #+#    #+#             */
/*   Updated: 2026/01/08 11:45:57 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	pwd(t_env_table *env, t_cmd *cmd)
{
	char	*cwd;

	(void)env;
	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("pwd");
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
}
