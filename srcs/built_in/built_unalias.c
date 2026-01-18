/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unalias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:41:52 by kamys             #+#    #+#             */
/*   Updated: 2026/01/18 11:48:11 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static int	is_valid_key(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == ' ' && s[i] == '\t')
			return (0);
		i++;
	}
	if (i == 0 && s[i] != '=')
		return (0);
	return (1);
}

void	unalias(t_alias_table *alias, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid_key(cmd->argv[i]))
		{
			ft_putstr_fd("unalias: ", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			i++;
			continue ;
		}
		alias_unset(alias, cmd->argv[i]);
		i++;
	}
}
