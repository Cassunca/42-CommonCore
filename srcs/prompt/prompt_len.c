/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:40:56 by kamys             #+#    #+#             */
/*   Updated: 2026/01/06 18:41:21 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

size_t	prompt_len(t_env_table *env, char *s)
{
	size_t	len;
	char	*val;
	int		i;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			val = resolve_prompt_token(env, s, &i);
			if (val)
			{
				len += ft_strlen(val);
				if (val != env_get(env, "USER"))
					free(val);
				continue ;
			}
		}
		len++;
		i++;
	}
	return (len);
}
