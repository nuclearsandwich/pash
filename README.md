# sh142 #

*A not-quite-POSIX shell for Unix systems.*

Writing this for a class. Who knows when it will be open-sourced. Using
[Aruba][] to test it.

## Development dependencies ##

- A C compiler
- [Valgrind][] advanced dynamic profiler; a memory leak's worst nightmare.
- [splint][] static analysis tool for C.
- [Aruba][] for advanced CLI testing.
- [CTest][] for C unit testing.
- [Rocco][] for literate documentation.
- [Cucumber][] for automated behavio.ral testing. A dependency of Aruba.
- [Ruby][] >= 1.9.2 to run Cucumber.
- [GNU Make][] because IDEs are for chumps.

[Aruba]: https://github.com/cucumber/aruba
[Cucumber]: https://github.com/cucumber/cucumber
[Ruby]: http://ruby-lang.org
[CTest]: https://github.com/bvdberg/ctest
[Rocco]: http://rtomayko.github.com/rocco/
[splint]: http://splint.org/
[Valgrind]:http://valgrind.org/
[GNU Make]: http://www.gnu.org/software/make/

# TODO #

Create bootstrap script to get meta-dependencies installed.
