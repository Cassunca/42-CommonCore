/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:56:28 by kamys             #+#    #+#             */
/*   Updated: 2025/12/21 00:44:02 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*interpret_escapes(char *s)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == 'x'
			&& s[i + 2] == '1' && s[i + 3] == 'b')
		{
			res[j++] = 27;
			i += 4;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*parse_ps1(char	*line)
{
	char	*raw;
	char	*ps1;

	raw = ft_strtrim(line + 7, "\"\n");
	if (!raw)
		return (NULL);
	ps1 = interpret_escapes(raw);
	free(raw);
	return (ps1);
}

void	init_ps1(t_env_table *env)
{
	char	*ps1;
	char	*user;
	int		fd;

	if (env_get(env, "PS1"))
		return ;
	fd = open(".minishellrc", O_RDONLY);
	if (fd == -1)
	{
		user = env_get(env, "USER");
		if (!user)
			user = "minishell";
		ps1 = ft_strjoin(user, ">_ ");
		env_set(env, "PS1", ps1);
		free(ps1);
		return ;
	}
	char	*line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, "#", 1))
		{
			free(line);
			continue ;
		}
		if (!ft_strncmp(line, "PROMPT=", 7))
		{
			ps1 = parse_ps1(line);
			env_set(env, "PS1", ps1);
			free(line);
			free(ps1);
			close(fd);
			return ;
		}
		free(line);
	}
	close(fd);
}

char	*get_prompt(t_env_table *env)
{
	char	*ps1;

	ps1 = env_get(env, "PS1");
	if (!ps1)
		return ("minishell$ ");
	return (ps1);
}
