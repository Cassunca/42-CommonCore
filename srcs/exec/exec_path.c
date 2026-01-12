/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:05:57 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/11 21:19:08 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char **av)
{
	if (!av || !av[0])
		return (0);
	if (ft_strcmp(av[0], "cd") == 0 || ft_strcmp(av[0], "echo") == 0
		|| ft_strcmp(av[0], "env") == 0 || ft_strcmp(av[0], "export") == 0
		|| ft_strcmp(av[0], "pwd") == 0 || ft_strcmp(av[0], "unset") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_env_table *env)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		cd(env, cmd);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		echo(env, cmd);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		print_env(env, cmd);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		export(env, cmd);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		pwd(env, cmd);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		unset(env, cmd);
	return (0);
}

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
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_char_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_char_array(paths);
	return (NULL);
}
