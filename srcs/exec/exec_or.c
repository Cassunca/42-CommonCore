/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:29:12 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/08 15:21:32 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_or(t_ast *root, t_env_table *env)
{
	int	status;

	status = execute_ast(root->left, env);
	if (status != 0)
		return (execute_ast(root->right, env));
	return (status);
}
