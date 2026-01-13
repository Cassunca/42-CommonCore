/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:32:19 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/13 15:32:59 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_ast		t_ast;
typedef struct s_redir		t_redir;
typedef enum s_node_type	t_node_type;
typedef enum s_redir_type	t_redir_type;
typedef struct s_cmd		t_cmd;

/* ========== EXEC ========== */

int		execute_ast(t_ast *root, t_env_table *env);
int		exec_simple_command(t_redir *redir, char *path_cmd,
			char **av, t_env_table *env);

/* ========== UTILS ========== */

void	free_char_array(char **arr);

/* ========== REDIRECT ========== */

int		apply_redirect(t_redir *redirs);

/* ========== PIPE/AND/OR ========== */

int		handle_pipe(t_ast *root, t_env_table *env);
int		handle_and(t_ast *root, t_env_table *env);
int		handle_or(t_ast *root, t_env_table *env);

/* ========== PATH ========== */

char	*resolve_path(char *cmd, t_env_table *env);

/* ========== CMD ========== */

int		execute_cmd(t_ast *cmd_node, t_env_table *env);

#endif
