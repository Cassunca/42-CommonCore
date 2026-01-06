/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:36:21 by kamys             #+#    #+#             */
/*   Updated: 2026/01/06 18:37:22 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	handle_ps1(t_env_table *env, char *line)
{
	char	*trim;
	char	*ps1;

	trim = skip_whitespace(line);
	if (*trim == '#' || *trim == '\0')
		return (0);
	if (!ft_strncmp(trim, "PROMPT=", 7))
	{
		ps1 = parse_ps1(env, line);
		if (ps1)
		{
			env_set(env, "PS1", ps1);
			free(ps1);
		}
		return (1);
	}
	return (0);
}

static int	load_rc(t_env_table *env)
{
	int		fd;
	char	*line;

	fd = open(".minishellrc", O_RDONLY);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (handle_ps1(env, line))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
	}
	close(fd);
	return (0);
}

void	init_ps1(t_env_table *env)
{
	if (env_get(env, "PS1"))
		return ;
	if (!load_rc(env))
		prompt_default(env);
}

char	*get_prompt(t_env_table *env)
{
	char	*ps1;

	ps1 = env_get(env, "PS1");
	if (!ps1)
		return ("minishell$ ");
	return (ps1);
}
