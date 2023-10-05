# Minishell - A Simple UNIX Shell Implementation ✅Grade 101/100

Minishell is a minimalistic shell program that replicates the basic functionalities of a Unix-like shell. It provides a command-line interface for interacting with the computer, executing commands, and managing processes. This README will explain the various features and capabilities of Minishell.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Redirection and Pipes](#redirection-and-pipes)
- [Environment Variables](#environment-variables)
- [Signals](#signals)
- [Exiting the Shell](#exiting-the-shell)

## Introduction

Minishell is a command-line shell designed to provide a user-friendly interface for executing commands on a computer. It was created to simplify the interaction with a computer by introducing a more human-readable way of sending instructions to the system.

## Features

Minishell includes the following features:

1. **Command Prompt**: Displays a prompt when waiting for a new command.

2. **Command History**: Maintains a command history for easy retrieval and execution.

3. **Executable Search**: Searches and launches the right executable based on the PATH variable or using a relative or absolute path.

5. **Quotation Handling**: Handles single quotes (' ') to prevent the interpretation of metacharacters. Handles double quotes (" ") except for $ (dollar sign).

6. **Redirections**: Supports input (<), output (>), input until a delimiter (<<), and output in append mode (>>).

7. **Pipes**: Implements pipes (|) to connect the output of one command to the input of the next command in a pipeline.

8. **Environment Variables**: Handles environment variables ($ followed by a sequence of characters) and expands them to their values.

9. **Exit Status**: Handles $? to expand to the exit status of the most recently executed foreground pipeline.

10. **Signal Handling**: Handles ctrl-C, ctrl-D, and ctrl-\ signals as in bash.

11. **Built-in Commands**: Implements essential built-in commands, including echo, cd, pwd, export, unset, env, and exit.

## Getting Started

To get started with Minishell, follow these steps:

1. Clone the Minishell repository to your local machine.

~~~shell
git clone https://github.com/your-username/minishell.git
~~~

2. Build the Minishell executable.

~~~shell
cd minishell
make
~~~

3. Run Minishell.

~~~shell
./minishell
~~~

## Usage

Once you have Minishell running, you can start using it like any other shell. Simply enter commands at the prompt, and Minishell will execute them. Below are some examples of how to use Minishell's features:

## Built-in Commands

Minishell includes several built-in commands that you can use directly from the shell:

- `echo [-n] [arguments]`: Print arguments to the standard output, with an option to omit the trailing newline.
- `cd [directory]`: Change the current working directory.
- `pwd`: Print the current working directory.
- `export [variable=value]`: Set or modify environment variables.
- `unset [variable]`: Unset environment variables.
- `env`: Display the current environment variables.
- `exit [status]`: Exit the shell with an optional exit status.

## Redirection and Pipes

Minishell supports input and output redirection, as well as pipes. Here are some examples:

- Input Redirection: `<` allows you to read from a file instead of standard input.

~~~shell
cat < file.txt
~~~

- Output Redirection: `>` allows you to write command output to a file.

~~~shell
ls > output.txt
~~~

- Input Until Delimiter: `<<` allows you to read input until a specified delimiter is encountered (without updating history).

~~~shell
cat << END
This is some text
END
~~~

- Output Redirection in Append Mode: `>>` appends command output to a file.

~~~shell
echo "New content" >> file.txt
~~~

- Pipes: `|` allows you to chain multiple commands, with the output of one command serving as the input to the next.

~~~shell
ls | grep "pattern"
~~~

## Environment Variables

You can use environment variables in Minishell by prefixing them with a `$`. For example:

~~~shell
$HOME
$PATH
~~~

## Signals

Minishell handles the following signals:

- `Ctrl-C`: Displays a new prompt on a new line.
- `Ctrl-D`: Exits the shell.
- `Ctrl-\`: Does nothing.

## Exiting the Shell

To exit Minishell, you can use the `exit` command or press `Ctrl-D`. The shell will terminate, returning an optional exit status.

