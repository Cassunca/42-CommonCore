/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:56:28 by kamys             #+#    #+#             */
/*   Updated: 2025/12/21 13:13:53 by kamys            ###   ########.fr       */
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

static size_t	prompt_len(t_env_table *env, char *s)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 'u')
		{
			len += ft_strlen(env_get(env, "USER"));
			i += 2;
		}
		else if (s[i] == '%' && s[i + 1] == 'd')
		{
			len += ft_strlen(cwd_with_tilde(env));
			i += 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*interpret_vars(t_env_table *env, char *s)
{
	char	*res;
	char	*val;
	int		i;
	int		j;

	res = malloc(prompt_len(env, s) + 1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			if (s[i + 1] == 'u')
				val = env_get(env, "USER");
			else if (s[i + 1] == 'd')
				val = cwd_with_tilde(env);
			else
			{
				res[j++] = s[i++];
				continue ;
			}
			while (*val)
				res[j++] = *val++;
			i += 2;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*parse_ps1(t_env_table *env, char *line)
{
	char	*raw;
	char	*escaped;
	char	*final;

	raw = ft_strtrim(line + 7, "\"\n");
	if (!raw)
		return (NULL);
	escaped = interpret_escapes(raw);
	free(raw);
	if (!escaped)
		return (NULL);
	final = interpret_vars(env, escaped);
	free(escaped);
	return (final);
}

void	init_ps1(t_env_table *env)
{
	char	*ps1;
	int		fd;

	if (env_get(env, "PS1"))
		return ;
	fd = open(".minishellrc", O_RDONLY);
	if (fd == -1)
		return (prompt_default(env));
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
			ps1 = parse_ps1(env, line);
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
