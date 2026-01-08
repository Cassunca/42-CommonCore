/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:26:52 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/22 11:45:49 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	dup_file(int fd, int fileno)
{
	if (dup2(fd, fileno) == -1)
	{
		perror("Minishell: dup2");
		close(fd);
		return (-1);
	}
	return (0);
}

static int	fd_type(t_redir_type type, int fd)
{
	if (fd == -1)
	{
		perror("Minishell: open");
		return (-1);
	}
	if (type == REDIR_IN || type == REDIR_HEREDOC)
	{
		if (dup_file(fd, STDIN_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup_file(fd, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	apply_redirect(t_redir *redir)
{
	int		fd;

	while (redir)
	{
		fd = -1;
		if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(redir->file);
			return (-1);
		}
		if (fd_type(redir->type, fd) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}
