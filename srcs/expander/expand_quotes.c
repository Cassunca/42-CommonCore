/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:41 by kamys             #+#    #+#             */
/*   Updated: 2026/01/11 21:10:47 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	handle_single_quotes(char **res, char *s, int *i)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
		append_char(res, s[(*i)++]);
	if (s[*i] == '\'')
		(*i)++;
}

void	handle_double_quotes(char **res, char *s, int *i, t_env_table *env)
{
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
			handle_dolar(res, s, i, env);
		else
			append_char(res, s[(*i)++]);
	}
	if (s[*i] == '"')
		(*i)++;
}
