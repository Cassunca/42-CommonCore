/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operetor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:46:57 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/28 16:50:33 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*match_two_char_token(int *i, const char *string, t_token_type tk)
{
	*i += 2;
	return (new_token(tk, ft_strdup(string)));
}

t_token	*tokenize_operetor(const char *s, int *i)
{
	char	c;

	if (s[*i] == '<' && s[*i + 1] == '<')
		return (match_two_char_token(i, "<<", TK_HEREDOC));
	if (s[*i] == '>' && s[*i + 1] == '>')
		return (match_two_char_token(i, ">>", TK_APPEND));
	if (s[*i] == '&' && s[*i + 1] == '&')
		return (match_two_char_token(i, "&&", TK_AND));
	if (s[*i] == '|' && s[*i + 1] == '|')
		return (match_two_char_token(i, "||", TK_OR));
	c = s[*i];
	(*i)++;
	if (c == '<')
		return (new_token(TK_REDIR_IN, ft_strdup("<")));
	if (c == '>')
		return (new_token(TK_REDIR_OUT, ft_strdup(">")));
	if (c == '|')
		return (new_token(TK_PIPE, ft_strdup("|")));
	if (c == ';')
		return (new_token(TK_LIST, ft_strdup(";")));
	if (c == '(')
		return (new_token(TK_LPAREN, ft_strdup("(")));
	if (c == ')')
		return (new_token(TK_RPAREN, ft_strdup(")")));
	return (NULL);
}
