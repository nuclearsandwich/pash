Feature: PATH and DATA manipulation
	Scenario: Altering the PATH of the running shell.
		Given a directory named "mybin"
		And a file named "mybin/myprg" with:
		"""
		echo my program
		"""
		When I run `sh142` interactively
		And I type "PATH=./mybin:$PATH"
		And I type "myprg"
		And I exit
		Then the stdout should contain "my program"

	Scenario: Altering the DATA path of the running shell.
		Given a directory named "mydata"
		And a file named "mydata/food" with:
		"""
		gum,candy,pizza
		"""
		When I run `sh142` interactively
		And I type "DATA=./mydata:$DATA"
		And I type "cut -d, -f2 #D:food"
		And I exit
		Then the stdout should contain "candy"

