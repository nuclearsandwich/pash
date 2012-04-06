Feature: Command execution
	Background:
		Given I run `sh142` interactively

	Scenario: Executing a single command
		When I type "echo hello world!"
		And I exit
		Then the stdout should contain "hello world!"

	Scenario: Run multiple commands
		When I type "echo foobar"
		And I type "echo bazqux"
		And I exit
		Then the stdout should contain "foobar"
		And the stdout should contain "bazqux"
		And the exit status should be 0

