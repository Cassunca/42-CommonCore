/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:51:35 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/11 21:18:07 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static int	is_flag(char *flag)
{
	int	i;

	if (!flag || flag[0] != '-')
		return (0);
	i = 1;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

void	echo(t_env_table *env, t_cmd *cmd)
{
	int	i;
	int	flag_n;

	(void)env;
	if (!cmd || !cmd->argv)
		return ;
	i = 1;
	flag_n = 0;
	while (cmd->argv[i] && is_flag(cmd->argv[i]))
	{
		flag_n = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr(cmd->argv[i]);
		if (cmd->argv[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (!flag_n)
		write(1, "\n", 1);
}
