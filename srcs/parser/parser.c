/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:42:06 by kamys             #+#    #+#             */
/*   Updated: 2025/12/09 14:35:45 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	token_op(t_token_type token)
{
	if (token == TK_PIPE
		|| token == TK_AND
		|| token == TK_OR
		|| token == TK_LIST
		|| token == TK_REDIR_IN
		|| token == TK_REDIR_OUT
		|| token == TK_HEREDOC
		|| token == TK_APPEND)
		return (1);
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	if (token_op(head->type))
	{
		printf("Syntax %s : error\n", head->value);
		return (1);
	}
	while (head->next)
	{
		if (token_op(head->type))
		{
			head = head->next;
			if (token_op(head->type))
			{
				printf("Syntax %s : error\n", head->value);
				return (1);
			}
		}
		head = head->next;
	}
	if (token_op(head->type))
	{
		printf("Syntax %s : error\n", head->value);
		return (1);
	}
	return (0);
}

void	parser(t_token *tokens)
{
	if (check_syntax(tokens))
		return ;
}
