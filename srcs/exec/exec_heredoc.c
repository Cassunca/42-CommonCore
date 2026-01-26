/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:06:48 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/26 15:06:07 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		set_signal_int();
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

static void	run_heredoc_loop(int fd, char *delim, t_shell *sh, int expand)
{
	char	*line;

	while (1)
	{
		if (get_signal() == SIGINT)
			break ;
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (is_delimiter(line, delim))
		{
			free(line);
			break ;
		}
		if (expand)
			line = expand_variables_in_heredoc(line, sh);
		ft_putstr_fd(line, fd);
		free(line);
	}
}

int	exec_heredoc(t_redir *redir, t_shell *sh)
{
	int		fd;
	int		exp;
	char	*tmp;

	if (!redir || !redir->file)
		return (1);
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	exp = !check_if_quoted(redir->file);
	tmp = ft_strtrim(redir->file, " \"\'\t\n\r\v\f");
	reset_signal();
	signal(SIGINT, sig_handler_heredoc);
	run_heredoc_loop(fd, tmp, sh, exp);
	close(fd);
	free(tmp);
	setup_sig();
	if (get_signal() == SIGINT)
		return (INTERRUPTED_BY_SIGINT);
	free(redir->file);
	redir->file = ft_strdup(".heredoc_tmp");
	redir->type = REDIR_IN;
	return (0);
}
