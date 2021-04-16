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
> > - cpu-clock: total time spent on the cpu
> >
> > - task-clock: time spent on the profiled task
> >
> > - context-switches: storing a state of a process.
> >
> > - mutex_acquired: number of times threads tried to acquire mutex.
> >
> > - cache-misses: application makes a request to retrieve data from a cache, but that specific data is not currently in cache memory.
> >
> > - etc...
> >
> > We could use the statistics of some events to determine the type of bottleneck in the provided task.
> > Perf also has a feature called **annotate** which allows our to observe the statistics mapped to compiled instructions or even source code.
>
> - valgrind
> - gprof

## Experiments & Analysis

## Conclusions

## References
