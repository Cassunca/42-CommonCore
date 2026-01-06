/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:15:14 by kamys             #+#    #+#             */
/*   Updated: 2026/01/13 16:08:22 by amyrodri         ###   ########.fr       */
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

static char	*colorize_string(char	*color, char *s)
{
	char	*tmp;
	char	*result;

	if (!color || !s)
		return (NULL);
	tmp = ft_strjoin(color, s);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, RESET);
	free(tmp);
	return (result);
}

void	prompt_default(t_env_table *env)
{
	char	*user;
	char	*cwd;
	char	*tmp;
	char	*ps1;

	user = env_get(env, "USER");
	if (!user)
		user = "minishell";
	tmp = colorize_string(B_MAGENTA, ft_strjoin(user, "@minishell:"));
	cwd = colorize_string(B_CYAN, cwd_with_tilde(env));
	ps1 = ft_strjoin(tmp, cwd);
	free(tmp);
	tmp = ft_strjoin(ps1, " ❯ ");
	free(ps1);
	ps1 = tmp;
	env_set(env, "PS1", ps1);
	free(ps1);
	free(cwd);
}
