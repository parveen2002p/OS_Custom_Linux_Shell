# OS_Custom_Linux_Shell
Implemented a custom shell having 8 different commands to execute using POSIX threads &amp; system calls. With error handling and 2 flags for each command.
Refer to the documentation for more details & test cases.
Run shell.c as main file.

Options handled:
cd: cd, cd ~, cd / , cd .. , cd path
pwd: pwd, pwd -L , pwd -P
echo: echo simple, echo -n , echo –help
ls : ls, ls -a , ls -m
date: date, date -u, date -r filename
cat : cat simple, cat -n, cat -e
rm : rm simple, rm -i , rm -v
mkdir : mkdir simple, mkdir -p , mkdir -v



