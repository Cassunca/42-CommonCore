/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:54:01 by kamys             #+#    #+#             */
/*   Updated: 2026/01/26 15:08:03 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal_status;

void	set_signal_int(void)
{
	g_signal_status = SIGINT;
}

int	get_signal(void)
{
	return (g_signal_status);
}

void	reset_signal(void)
{
	g_signal_status = 0;
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		set_signal_int();
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_sig(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
