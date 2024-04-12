#define INPUT "/bin/cat <in "
//#define INPUT "( /bin/echo A && /bin/cat -e ) <in "

#include <stdio.h>
#include "parser/tokenizer.h"
#include "parser/syntax_analyzer.h"
#include "parser/syntax_tree.h"
#include "parser/semantic_analyzer.h"
#include "execute/execute.h"

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

// void print_syntax_tree(t_syntax_tree *node) {
// 	if (node == NULL)
// 		return;
//     if (node->type == sym_command) {
// 		printf("Node Type: word\n");
// 		return; // 기저 조건: 노드가 NULL이면 종료
// 	}
//     // 현재 노드의 내용 출력
//     printf("Node Type: %d\n", node->type);
    
//     // 자식 노드를 재귀적으로 방문
//     for (int i = 0; i < 2; ++i) {
//         print_syntax_tree((t_syntax_tree *)node->child[i]);
//     }
// }

const char* get_syntax_type_name(t_symbol type) {
    switch (type) {
        case sym_and: return "AND";
        case sym_or: return "OR";
        case sym_pipe: return "PIPE";
        case sym_subshell: return "SUBSHELL";
        case sym_command: return "COMMAND";
        default: return "UNKNOWN";
    }
}

// t_syntax_tree를 출력하는 함수
void print_syntax_tree(t_syntax_tree *node, int level) {
	char **words;
	t_list	*redi_list;
	t_redi	*redi;
	int		flag = 0;
    if (node == NULL) return;
	if (*(get_syntax_type_name(node->type)) == 'U')
	{
		redi_list = (t_list *)node;
		
			for (int i = 0; i < level; ++i) printf("  "); // 레벨에 따른 들여쓰기
			printf("redi  :");
		while (redi_list)
		{
			redi = (t_redi *)redi_list->content;
			// for (int i = 0; i < level+1; ++i) printf("  "); // 레벨에 따른 들여쓰기
			printf("%s~",redi->file);
			redi_list =redi_list->next;
		}
		printf("\n");
		return ;
	}
	// if (node->type == sym_subshell)
	// {
	// 	print_syntax_tree((void *)node->child[0], level + 1);
	// }
	if (node->type == sym_command)
	{
		words = (char **)node->child[0];
		for (int i = 0; i < level; ++i) printf("  "); // 레벨에 따른 들여쓰기
		printf("words :\n");
		for (int i = 0; i < level+1; ++i) printf("  "); // 레벨에 따른 들여쓰기
		while (*words)
		{
			printf("%s~",*words++);
		}
		redi_list = (t_list *)node->child[1];
		printf("\n");
		
		if (redi_list)
		{
			flag = 1;
			for (int i = 0; i < level + 1; ++i) printf("  "); // 레벨에 따른 들여쓰기
			printf("redi  :");
		}
		while (redi_list)
		{
			redi = (t_redi *)redi_list->content;
			// for (int i = 0; i < level+1; ++i) printf("  "); // 레벨에 따른 들여쓰기
			printf("%s~",redi->file);
			redi_list =redi_list->next;
		}
		if(flag)
			printf("\n");
		return ;
	}

    // 현재 노드의 정보 출력
    for (int i = 0; i < level; ++i) printf("  "); // 레벨에 따른 들여쓰기
    printf("%s\n", get_syntax_type_name(node->type));

    // 자식 노드가 있다면 재귀적으로 출력
    for (int i = 0; i < 2; ++i) {
        if (node->child[i] != NULL) {
            print_syntax_tree((void *)node->child[i], level + 1);
        }
    }
}
int main()
{
	t_grammar		*grammar;
	t_lr_table		*lr_table;
	t_list			*token;
	t_parse_tree	*parse_tree;
	t_syntax_tree	*syntax_tree;
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
	//print_parse_tree(parse_tree, 0, "└───");
	syntax_tree = semantic_analyzer(parse_tree);
	//printf(BLUE "-----------print_syntax_tree\n" );
	//print_syntax_tree(syntax_tree, 0);
	printf(RESET "-----------result\n" );
	printf(RED "-----------exit: %d", execute(syntax_tree));
	printf(RESET "\n" );
}
