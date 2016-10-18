# pash #

*A not-quite-POSIX shell for Unix systems.*

![Pash!](http://nuclearsandwich.com/images/pash.png)

This was an assignment. It is now a labor of love. Hence, pash.

## Development dependencies ##

- A C compiler
- [Valgrind][] advanced dynamic profiler; a memory leak's worst nightmare.
- [GNU Make][] for compilation automation.

[Valgrind]:http://valgrind.org/
[GNU Make]: http://www.gnu.org/software/make/

C and UNIX Library Commands of Note
-----------------------------------

I've listed them below in the form necessary to look them up in the system
manual

- `man 3 getenv` For accessing environment variables.
- `man 3 setenv` For setting environment variables.
- `man 3 freopen` For reifying streams for redirection.
- `man 3 fprint` For printing to streams other than stdout.
- `posix_spawn` A possible way to easily run stuff in background.

