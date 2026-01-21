/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:01:42 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/21 15:12:10 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int is_delimiter(char *line, char *delimiter)
{
	int i;

	i = 0;
	while (line[i] && delimiter[i] && line[i] == delimiter[i])
		i++;
	if (delimiter[i] == '\0' && (line[i] == '\n' || line[i] == '\0'))
		return (1);
	return (0);
}

int	check_if_quoted(char *delimiter)
{
	int	len;

	if (!delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (len >= 2 && ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
			|| (delimiter[0] == '\"' && delimiter[len - 1] == '\"')))
		return (1);
	return (0);
}

static char	*get_var_value(char *name, t_shell *sh)
{
	char	*value;

	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(sh->last_status));
	value = env_get(sh->env, name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*extract_and_replace_var(char *str, t_shell *sh, int *global_i)
{
	int		len;
	char	*var_name;
	char	*value;

	len = 1;
	if (str[len] == '?')
		len++;
	else
		while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
	var_name = ft_substr(str, 1, len - 1);
	value = get_var_value(var_name, sh);
	free(var_name);
	*global_i += len;
	return (value);
}
char	*expand_variables_in_heredoc(char *line, t_shell *sh)
{
	int		i;
	char	*new_line;
	char	*tmp;
	char	*aux;

	i = 0;
	new_line = ft_strdup("");
	while(line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) ||
				line[i + 1] == '_' || line[i + 1] == '?'))
			tmp = extract_and_replace_var(&line[i], sh, &i);
		else
			tmp = ft_substr(line, i++, 1);
		aux = new_line;
		new_line = ft_strjoin(aux, tmp);
		free(aux);
		free(tmp);
	}
	free(line);
	return (new_line);
}
