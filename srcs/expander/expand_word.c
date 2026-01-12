/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:09:00 by kamys             #+#    #+#             */
/*   Updated: 2026/01/11 21:09:56 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_word(char *s, t_env_table *env)
{
	char	*res;
	int		i;

	(void)env;
	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			handle_single_quotes(&res, s, &i);
		else if (s[i] == '\"')
			handle_double_quotes(&res, s, &i, env);
		else if (s[i] == '$')
			handle_dolar(&res, s, &i, env);
		else if (s[i] == '~')
			handle_tilde(&res, s, &i, env);
		else
			append_char(&res, s[i++]);
	}
	free(s);
	return (res);
}
