/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:39:55 by kamys             #+#    #+#             */
/*   Updated: 2026/01/08 17:01:48 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	append_prompt_value(t_env_table *env, char **val, char **res, int *j)
{
	char	*p;

	p = *val;
	while (*p)
		(*res)[(*j)++] = *p++;
	if (*val != env_get(env, "USER"))
		free(*val);
}

char	*resolve_prompt_token(t_env_table *env, char *s, int *i)
{
	char	*val;

	val = NULL;
	if (s[*i + 1] == 'u')
	{
		val = env_get(env, "USER");
		*i += 2;
	}
	else if (s[*i + 1] == 'd')
	{
		val = cwd_with_tilde(env);
		*i += 2;
	}
	else if (ft_isdigit(s[*i + 1]) && s[*i + 2] == 'd')
	{
		val = expand_cwd(env, s[*i + 1]);
		*i += 3;
	}
	return (val);
}

char	*interpret_vars(t_env_table *env, char *s)
{
	char	*res;
	char	*val;
	int		i;
	int		j;

	res = malloc(prompt_len(env, s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			val = resolve_prompt_token(env, s, &i);
			if (val)
			{
				append_prompt_value(env, &val, &res, &j);
				continue ;
			}
		}
		res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
