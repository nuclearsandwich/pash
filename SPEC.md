1 Shell must be able to read shell configuration from files named \*.sh142 in
	the current directory if any. 
	*Test:* `features/confing_files.feature`

2 User should be able to dynamically set persistent executable path. i.e.
	`PATH=/home/usr/myname:/usr/bin` 
	*Test:*	`features/path_manipulation.feature:2`

3 User should be able to dynamically set a persistent data file path:
	`DATA=/data/files:/home/usr/myname` 
	*Test:*	`features/path_manipulation.feature:13`

4 User should be able to run any commands on the path
	*Test:* `features/path_manipulation.feature:2`

5 User should be able to run a command with an argument being a data file as
	follows, and the shell should automatically locate the file in the data path
	(DATA): `mycommand #D:datafileargument
	*Test:* `features/path_manipulation.feature:13`

6 User should be able to check the exit status of the last few commands by
	executing $?1, $?2, ... 
	*Test:* `features/exit_statuses.feature`

7 User should be able to redirect stdin, stdout, stderr to files using the <, >,
	and 2> symbols. 
	*Test:* `features/io_redirection.feature

8 User should be able to pipeline a number of commands using the following
	syntax: `cmd1 | cmd2 | cmd3 ...` 
	*Test:* `features/command_pipelining.feature`

9 User should be able to execute commands conditionally: `!cmd1 && cmd2 ||
	cmd3..` 
	*Test:* `features/conditional_operation.feature`

10 User should be able to specify commands to run in the background. `cmd &`
	*Test:* `features/background_jobs.feature`

11 User should be able to bring background commands back to foreground. 
    *Test:*	`features/background_jobs.feature`

12 User should be able to query background jobs. 
	*Test:*	`features/background_jobs.feature`

13 User should be able to specify maximum amount of memory and CPU utilization
	that a command may use before being terminated by the shell.
	- `CPUMAX=99:200` (programs can run at most 200 seconds wit CPU utilization of
		99% or more.)
	- `MEMMAX=50M:360` (programs cannot exceed 50Megabytes for more than 360
		seconds)
	- `TIMEMAX=250` (programs can't run for more than 250 seconds)
	*Test:* `features/resource_controls.feature`

14 User should be able to iterate the execution of one or more commands as
	follows: `for (n=0;m < MAX; n++)\n com1; com2; ...; forend`
	*Test:* `features/flow_control.feature`

15 User should be able to set and unset shell variables and use them in command
	lines. `MYPATH=/mydir; cmd1 $MYPATH/file`
	*Test:* `features/set_variables.feature`

16 Shell must connect to remote shells and be able to support local and remote
	execution.
	- `node1:cmd1` (execute cmd1 in remote node1)
	- `localhost:cmd2` (execute cmd2 on local host)
	*Test:* `features/remote_exec.feature`

