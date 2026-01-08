/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:56:28 by kamys             #+#    #+#             */
/*   Updated: 2026/01/08 15:07:19 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*cwd_tail(char *cwd, int depth)
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
	depth = limit - '0';
	if (depth < 1)
		depth = 1;
	if (depth > 9)
		depth = 9;
	tail = cwd_tail(cwd, depth);
	res = ft_strdup(tail);
	free(cwd);
	return (res);
}

char	*cwd_with_tilde(t_env_table *env)
{
	char	*cwd;
	char	*home;
	char	*res;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("~"));
	home = env_get(env, "HOME");
	if (!home)
		return (cwd);
	if (!ft_strncmp(cwd, home, ft_strlen(home)))
	{
		if (cwd[ft_strlen(home)] == '\0')
			res = ft_strdup("~");
		else
			res = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		return (res);
	}
	return (cwd);
}

void	prompt_default(t_env_table *env)
{
	char	*ps1;

	ps1 = "\x1b[01;31m%u"
		"\x1b[01;37m:"
		"\x1b[01;34m%d"
		"\x1b[01;37m > \x1b[0m";
	env_set(env, "PS1", ps1);
}
