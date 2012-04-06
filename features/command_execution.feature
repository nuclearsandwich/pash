Feature: Command execution
	Background:
		Given I run `sh142` interactively

	Scenario: Executing a single command
		When I type "echo hello world!"
		Then the stdout should contain "hello world!"

	Scenario: Run multiple commands and exit
		When I type "echo foobar"
		When I type "echo bazqux"
		When I type "exit"
		Then the stdout should contain "foobar"
		And the stdout should contain "bazqux"
		And the exit status should be 0

