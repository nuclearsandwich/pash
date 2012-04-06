Feature: Conditional operation
	Background:
		Given I run `sh142` interactively

	Scenario: Negation of an exit statuses using space-separated !
		When I type "! echo"
		And I type "echo $?1"
		Then the stdout should contain exactly:
		"""
		1
		"""

	Scenario: Negation of an exit statuses using near !
		When I type "!echo"
		And I type "echo $?1"
		Then the stdout should contain exactly:
		"""
		1
		"""

	Scenario: Logically AND-ing successful commands runs both
		When I type "mkdir foobar && cd foobar"
		And I type "pwd"
		Then the stdout should contain "foobar"

	Scenario: Logically AND-ing a failed command short circuits
		When I type "exitwith 1 && echo should not print"
		Then the stdout should not contain "should not print"

	Scenario: Logically OR-ing successful commands short circuits
		When I type "touch foobar || rm foobar"
		Then a file named "foobar" should exist

	Scenario: Logically AND-ing a failed command runs the subsequent one
		When I type "exitwith 128 || exitwith 32"
		And I type "echo $?1"
		Then the stdout should contain exactly:
		"""
		32
		"""


	Scenario: Mixing logical operators works fine and dandy
		When I type "!fail && fail || echo got all the way"
		Then the stdout should contain exactly:
		"""
		got all the way
		"""
