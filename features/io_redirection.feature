Feature: I/O redirection
	Background:
		Given I run `sh142` interactively
	Scenario: Redirect stdout to a file
		When I type "echo foo >bar"
		Then the file "bar" should contain exactly:
		"""
		foo
		"""

	Scenario: redirect stderr to a file
		When I type "makeout err error to file 2>errfile"
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
		Then the stdout should contain exactly:
		"""
		bar
		"""

	@skipme
	# Not actually required. I might do it later
	Scenario: redirect stderr to stdout
		When I type "makeout err error output 2>&1"
		Then the stderr should contain exactly:
		"""
		"""
		And the stdout should contain exactly:
		"""
		error output
		"""


