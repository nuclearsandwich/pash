#13 User should be able to specify maximum amount of memory and CPU utilization
#	that a command may use before being terminated by the shell.
#	- `CPUMAX=99:200` (programs can run at most 200 seconds wit CPU utilization of
#		99% or more.)
#	- `MEMMAX=50M:360` (programs cannot exceed 50Megabytes for more than 360
#		seconds)
#	- `TIMEMAX=250` (programs can't run for more than 250 seconds)
#	*Test:* `features/resource_controls.feature`