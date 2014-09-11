Name: David Greenberg

Time And Forking Children
___
The second project for comp 322

Takes in no values.

Stores the current number of cpu cycles and then prints them.   

The process then creates a child which prints it's own PID and PPID. 

The process then waits for the child to finish.

The process then prints the pid, the ppid, the retrieved value from the child, and the childid.

Then the system prints the cpu (user, system, cuser,csystem).

Finally it prints the end cpu cycles.

Note: The results may show zero as the program may not take any process cycles. I have tested this and found the results to change if a long enough for loop is included.  
