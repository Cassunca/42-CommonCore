/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:32:19 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/08 15:40:46 by cassunca         ###   ########.fr       */
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
void	exec_child(char *path_cmd, char **av, t_env_table *env);
int		exec_simple_command(char *path_cmd, char **av, t_env_table *env);

/* ========== UTILS ========== */

void	free_char_array(char **arr);

/* ========== REDIRECT ========== */

int		handle_redirect(t_ast *redir_node, t_env_table *env);
int		apply_redirect(t_redir *redirs);
t_ast	*new_redir_node(t_ast *cmd_node, t_redir_type type, char *file);

/* ========== PIPE/AND/OR ========== */

int		handle_pipe(t_ast *root, t_env_table *env);
int		handle_and(t_ast *root, t_env_table *env);
int		handle_or(t_ast *root, t_env_table *env);

/* ========== PATH ========== */

char	*resolve_path(char *cmd, t_env_table *env);
int		execute_builtin(t_cmd *cmd, t_env_table *env);
int		is_builtin(char **av);

/* ========== CMD ========== */

int		execute_cmd(t_ast *cmd_node, t_env_table *env);

#endif
