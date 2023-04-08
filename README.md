# Fair-Share-Algorithm
This repository contains C code implementation for the Fair Share Scheduler

## Input file
This file contains the jobs that are to be scheduled
First line represents the number of jobs to be scheduled
Each job has 3 lines
<br/>
First line: Group id, Base Priority, Arrival Time, Number Of CPU Bursts
<br/>
Second line: The array Worst Case CPU bursts
<br/>
Third Line: The array of I/O bursts

## Note
Number of I/O bursts SHOULD be 1 less than CPU bursts. Last I/O burst must have a value of -1 to indicate end of I/O burst. Manual checking isn't implemented as of the moment. We are assuming all jobs are successful hence -1

## Executing
To run the code:
```bash
make
./a.out <input_file> <time_slice>
```