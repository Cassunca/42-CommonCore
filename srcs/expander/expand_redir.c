/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:46 by kamys             #+#    #+#             */
/*   Updated: 2026/01/11 21:09:44 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_redir(t_redir *redir, t_env_table *env)
{
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
			redir->file = expand_word(redir->file, env);
		redir = redir->next;
	}
}
