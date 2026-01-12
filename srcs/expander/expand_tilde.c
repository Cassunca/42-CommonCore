/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:49 by kamys             #+#    #+#             */
/*   Updated: 2026/01/11 21:10:12 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	handle_tilde(char **res, char *s, int *i, t_env_table *env)
{
	if (*i == 0 || s[*i - 1] == ' ')
		append_str(res, env_get(env, "HOME"));
	else
		append_char(res, s[*i]);
	(*i)++;
}
