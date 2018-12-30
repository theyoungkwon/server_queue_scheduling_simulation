## Server Queue Scheduling Simulation

#### Description
Analyzed conditions which cause bottle neck situation in a simulated environment. 
Improved the efficiency of server queue scheduling with limited resources.


#### How to run the code
 - move to working directory.

$make : make object files and executable file named "main"


 - take input.txt as input. Then display statistics as output.
 - also display results of Mini Factory program.
$./main < input.txt: run executable file (main)


#### object files
- main.o : main object file of Mini Factory simulation.
- setup.o : object file which has classes and structures used in other object files (process_module.o, server_module.o, connection_module.o, time_module.o)
- process_module.o : object file which declare and define behavior of process
- server_module.o : object file which declare and define behavior of server
- connection_module.o : object file which declare and define behavior of way and bus
- time_module.o : object file which declare and define behavior of time event
