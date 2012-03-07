- Shell must be able to read shell configuration from files named \*.sh142 in
	the current directory if any.
- User should be able to dynamically set persistent executable path. i.e.
	`PATH=/home/usr/myname:/usr/bin`
- User should be able to dynamically set a persistent data file path:
	`DATA=/data/files:/home/usr/myname`
- User should be able to run any commands on the path
- User should be able to run a command with an argument being a data file as
	follows, and the shell should automatically locate the file in the data path
(DATA): `mycommand #D:datafileargument
- User should be able to check the exit status of the last few commands by
	executing $?1, $?2, ...
- User should be able to redirect stdin, stdout, stderr to files using the <, >,
	and 2> symbols.
- User should be able to pipeline a number of commands using the following
	syntax: `cmd1 | cmd2 | cmd3 ...`
- User should be able to execute commands conditionally: `!cmd1 && cmd2 ||
	cmd3..`
- User should be able to specify commands to run in the background. `cmd &`
- User should be able to bring background commands back to foreground.
- User should be able to query background jobs.
- User should be able to specify maximum amount of memory and CPU utilization
	that a command may use before being terminated by the shell.
	- `CPUMAX=99:200` (programs can run at most 200 seconds wit CPU utilization of
		99% or more.)
	- `MEMMAX=50M:360` (programs cannot exceed 50Megabytes for more than 360
		seconds)
	- `TIMEMAX=250` (programs can't run for more than 250 seconds)
- User should be able to iterate te execution of one or more commands as
	follows: `for (n=0;m < MAX; n++)\n com1; com2; ...; forend`
- User should be able to set and unset shell variables and use them in command
	lines. `MYPATH=/mydir; cmd1 $MYPATH/file`
- Shell must connect to remote shells and be able to support local and remote
	execution.
	- `node1:cmd1` (execute cmd1 in remote node1)
	- `localhost:cmd2` (execute cmd2 on local host)

