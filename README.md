# sh142 #

*A not-quite-POSIX shell for Unix systems.*

![Pash!](http://blog.nuclearsandwich.com/images/pash.png)

This was an assignment. It is now a labor of love. Hence, pash.

## Development dependencies ##

- A C compiler
- [Valgrind][] advanced dynamic profiler; a memory leak's worst nightmare.
- [Aruba][] for advanced CLI testing.
- [Cucumber][] for automated behavioral testing. A dependency of Aruba.
- [Ruby][] >= 1.9.2 to run Cucumber.
- [GNU Make][] because IDEs are for chumps.

[Aruba]: https://github.com/cucumber/aruba
[Cucumber]: https://github.com/cucumber/cucumber
[Ruby]: http://ruby-lang.org
[Valgrind]:http://valgrind.org/
[GNU Make]: http://www.gnu.org/software/make/

Writing Cucumber Specs
----------------------

Because we're good developers, we're writing pretty comprehensive tests to prove
or disprove our hypotheses about whether our software works. We've chosen
Cucumber and Aruba to do this in the most expressive and automated way possible.

For details on the language of Cucumber see existing examples in the `features/`
directory and the documentation of available "steps"
[here](https://github.com/cucumber/aruba/blob/master/lib/aruba/cucumber.rb).



C and UNIX Library Commands of Note
-----------------------------------

I've listed them below in the form necessary to look them up in the system
manual

- `man 3 getenv` For accessing environment variables.
- `man 3 setenv` For setting environment variables.
- `man 3 freopen` For reifying streams for redirection.
- `man 3 fprint` For printing to streams other than stdout.
- `posix_spawn` A possible way to easily run stuff in background.

