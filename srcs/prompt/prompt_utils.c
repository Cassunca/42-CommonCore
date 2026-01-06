/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:56:28 by kamys             #+#    #+#             */
/*   Updated: 2026/01/06 18:41:46 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*cwd_tail(char *cwd, int depth)
{
	char	*p;

	if (!cwd || depth <= 0)
		return (cwd);
	p = cwd + ft_strlen(cwd);
	while (p > cwd && depth > 0)
	{
		p--;
		if (*p == '/')
			depth--;
	}
	if (p <= cwd)
		return (cwd);
	return (p + 1);
}

char	*expand_cwd(char limit)
{
	char	*cwd;
	char	*tail;
	char	*res;
	int		depth;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("~"));
	depth = ft_atoi(&limit);
	if (depth < 1)
		depth = 1;
	if (depth > 9)
		depth = 9;
	tail = cwd_tail(cwd, depth);
	res = ft_strdup(tail);
	free(cwd);
	return (res);
}
