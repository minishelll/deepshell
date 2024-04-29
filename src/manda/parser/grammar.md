complete_command -> and_or
and_or -> pipeline
and_or -> and_or AND_IF pipeline
and_or -> and_or OR_IF pipeline
pipeline -> command
pipeline -> pipeline PIPE command
command -> simple_command
command -> subshell
command -> subshell redirect_list
subshell -> LPAREN and_or RPAREN
simple_command -> redirect_list cmd_word cmd_suffix
simple_command -> redirect_list cmd_word
simple_command -> redirect_list
simple_command -> cmd_word cmd_suffix
simple_command -> cmd_word
cmd_word -> WORD
cmd_suffix -> io_redirect
cmd_suffix -> cmd_suffix io_redirect
cmd_suffix -> WORD
cmd_suffix -> cmd_suffix WORD
redirect_list -> io_redirect
redirect_list -> redirect_list io_redirect
io_redirect -> io_file
io_redirect -> io_here
io_file -> LESS filename
io_file -> GREAT filename
io_file -> DGREAT filename
filename -> WORD
io_here -> DLESS here_end
here_end -> WORD