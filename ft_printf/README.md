# ft_printf
A remake from scratch of the printf command in C.

# Steps to run
1) clone repo in desired directory. `git clone https://github.com/zill4/42_projects.git`

2) Make sure to have gcc installed. Compile and build the code with `make` command

3) This will generate a `libftprintf.a` libary file you can link to a C project using `-L libftprintf.a`
  You can learn more about linking with Makefiles and what not here: https://www.linuxtopia.org/online_books/an_introduction_to_gcc/gccintro_17.html

4) You can use the following flags `cspdiouxXhhll` but there may be a memory leak so just check it out for fun.
