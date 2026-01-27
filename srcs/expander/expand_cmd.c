/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:05:34 by kamys             #+#    #+#             */
/*   Updated: 2026/01/27 15:00:46 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	has_wildcard(const char *s)
{
	return (ft_strchr(s, '*') || ft_strchr(s, '?'));
}

static void	restore_wildcard(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\a')
			s[i] = '*';
		i++;
	}
}

void	expand_cmd(t_cmd *cmd, t_shell *sh)
{
	char	**new;
	char	*word;
	int		i;
	int		quote;

	i = 0;
	new = NULL;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		quote = 0;
		word = expand_word(cmd->argv[i], sh, &quote);
		if (!quote && has_wildcard(word))
			new = wildcard_expand(new, word);
		else
		{
			restore_wildcard(word);
			new = argv_add(new, word);
		}
		free(word);
		i++;
	}
	free(cmd->argv);
	cmd->argv = new;
}
