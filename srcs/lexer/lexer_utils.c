/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:56:17 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/28 16:00:30 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

const char	*token_type_to_str(t_token_type type)
{
	if (type == TK_WORD)
		return ("WORD");
	if (type == TK_PIPE)
		return ("PIPE");
	if (type == TK_REDIR_IN)
		return ("<");
	if (type == TK_REDIR_OUT)
		return (">");
	if (type == TK_APPEND)
		return (">>");
	if (type == TK_HEREDOC)
		return ("<<");
	if (type == TK_AND)
		return ("&&");
	if (type == TK_OR)
		return ("||");
	if (type == TK_LIST)
		return (";");
	if (type == TK_LPAREN)
		return ("(");
	if (type == TK_RPAREN)
		return (")");
	return ("UNKNOWN");
}

void	print_tokens(t_token *list)
{
	int		i;
	char	*value;

	i = 0;
	while (list)
	{
		if (list->value)
			value = list->value;
		else
			value = "(null)";
		printf("[%d] Type: %-7s | Value: \"%s\"\n",
			i, token_type_to_str(list->type), value);
		list = list->next;
		i++;
	}
}
