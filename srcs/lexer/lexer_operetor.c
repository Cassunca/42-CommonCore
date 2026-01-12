/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operetor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:46:57 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/11 21:21:09 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*tokenize_operetor(const char *s, int *i)
{
	int					j;
	int					len;
	static const t_op	ops[] = {
	{"<<", TK_HEREDOC},
	{">>", TK_APPEND},
	{"&&", TK_AND},
	{"||", TK_OR},
	{"|", TK_PIPE}, {";", TK_LIST},
	{"(", TK_LPAREN}, {")", TK_RPAREN},
	{"<", TK_REDIR_IN}, {">", TK_REDIR_OUT},
	{NULL, 0}
	};

	j = 0;
	while (ops[j].op)
	{
		len = ft_strlen(ops[j].op);
		if (!ft_strncmp(s + *i, ops[j].op, len))
		{
			*i += len;
			return (new_token(ops[j].type, ft_strdup(ops[j].op)));
		}
		j++;
	}
	return (NULL);
}
