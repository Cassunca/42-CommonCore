/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:35:20 by kamys             #+#    #+#             */
/*   Updated: 2025/11/28 16:54:06 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	add_token(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	isopertor(const char *s, int i)
{
	if (s[i] == '&' && s[i + 1] == '&')
		return (1);
	if (s[i] == '|' && s[i + 1] == '|')
		return (1);
	if (s[i] == '<' && s[i + 1] == '<')
		return (1);
	if (s[i] == '>' && s[i + 1] == '>')
		return (1);
	if (s[i] == '|' || s[i] == ';'
		|| s[i] == '<' || s[i] == '>'
		|| s[i] == '(' || s[i] == ')')
		return (1);
	return (0);
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

t_token	*lexer(const char *s)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			i++;
			continue ;
		}
		if (s[i] == '\0')
			break ;
		if (isopertor(s, i))
		{
			add_token(&list, tokenize_operetor(s, &i));
			continue ;
		}
		add_token(&list, tokenize_word(s, &i));
	}
	return (list);
}
