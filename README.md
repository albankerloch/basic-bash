# Basic bash

An homemade bash for Unix

Features :
- Print a prompt for the user
- Find and launch the correct executable (based on the PATH or the absolute or relative path)
- Implement redirections : >, <, >>, <<
- Manage single and double quotes : ', ''
- Implement pipes : |
- Manage ctrl-C, ctrl-D et ctrl-\
- Manage environement viariable and $?
- Implement those builtins :
  - echo
  - cd (only with and absolute or relative path)
  - pwd (without options)
  - export (without options) 
  - unset (without options) 
  - env (without options)
  - exit(without options)
- No memory leak
- No more than 25 lines for every functions

## Installation

Use the makefile with this command : 


```bash
make
```

(clang and make needed)

## Usage

```bash
./minishell

# a prompt will appeared to be used as bash
```
#### Author : Alban Kerloc'h, Alice Duchemin
#### Category: Low-level
#### Tag: C
