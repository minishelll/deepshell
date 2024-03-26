/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwanii <sehwanii@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-03-25 10:10:43 by sehwanii          #+#    #+#             */
/*   Updated: 2024-03-25 10:10:43 by sehwanii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

static char	**parse_quote(t_list **list, char *command);

t_list  **tokenizer(char *command)
{
	// char    **words;
	// int     idx;
	t_list	*head;

	head = NULL;
	parse_quote(&head, command);
	while (head != NULL){
		printf("%s$\n",(char *)head->content);
		head = head -> next;
	}
	// idx = 0;
	// words = ft_split(command, '"');
	// while (words[idx] != NULL)
	// {

	// }
	return NULL;
}
static char	**parse_quote(t_list **list, char *command)
{
	char	state;
	int		idx;
	int		prev_idx;

	idx = -1;
	prev_idx = 0;
	while (command[++idx])
	{
		if (command[idx] == '\"' || command[idx] == '\'')
		{
			ft_lstadd_back(list, ft_lstnew(ft_strtrim(ft_substr(command, prev_idx, idx - prev_idx), " ")));
			state = command[idx];
			prev_idx = idx++;
			while (command[idx] != state && command[idx] != '\0')
				idx++;
			ft_lstadd_back(list, ft_lstnew(ft_strtrim(ft_substr(command, prev_idx, idx - prev_idx + 1), " ")));
			prev_idx = ++idx;
		}
	}
	return NULL;
}

int main(void)
{
	char *str = "echo \"asdf\" -e \"\' zxcv    \'   \" ";
	printf("%s\n", str);
	tokenizer(str);
}