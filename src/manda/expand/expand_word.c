/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:23:18 by taerankim         #+#    #+#             */
/*   Updated: 2024/05/03 19:47:55 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand.h"
#include "wildcard.h"

static int	_more_split(t_list *token)
{
	t_list	*orgnext;
	t_list	*curr;
	char	**split;
	int		i;

	if (ft_strchr(((t_token *)token->content)->word, ' ') == NULL)
		return (0);
	split = ft_split(((t_token *)token->content)->word, ' ');
	free(((t_token *)token->content)->word);
	((t_token *)token->content)->word = split[0];
	orgnext = token->next;
	curr = token;
	i = 1;
	while (split[i + 1] != NULL)
	{
		curr->next = ft_lstnew(new_token(ft_strdup(""), undefined));
		curr->next->next = ft_lstnew(new_token(split[i], word));
		curr = curr->next->next;
		i++;
	}
	curr->next = ft_lstnew(new_token(ft_strdup(""), undefined));
	curr->next->next = ft_lstnew(new_token(split[i], word));
	curr->next->next->next = orgnext;
	free(split);
	return (i);
}

static void	_skip_lst(t_list **curr, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		*curr = (*curr)->next;
		i++;
	}
}

static t_quote	_is_quote(t_token *token)
{
	const int	len = ft_strlen(token->word);

	if (len < 2)
		return (q_not);
	if (token->word[0] == '\'' \
	&& token->word[len - 1] == '\'')
		return (q_single);
	if (token->word[0] == '"' \
	&& token->word[len - 1] == '"')
		return (q_double);
	return (q_not);
}

static t_list	*_init_list(char *str)
{
	t_list	*head;
	t_list	*curr;

	head = parse_quote(str);
	curr = head->next;
	free(head);
	head = curr;
	while (curr != NULL)
	{
		if (((t_token *)curr->content)->word[0] != '\0')
			((t_token *)curr->content)->type = word;
		curr = curr->next;
	}
	return (head);
}

t_list	*expand_one_word(char *str, t_env *env)
{
	t_list	*head;
	t_list	*curr;
	t_token	*token;
	t_quote	quote;

	head = _init_list(str);
	curr = head;
	while (curr != NULL)
	{
		token = curr->content;
		quote = _is_quote(token);
		if (quote != q_single && ft_strchr(token->word, '$') != NULL)
			expand_variable(token, env);
		if (quote == q_not && ft_strchr(token->word, '*') != NULL)
			expand_wildcard(&head, &curr);
		else if (quote == q_not)
			_skip_lst(&curr, _more_split(curr));
		else
			token->word = ft_substr(token->word, 1, ft_strlen(token->word) - 2);
		curr = curr->next;
	}
	merge_word_nodes(&head);
	return (head);
}
