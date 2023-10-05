# minishell
### This project is about creating a simple shell. This shell has different functionalities:

- Display a prompt when waiting for a new command

- Working history

- Searchs and launches the right executable (based on the PATH variable or using a
relative or an absolute path)

- Single quote ('), which prevents the shell from interpreting the metacharacters in the quoted sequence

- Double quotes ("), which prevents the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign)

- Redirections (<, <<, >, >>)

- Pipes ( | )

- Environment variables ($ followed by a sequence of characters), also $?

- Signals ctrl-C, ctrl-D and ctrl-\


#### It also has the following built-ins:

- echo with option -n

- cd with only a relative or absolute path

- pwd with no options

- export with no options

- unset with no options

- env with no options or arguments

- exit with no options
