/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:40:49 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/22 11:35:33 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static int	is_valid_key(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_env_table *env, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid_key(cmd->argv[i]))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			i++;
			continue ;
		}
		env_unset(env, cmd->argv[i]);
		i++;
	}
}
