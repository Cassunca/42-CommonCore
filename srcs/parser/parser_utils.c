/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 23:51:43 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/15 16:10:02 by amyrodri         ###   ########.fr       */
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

int	check_in_end(t_token *start, t_token *end)
{
	t_token	*curr;
	t_token	*prev;

	curr = start;
	prev = NULL;
	while (curr != end)
	{
		if (prev && token_op(prev->type)
			&& token_op(curr->type))
		{
			printf("Syntax %s : error\n", prev->value);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	if (prev && token_op(prev->type))
	{
		printf("Syntax %s : error\n", prev->value);
		return (1);
	}
	return (0);
}

int	check_inside(t_token *head, t_token *end)
{
	if (head == end)
	{
		printf("Minishell: syntax error near unexpected token ')'\n");
		return (1);
	}
	if (token_op(head->type))
	{
		printf("Syntax %s : error\n", head->value);
		return (1);
	}
	if (check_in_end(head, end))
		return (1);
	return (0);
}
