/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:54:01 by kamys             #+#    #+#             */
/*   Updated: 2025/11/17 17:20:00 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal_status;

int	get_singal(void)
{
	return (g_signal_status);
}

void	reset_signal(void)
{
	g_signal_status = 0;
}

void	handler(int sig)
{
	g_signal_status = sig;
	ft_putstr_fd("\n> ", 1);
}
