/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:28:05 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/05 17:30:29 by amyrodri         ###   ########.fr       */
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

// static void	add_array(char **order, char *key, char *value)
// {
	
// }

void	export(t_env_table *env, char *key_value)
{
	char	**split;
	char	*key;
	char	*value;

	if (!key_value)
	{
		size_t	i;
		t_env	*curr;
		char	**order;

		order = malloc(sizeof(char *) * hash_len(env) + 1);
		i = 0;
		while (i < env->size)
		{
			curr = env->buckets[i++];
			while (curr)
			{
				add_array(order, curr->key, curr->value);
				curr = curr->next;
			}
		}
		order[i + 1] = NULL;
		order_array(order);
		i = 0;
		while (order[i])
			printf("declare -x %s", order[i++]);
		return ;
	}
	split = ft_split(key_value, '=');
	if (!split || !split[0] || !split[1])
		return ;
	key = split[0];
	value = split[1];
	env_set(env, key, value);
}
