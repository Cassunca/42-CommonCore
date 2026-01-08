/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:15:14 by kamys             #+#    #+#             */
/*   Updated: 2026/01/08 13:02:06 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

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
