/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:52:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/28 16:03:20 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*tokenize_word(const char *s, int *i)
{
	int		j;
	int		start;
	char	quote;
	char	*word;

	start = *i;
	j = *i;
	while (s[j] && !ft_isspace(s[j]) && !isopertor(s, j))
	{
		if (s[j] == '\'' || s[j] == '\"')
		{
			quote = s[j];
			j++;
			while (s[j] && s[j] != quote)
				j++;
			if (!s[j])
				break ;
			j++;
		}
		else
			j++;
	}
	word = ft_substr(s, start, j - start);
	*i = j;
	return (new_token(TK_WORD, word));
}
