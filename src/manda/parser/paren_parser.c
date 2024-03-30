/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:45:39 by sehwjang          #+#    #+#             */
/*   Updated: 2024/03/30 15:50:05 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		parse_token(t_list **list, char *str);
static void	token_add_back(t_list **token_list, char *str);

static void	ft_free_split(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
		free(strs[i]);
	free(strs);
}

t_list	*parse_paren(t_list *quote_parsed_list)
{
	t_token	*token;
	t_list	*prev;
	t_list	*cur;
	t_list	*temp_list;
	char	**temp;
	char	**temp_tmp;

	temp_list = NULL;
	prev = quote_parsed_list;
	cur = quote_parsed_list->next;
	while (cur)
	{
		token = cur -> content;
		if (token ->type == undefined)
		{
			temp = ft_split(token->word, ' ');
			temp_tmp = temp;
			while (temp && *temp)
			{
				parse_token(&temp_list, *(temp));
				temp++;
			}
			ft_free_split(temp_tmp);
			free_token((prev->next)->content);
			free(prev->next);
			prev->next = temp_list;
			prev = ft_lstlast(temp_list);
			ft_lstadd_back(&temp_list, cur->next);
			temp_list = NULL;
		}
		else
			prev = cur;
		cur = cur->next;
	}
	t_token	*end_token;
	end_token = (t_token *)malloc(sizeof(t_token));
	end_token -> word = "$";
	end_token -> type = dollar_sign;
	ft_lstadd_back(&quote_parsed_list, ft_lstnew(end_token));
	return (quote_parsed_list->next);
}

void	parse_token(t_list **temp, char *str)
{
	int			i;
	int			prev_i;

	//printf("%s$\n",str);
	i = -1;
	prev_i = 0;
	while (str[++i])
	{
		if (str[i] == '&' || str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if (str[i + 1] == str[i])
			{
				token_add_back(temp, ft_substr(str, prev_i, i - prev_i));
				token_add_back(temp, ft_substr(str, i++, 2));
				prev_i = i + 1;
			}
			else if (str[i] != '&')
			{
				token_add_back(temp, ft_substr(str, prev_i, i - prev_i));
				token_add_back(temp, ft_substr(str, i, 1));
				prev_i = i + 1;
			}
		}
	}
	token_add_back(temp, ft_substr(str, prev_i, i - prev_i));
}

static void	token_add_back(t_list **token_list, char *str)
{
	t_token		*token;
	const int	len = ft_strlen(str);

	if (*str == '\0')
	{
		free(str);
		return ;
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (len == 2)
	{
		if (*str == '<')
			token->type = dless;
		else if (*str == '>')
			token->type = dgreat;
		else if (*str == '|')
			token->type = or_if;
		else if (*str == '&')
			token->type = and_if;
	}
	else if (len == 1)
	{
		if (*str == '<')
			token->type = less;
		else if (*str == '>')
			token->type = great;
		else if (*str == '|')
			token->type = pipe;
	}
	else
		token->type = undefined;
	token->word = ft_strtrim(str, " "); 
	ft_lstadd_back(token_list, ft_lstnew(token));
	free(str);
}
