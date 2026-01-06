/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:28:05 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/06 12:45:52 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

/*
** TODO - Implementar export corretamente (padrão Bash)
**
** Regras Gerais:
**  - Se não houver argumentos -> imprimir todas variáveis exportadas
**    - Impressão deve ser em ordem alfabética
**    - Formato: declare -x KEY="VALUE"
**      * Se a variável não tem valor -> apenas: declare -x KEY
**
** Parsing / Validação:
**  - Verificar se o identificador é válido antes do '='
**    * Deve começar com letra ou '_'
**    * Pode conter números após o primeiro caractere
**    * Sem caracteres especiais como: - + / @ ! ? etc.
**    * Se inválido -> imprimir erro:
**        export: `argumento': not a valid identifier
**
** Manipulação de Variáveis:
**  - Suportar definições simples:
**      export KEY=VALUE
**
**  - Suportar variáveis sem '=':
**      export KEY
**      * Apenas marcar como exportada, sem alterar valor existente
**
**  - Suportar concatenação com '+=':
**      export KEY+=VALUE
**      * Se KEY já existe:
**          NOVO_VALOR = VALOR_ANTIGO + VALUE
**      * Se não existe:
**          KEY=VALUE (mesmo comportamento do Bash)
**
**  - Suportar múltiplos argumentos:
**      export A=1 B=2 C+=3 VAR
**
** Casos Especiais / Edge Cases:
**  - KEY=VALUE com vários '=' no valor:
**      export VAR=a=b=c
**      * O valor deve ser "a=b=c" sem quebrar errado no split
**
**  - Não sobrescrever valor antigo quando apenas exportado:
**      VAR=old -> export VAR -> não muda
**
**  - Atualizar corretamente o ambiente interno (env_set)
**    * Se já existir -> atualizar valor apenas se tiver '='
**
** Memória:
**  - Liberar corretamente arrays e strings usadas no split
**  - Evitar vazamento em qualquer retorno antecipado
**
** Erros:
**  - Não interromper parsing ao encontrar um erro
**    * Apenas printar erro e continuar nos próximos argumentos
**
** Exemplos que devem funcionar:
**  export       -> lista variáveis
**  export A     -> marca A como exportada
**  export A=1   -> define A e exporta
**  export A+=2  -> concatena
**  export 2A=3  -> erro de identificador
**
*/

static int	hash_len(t_env_table *table)
{
	size_t	count;
	size_t	i;
	t_env	*curr;

	count = 0;
	i = 0;
	while (i < table->size)
	{
		curr = table->buckets[i++];
		while (curr)
		{
			count++;
			curr = curr->next;
		}
	}
	return (count);
}

static char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*new_str;

	len1 = 0;
	len2 = 0;
	len3 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (s3)
		len3 = ft_strlen(s3);
	new_str = malloc(len1 + len2 + len3 + 1);
	if (!new_str)
		return (NULL);
	if (s1)
		ft_memcpy(new_str, s1, len1);
	if (s2)
		ft_memcpy(new_str + len1, s2, len2);
	if (s3)
		ft_memcpy(new_str + len1 + len2, s3, len3);
	new_str[len1 + len2 + len3] = '\0';
	return (new_str);
}

static int	key_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static int	key_cmp(const char *s1, const char *s2)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	len1 = key_len(s1);
	len2 = key_len(s2);
	while (i < len1 && i < len2)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (len1 - len2);
}

static void	order_array(char **array)
{
	int		i;
	int		j;
	char	*key;

	i = 1;
	while (array[i])
	{
		key = array[i];
		j = i - 1;
		while (j >= 0 && key_cmp(array[i], key) > 0)
		{
			array[j + 1] = array[i];
			j--;
		}
		array[j + 1] = key;
		i++;
	}
}

static void	print_export(char **order)
{
	int		i;
	char	*eq;

	i = 0;
	while (order[i])
	{
		write(1, "declare -x ", 11);
		eq = ft_strchr(order[i], '=');
		if (eq)
		{
			write(1, order[i], eq - order[i]);
			write(1, "=\"", 2);
			write(1, eq + 1, ft_strlen(eq) + 1);
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, order[i], ft_strlen(order[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void display_export(t_env_table *env)
{
	size_t	i;
	size_t	j;
	t_env	*curr;
	char	**order;

	order = malloc(sizeof(char *) * hash_len(env) + 1);
	i = 0;
	j = 0;
	while (i < env->size)
	{
		curr = env->buckets[i];
		while (curr)
		{
			order[j++] = ft_strjoin3(curr->key, "=", curr->value);
			curr = curr->next;
		}
		i++;
	}
	order[j] = NULL;
	order_array(order);
	print_export(order);
}

void	export(t_env_table *env, char *key_value)
{
	char	**split;
	char	*key;
	char	*value;

	if (!key_value)
		return (display_export(env));
	split = ft_split(key_value, '=');
	if (!split || !split[0] || !split[1])
		return ;
	key = split[0];
	value = split[1];
	env_set(env, key, value);
}
