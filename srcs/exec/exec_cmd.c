/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:15:03 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/22 11:20:18 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_builtin(char **av)
{
	if (!av || !av[0])
		return (0);
	if (ft_strcmp(av[0], "cd") == 0 || ft_strcmp(av[0], "echo") == 0
		|| ft_strcmp(av[0], "env") == 0 || ft_strcmp(av[0], "export") == 0
		|| ft_strcmp(av[0], "pwd") == 0 || ft_strcmp(av[0], "unset") == 0)
		return (1);
	return (0);
}

static int	execute_builtin(t_cmd *cmd, t_env_table *env)
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

int	execute_cmd(t_ast *cmd_node, t_env_table *env)
{
	t_cmd	*cmd;
	char	*path_cmd;
	int		status;

	cmd = (t_cmd *)cmd_node->content;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd->argv))
		return (execute_builtin(cmd, env));
	path_cmd = resolve_path(cmd->argv[0], env);
	if (!path_cmd)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	status = exec_simple_command(cmd->redir, path_cmd, cmd->argv, env);
	free(path_cmd);
	return (status);
}
