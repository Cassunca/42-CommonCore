/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:56:28 by kamys             #+#    #+#             */
/*   Updated: 2025/12/22 01:11:36 by kamys            ###   ########.fr       */
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
		{
			depth--;
		}
	}
	if (p <= cwd)
	{
		return (cwd);
	}
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
		else if (s[i] == '%' && ft_isdigit(s[i + 1]) && s[i + 2] == 'd')
		{
			len += ft_strlen(expand_cwd(s[i]));
			i += 3;
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
			{
				val = env_get(env, "USER");
				i += 2;
			}
			else if (s[i + 1] == 'd')
			{
				val = cwd_with_tilde(env);
				i += 2;
			}
			else if (ft_isdigit(s[i + 1]) && s[i + 2] == 'd')
			{
				val = expand_cwd(s[i + 1]);
				i += 3;
			}
			else
			{
				res[j++] = s[i++];
				continue ;
			}
			while (*val)
				res[j++] = *val++;
			// if (s[i - 1] == 'd' && (i >= 2 && ft_isdigit(s[i - 2])))
			// 	free(val);
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
