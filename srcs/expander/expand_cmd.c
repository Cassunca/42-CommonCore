/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:05:34 by kamys             #+#    #+#             */
/*   Updated: 2026/01/11 21:09:32 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_cmd(t_cmd *cmd, t_env_table *env)
{
	int	i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		cmd->argv[i] = expand_word(cmd->argv[i], env);
		i++;
	}
}
