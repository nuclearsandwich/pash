@announce
Feature: Testing aruba
	Scenario: Hello world in bash
		When I run `bash` interactively
		And I type "echo hello world!"
		And I type "exit"
		Then the stdout should contain "hello world!"
		And the exit status should be 0

