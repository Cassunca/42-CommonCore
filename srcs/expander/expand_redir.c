/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:46 by kamys             #+#    #+#             */
/*   Updated: 2026/01/27 15:01:07 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_redir(t_redir *redir, t_shell *sh)
{
	int	quote;

	quote = 0;
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
			redir->file = expand_word(redir->file, sh, &quote);
		redir = redir->next;
	}
}
