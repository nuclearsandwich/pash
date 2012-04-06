Feature: Exit status querying
	Scenario: Get the exit status of the last run program
		When I run `sh142` interactively
		And I type "exitwith 3"
		And I type "echo exit code was $?1"
		And I exit
		Then the stdout should contain "exit code was 3"

	Scenario: Get the exit status of the last nine run programs
		When I run `sh142` interactively
		And I type "exitwith 1"
		And I type "exitwith 2"
		And I type "exitwith 3"
		And I type "exitwith 4"
		And I type "exitwith 5"
		And I type "exitwith 6"
		And I type "exitwith 7"
		And I type "exitwith 8"
		And I type "exitwith 9"
		And I type "echo exit codes were $?1 $?2 $?3 $?4 $?5 $?6 $?7 $?8 $?9"
		And I exit
		Then the stdout should contain "exit codes were 9 8 7 6 5 4 3 2 1"

