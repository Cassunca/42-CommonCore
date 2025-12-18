/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:26:52 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/18 13:29:11 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_redir	*new_redir_content(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = NULL;
	return (redir);
}

t_ast	*new_redir_node(t_ast *cmd_node, t_redir_type type, char *file)
{
	t_redir	*redir_content;

	redir_content = new_redir_content(type, file);
	if (!redir_content)
		return (NULL);
	return (new_ast_node(NODE_REDIR, cmd_node, NULL, redir_content));
}

int	apply_redirect(t_redir *redir)
{
	int		fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Minishell: open");
			return (-1);
		}
		if (redir->type == REDIR_IN
			|| redir->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("Minishell: dup2");
			close(fd);
			return (-1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}

int	handle_redirect(t_ast *redir_node, char **envp)
{
	t_redir	*redir_list;
	pid_t	pid;
	int		status;

	redir_list = (t_redir *)redir_node->content;
	if (!redir_list)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (apply_redirect(redir_list) == -1)
			exit(1);
		status = execute_ast(redir_node->left, envp);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
