Feature: I/O redirection
	Background:
		Given I run `sh142` interactively
	Scenario: Redirect stdout to a file
		When I type "echo foo >bar"
		And I exit
		Then the file "bar" should contain exactly:
		"""
		foo
		"""

	Scenario: redirect stderr to a file
		When I type "makeout err error to file 2>errfile"
		And I exit
		Then the stderr should contain exactly:
		"""
		"""
		And the stdout should contain exactly:
		"""
		"""
		And the file "errfile" should contain exactly:
		"""
		error to file
		"""

	Scenario: redirect command to stdin
		When I type "cut -d' ' -f2 <(echo foo bar baz)"
		And I exit
		Then the stdout should contain exactly:
		"""
		bar
		"""

	@skipme
	Scenario: redirect stderr to stdout
		When I type "makeout err error output 2>&1"
		And I exit
		Then the stderr should contain exactly:
		"""
		"""
		And the stdout should contain exactly:
		"""
		error output
		"""


