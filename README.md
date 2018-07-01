# Round-Robin-Scheduler
Round-robin (RR) is one of the algorithms employed by process and network schedulers in computing. As the term is generally used, time slices (also known as time quanta) are assigned to each process in equal portions and in circular order, handling all processes without priority.

For more info read: [Round Robin Scheduler Wiki](https://en.wikipedia.org/wiki/Round-robin_scheduling)


## Problem Statement

You have to write a code which acts like a Round Robin scheduler. Your program will read an input file named Assign-1.ip. It will be a comma separated file containing a table like following (see the sample comma separated input file)

![table 1](../master/images/i1.png)

When user will start your program it will ask the user to enter the length of the quantum as following
```[pc@user ~ ]$ Enter the length of the quantum [1-100]:```

When a user enters any value between 1 to 100, it will schedule the jobs according to that quantum and save the order in which they execute into a comma separated file named Assign-1.op. In the above example suppose the value of quantum was given to be as 10, then its result will be the following table. The table will be saved in the form of a comma separated file as provided in the sample.

![table 2](../master/images/i2.png)

## How to Run

Simply run the "Round Robin Scheduler.cpp" file in any C++ compliant IDE. 
In order to open the Assign-1.ip and Assign-1.op files, you can use any editor like Notepad ++
