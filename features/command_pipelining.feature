Feature: Command pipelining
	Background:
		Given I run `sh142` interactively

	Scenario: piping one command's output to another
		When I type "echo foo bar baz | cut -d' ' -f2"
		Then the stdout should contain exactly:
		"""
		bar
		"""

	Scenario: chaining multiple commands
		When I type "echo the rain in Spain | cut -d' ' -f3 | wc -c"
		Then the stdout should contain exactly:
		"""
		2
		"""

