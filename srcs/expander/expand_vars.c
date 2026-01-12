/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:56 by kamys             #+#    #+#             */
/*   Updated: 2026/01/11 21:12:29 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	handle_dolar(char **res, char *s, int *i, t_env_table *env)
{
	char	*var;
	char	*val;
	int		start;

	(*i)++;
	if (s[*i] == '$')
	{
		append_str(res, env_get(env, "LAST_CODE"));
		(*i)++;
		return ;
	}
	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	var = ft_substr(s, start, *i - start);
	val = env_get(env, var);
	if (val)
		append_str(res, val);
	free(var);
}
