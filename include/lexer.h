/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:30:19 by kamys             #+#    #+#             */
/*   Updated: 2025/11/28 16:55:10 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum s_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_LIST,
	TK_LPAREN,
	TK_RPAREN,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// lexer_operetor.c
t_token	*tokenize_operetor(const char *s, int *i);

// lexer.c
int		isopertor(const char *s, int i);
t_token	*lexer(const char *s);
t_token	*new_token(t_token_type type, char *value);

// lexer_word.c
t_token	*tokenize_word(const char *s, int *i);

// lexer_utils.c
void	print_tokens(t_token *list);

#endif