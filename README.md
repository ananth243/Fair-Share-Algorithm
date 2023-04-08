# Fair-Share-Algorithm
This repository contains C code implementation for the Fair Share Scheduler

# input.txt
This file contains the jobs that are to be scheduled
First line represents the number of jobs to be scheduled
Each job has 5 lines
First line: Group id
Second line: Base priority of the job
Third Line: Arrival time
Fourth Line: Number of CPU bursts
Fifth line: The array Worst Case CPU bursts
Sixth Line: An array of I/O bursts
Note: Number of I/O bursts SHOULD be 1 less than CPU bursts. Last I/O burst must have a value of -1 to indicate end of I/O burst Manual checking isn't implemented as of the moment.

To run the code:
make
./a.out <input_file> <time_slice>