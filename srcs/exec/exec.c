/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:36:20 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/18 13:23:06 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_ast(t_ast *root, char **envp)
{
	if (!root)
		return (0);
	// if (root->type == NODE_PIPE)
	// 	return (handle_pipe(root, envp));
	if (root->type == NODE_REDIR)
		return (handle_redirect(root, envp));
	if (root->type == NODE_CMD)
		return (execute_cmd(root, envp));
	// if (root->type == NODE_AND)
	// 	return (handle_and(root, envp));
	// if (root->type == NODE_OR)
	// 	return (handle_or(root, envp));
	return (1);
}

void	exec_child(char *path_cmd, char **av, char **envp)
{
	execve(path_cmd, av, envp);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(av[0], 2);
	if (errno == ENOENT)
		ft_putstr_fd(": command not found\n", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	exit(127);
}

int	exec_simple_command(char *path_cmd, char **av, char **envp)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("Minishell: fork\n");
		return (1);
	}
	if (pid == 0)
		exec_child(path_cmd, av, envp);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Minishell: waitpid\n");
			return (1);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
