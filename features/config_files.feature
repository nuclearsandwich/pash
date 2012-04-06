Feature: Test config file loading
	Scenario: Setting variables in configs.
		Given a directory named "config_files"
		And a file named "config_files/config.sh142" with:
			"""
			CONVAR=test_value
			"""
		And a file named "config_files/config2.sh142" with:
			"""
			ANOTHER_VAR=test_value2
			"""
		When I cd to "config_files"
		And I run `sh142` interactively
		And I type "echo $CONVAR $ANOTHER_VAR"
		And I exit
		Then the stdout should contain "test_value test_value2"

