#define INPUT "cat | ( echo A | cat -e ) | sleep 5 && ls -l /bin/."

#include <stdio.h>
#include "parser.h"
#include "parser/syntax_analyzer.h"
#define RED      "\x1b[31m"
#define RED      "\x1b[31m"
#define GREEN    "\x1b[32m"
#define YELLOW   "\x1b[33m"
#define BLUE     "\x1b[34m"
#define MAGENTA  "\x1b[35m"
#define CYAN     "\x1b[36m"
#define RESET    "\x1b[0m"

void	token_print(t_token *token, int depth, char *arrow)
{
	char *termi_str[12] = {"and_if", "or_if", "pipe", "lparen", "rparen", "word", "less", "great", "dgreat", "dless", "dollar_sign", "undefined"};

	for(int i = 0; i <= depth; i++)
		printf("  ");
	printf("%s", arrow);
	if (token->type == word)
	{
		printf(RESET "%s, ", termi_str[token->type]);
		printf(RED   "%s", token->word);
	}
	else
	{
		printf(BLUE  "%s, ", termi_str[token->type]);
		printf(YELLOW "%s", token->word);
	}
	printf(RESET "\n");
}
void	parse_tree_print(t_parse_tree *parse_tree, int depth, char *arrow)
{
	char *non_termi_str[14] = {"complete_command", "and_or" \
				, "pipeline", "command", "subshell", "simple_command"\
				, "cmd_word", "cmd_suffix", "redirect_list", "io_redirect"\
				, "io_file", "filename", "io_here", "here_end"};

	for(int i = 0; i < depth; i++)
		printf("  ");
	printf("%s%s\n", arrow, non_termi_str[parse_tree->type]);
}

void	print_parse_tree(t_parse_tree *parse_tree, int depth, char *arrow)
{

	parse_tree_print(parse_tree, depth, arrow);
	if (parse_tree->child_type[LEFT] == non_terminal)
	{
		if (parse_tree->child_type[MID] == none\
		&& parse_tree->child_type[RIGHT] == none)
			print_parse_tree(parse_tree->child[LEFT], depth + 1, "└───");
		else
			print_parse_tree(parse_tree->child[LEFT], depth + 1, "├───");
	}
	else if (parse_tree->child_type[LEFT] == terminal)
	{
		if (parse_tree->child_type[MID] == none\
		&& parse_tree->child_type[RIGHT] == none)
			token_print(parse_tree->child[LEFT], depth, "└───");
		else
			token_print(parse_tree->child[LEFT], depth, "├───");
	}
	if (parse_tree->child_type[MID] == non_terminal)
	{
		if (parse_tree->child_type[RIGHT] == none)
			print_parse_tree(parse_tree->child[MID], depth + 1, "└───");
		else
			print_parse_tree(parse_tree->child[MID], depth + 1, "├───");
	}
	else if (parse_tree->child_type[MID] == terminal)
	{
		if (parse_tree->child_type[RIGHT] == none)
			token_print(parse_tree->child[MID], depth, "└───");
		else
			token_print(parse_tree->child[MID], depth, "├───");
	}
	if (parse_tree->child_type[RIGHT] == non_terminal)
	{
		print_parse_tree(parse_tree->child[RIGHT], depth + 1, "└───");
	}
	else if (parse_tree->child_type[RIGHT] == terminal)
		token_print(parse_tree->child[RIGHT], depth, "└───");
	return ;
}

int main()
{
	t_grammar		*grammar;
	t_lr_table		*lr_table;
	t_list			*token;
	t_parse_tree	*parse_tree;

	grammar = insert_grammar();
	lr_table = insert_lr_table();
	token = tokenizer(INPUT);

	//// char *terminal_str[12] = {"and_if", "or_if", "pipe", "lparen", "rparen", "word", "less", "great", "dgreat", "dless", "dollar_sign", "undefined"};
	//for(t_list *curr = token; curr != NULL; curr = curr->next)
	//{
	//	if (((t_token *)curr->content)->word[0] == '(')
	//		((t_token *)curr->content)->type = lparen;
	//	else if (((t_token *)curr->content)->word[0] == ')')
	//		((t_token *)curr->content)->type = rparen;
	//	else if (((t_token *)curr->content)->type == undefined)
	//		((t_token *)curr->content)->type = word;
	//	// printf("%s| ", terminal_str[((t_token *)curr->content)->type]);
	//	// printf("%s\n", ((t_token *)curr->content)->word);
	//	if (curr->next == NULL)
	//		((t_token *)curr->content)->type = dollar_sign;
	//}

	parse_tree = syntax_analyzer(token, grammar, lr_table);

	print_parse_tree(parse_tree, 0, "└───");
	printf(RED "FINISH" );
	printf(RESET "\n" );
}
