/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:09:00 by kamys             #+#    #+#             */
/*   Updated: 2026/01/27 14:58:44 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	scape_wildcard(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
			s[i] = '\a';
		i++;
	}
}

static int	with_quotes(char **res, char *s, int *i, t_shell *sh)
{
	int		quote;

	quote = 0;
	if (s[*i] == '\'')
	{
		handle_single_quotes(res, s, i);
		quote = 1;
	}
	else if (s[*i] == '\"')
	{
		handle_double_quotes(res, s, i, sh);
		quote = 1;
	}
	return (quote);
}

char	*expand_word(char *s, t_shell *sh, int *quote)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		*quote |= with_quotes(&res, s, &i, sh);
		if (!s[i])
			break ;
		if (s[i] == '$')
			handle_dolar(&res, s, &i, sh);
		else if (s[i] == '~')
			handle_tilde(&res, s, &i, sh);
		else
			append_char(&res, s[i++]);
	}
	if (*quote)
		scape_wildcard(res);
	free(s);
	return (res);
}
