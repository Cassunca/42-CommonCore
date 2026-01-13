/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:05:57 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/13 15:31:00 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*resolve_path(char *cmd, t_env_table *env)
{
	char	*path_envp;
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path_envp = env_get(env, "PATH");
	paths = ft_split(path_envp, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_char_array(paths);
			return (full_path);
		}
		free(full_path);
	}
	free_char_array(paths);
	return (NULL);
}
