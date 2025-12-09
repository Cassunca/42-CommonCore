/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:37:31 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/09 18:45:39 by amyrodri         ###   ########.fr       */
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

int	check_borders(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	if (token_op(head->type))
	{
		printf("Syntax %s : error\n", head->value);
		return (1);
	}
	while (head->next)
		head = head->next;
	if (token_op(head->type))
	{
		printf("Syntax %s : error\n", head->value);
		return (1);
	}
	return (0);
}

int	check_next_token(t_token *tokens)
{
	if (token_op(tokens->type))
	{
		if (token_op(tokens->next->type))
		{
			printf("Syntax %s : error\n", tokens->next->value);
			return (1);
		}
	}
	return (0);
}

t_token	*check_paren(t_token *tokens)
{
	int	depth;

	depth = 0;
	if (tokens->type != TK_LPAREN)
		return (NULL);
	while (tokens)
	{
		printf("paren:  %s\n", tokens->value);
		if (tokens->type == TK_LPAREN)
			depth++;
		else if (tokens->type == TK_RPAREN)
		{
			depth--;
			if (depth == 0)
				return (tokens);
		}
		tokens = tokens->next;
	}
	if (depth > 0)
		printf("syntax: unexpected '('\n");
	return (NULL);
}

int	check_syntax(t_token *tokens)
{
	t_token	*head;
	t_token	*end;

	head = tokens;
	if (check_borders(head))
		return (1);
	while (head)
	{
		if (check_next_token(head))
			return (1);
		if (head->type == TK_LPAREN)
		{
			end = check_paren(head);
			if (!end)
				return (1);
			head = end->next;
			continue ;
		}
		if (head->type == TK_RPAREN)
		{
			printf("syntax: unexpected ')'\n");
			return (1);
		}
		printf("check:  %s\n", head->value);
		head = head->next;
	}
	return (0);
}
