/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:38:02 by kamys             #+#    #+#             */
/*   Updated: 2026/01/08 12:41:27 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*skip_whitespace(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	return (s);
}

static char	*interpret_escapes(char *s)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(s) * 3 + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_strncmp(&s[i], "\\x1b", 4))
		{
			res[j++] = '\001';
			res[j++] = 27;
			res[j++] = '\002';
			i += 4;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*parse_ps1(t_env_table *env, char *line)
{
	char	*escaped;
	char	*final;

	escaped = interpret_escapes(line);
	if (!escaped)
		return (NULL);
	final = interpret_vars(env, escaped);
	free(escaped);
	return (final);
}
