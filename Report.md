# Project Report

## Abstract

Parallel computing is usually taken as a method of acceleration in order to deminish the running time of a program. However, it requires excellent implementation and ideal execution environment to get the desired speedup. There're many factors that could influence the performance of a multi-threaded program and those with negative effect have the potential to be the bottleneck of the entire program. In this project, we use multiple tools to profile a parallel program and analyze the result to determine what could be the potential bottleneck of this specific program.

## Introduction

## Literature Survey

## Proposed Idea

From all the research we have done, we have listed multiple types of bottleneck that could theoretically have a negative influence on the program.

> - IO
> - Network
> - Multiple loops
> - Barrier
> - Critical regions
> - Ordered constructs
> - Unbalanced loops

For each potential bottleneck we construct a example that contains this bottleneck. Then we use profiling tools to get the statistics of the execution of each program. With all the profiling statistics we have we could extract the characteristics of each type of bottleneck and use them to determine whether a provided multi-thread program have them or not.

To prove the accuracy of our method, we then construct another program with several parallel section, each presents a different type of bottleneck. Then we analyze this program with our method as an experiment to see if we can correctly get all the bottleneck types presented in this file.

## Experimental Setup

### Profiling tools

> - perf is a standard profiling infrastructure on Linux. It supports a huge number of events that could be recorded for measuring the performance of a machien or a task.
>
> > perf event list:
> >
> > - task-clock: time spent on the profiled task
> >
> > - context-switches: storing a state of a process.
> >
> > - mutex_acquired: number of times threads tried to acquire mutex.
> >
> > - cache-misses: application makes a request to retrieve data from a cache, but that specific data is not currently in cache memory.
> >
> > - sched:sched_stat_wait: time spent in waiting states
> >
> > - etc...
> >
> > We could use the statistics of some events to determine the type of bottleneck in the provided task.
> > Perf also has a feature called **annotate** which allows our to observe the statistics mapped to compiled instructions or even source code.
>
> - valgrind
>
> - gprof
>

> Perf command:

> sudo perf record -e task-clock,page-faults,context-switches,sched:sched_stat_blocked,sched:sched_stat_iowait,sched:sched_stat_runtime,sched:sched_stat_sleep,sched:sched_stat_wait,sched:sched_wait_task,sched:sched_wake_idle_without_ipi,syscalls:sys_enter_futex,writeback:writeback_wait -s ${executable} ${number of threads} && sudo perf report -T --sort=dso > ${report_filename}

## Experiments & Analysis

### Barrier

From the statistics measured using perf, we can find that the code with barrier has some traits comparing to the version without barrier:

- the run time of each thread is very balanced
- has more total waiting and sleeping time of all threads, the distribution of waiting time among all the threads are less diverse
- has a huge number occurances of calling futex and getting blocked, and a significant amount was raised by OpenMP library
- context switching and page faults happens a lot more

### Critical Region

We use the same methods as the techniques in the previous section trying to find the deterministic features that could help identify the code with huge critical region. And from the controlled experiment we have found that code with huge critical section generally has:

- a great number of wakening without inter-processor interrupt
- a lot more futex system call and almost entirely raised by OpenMP library
- a large number of page faults

### Ordered Construct

We use the same task which is duplication of a int array as an example to show how ordered parallel section could influence the efficiency of multi-thread program. We find that a ordered parallel section with ordered construct have the following characteristics:

- significantly slower
- a lot of futex system calls and most of them are called by OpenMP library
- many wakening of threads that are not due to inter-processor interrupt
- threads spent a lot more time sleeping and waiting on a runqueue
- a great number of context switches

### Unbalanced task

The statistics from our experiment on unbalanced task for each threads show us that code with unbalanced task could result in:

- higher running time
- more time in waiting state

## Conclusions

## References
