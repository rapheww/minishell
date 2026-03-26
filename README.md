*This project has been created as part of the 42 curriculum by rchaumei, lchambos.*

# Minishell

## Description

Minishell is a simplified Unix shell written in C, developed as part of the 42 School curriculum.  
The goal of this project is to recreate the core behavior of a real shell such as Bash, and to deeply understand how command interpretation, process creation, file descriptor management, and signal handling work internally.

This project focuses on:

- Process management (fork, execve, wait)
- Pipes and inter-process communication
- File descriptor duplication and redirections
- Environment variable handling
- Signal management
- Parsing and lexical analysis

Minishell is not a fully featured shell, but it reproduces essential Bash behaviors closely enough to understand how shells operate under the hood.


## Features

### Mandatory Features

- Display a prompt and wait for user input
- Maintain a working command history
- Execute commands using:
  - Absolute paths (/bin/ls)
  - Relative paths (./program)
  - $PATH resolution
- Handle:
  - Pipes (|)
  - Redirections:
    - Input (<)
    - Output (>)
    - Append (>>)
    - Heredoc (<<)
- Handle environment variables ($VAR)
- Handle $? (last exit status)
- Handle signals:
  - Ctrl-C
  - Ctrl-D
  - Ctrl-\
- Implement the following builtins:
  - echo (with -n)
  - cd
  - pwd
  - export
  - unset
  - env
  - exit


## Instructions

### Compilation

To compile the project:
```bash
make
```

Clean the project:
```bash
make clean # removes object files
make fclean # removes object files and executable
make re # rebuilds everything
```

### Execution

Run the shell:

./minishell

You should see a prompt similar to:

minishell$

You can now execute most commands just like in Bash.


## Resources

Official documentation and references:

- GNU Bash Manual: https://www.gnu.org/software/bash/manual/
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/
- Linux manual pages:
  man 2 fork
  man 2 execve
  man 2 pipe
  man 2 dup2
  man 3 readline

## AI Usage Disclosure

AI tools were used during the development of this project in the following ways:

- Understanding edge cases in shell behavior
- Debugging segmentation faults and memory leaks
- Reviewing parsing logic and suggesting refactoring improvements
- Improving documentation quality (README writing and structure)
