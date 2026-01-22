/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:09:13 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 18:29:47 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

int	pwd(t_env_table *env, t_cmd *cmd)
{
	char	*cwd;

	(void)env;
	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", STDIN_FILENO);
		ft_putstr_fd("getcwd: cannot access parent directory\n", STDIN_FILENO);
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
