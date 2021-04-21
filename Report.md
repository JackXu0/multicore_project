# Project Report

## Abstract

Parallel computing is usually taken as a method of acceleration in order to deminish the running time of a program. However, it requires excellent implementation and ideal execution environment to get the desired speedup. There're many factors that could influence the performance of a multi-threaded program and those with negative effect have the potential to be the bottleneck of the entire program. In this project, we use multiple tools to profile a parallel program and analyze the result to determine what could be the potential bottleneck of this specific program.

## Introduction

Parallel computing is a surging topic in science and engineer for faster application processing. Parallel computing breaks a computational problem into multiple pieces and solves each of them on a separate CPU simultaneously.

OpenMP is a simple and flexible API for creating paralleled programs. Paralleled blocks in OpenMP typically start with the keyword **#pragma omp**. Inside such blocks, programmers can define tasks to parallelize. Creating an OpenMP program is easy, but the resulting code may not deliver the expected level of performance. Ideally, tasks defined in each OpenMP block will achieve nearly X times speed up with X computation resources (CPUs or cores). However, this is more often not the case.

Lots of factors can negatively affect the performance of a parallel computing task, such as memory conflicts, synchronization overhead, load unbalancing, and limited shared resources. These problems appear on the code as bottlenecks, which refer to lines or blocks of code that constrain the parallel computing task to scale or speed up. Bottlenecks could cause the parallel program to not fully utilize the hardware resources, thus the overhead of thread management and synchronization could undermine the potential speedup or could even make the program run slower than its serial counterpart. Programmers can eliminate many of these bottlenecks and improve the efficiency of the program if they know where these bottlenecks might be.

This project aims to find a way to detect and locate potential bottlenecks in parallel programs and helps programmers improve the code. We mainly use several profiling tools to get the statistics of several events during the program's execution and use the data to determine what types of bottleneck might exist in the code. And then we would try to determine the location of the bottleneck by mapping the statistics to the source code to see which part of the code that takes up the most time.

## Literature Review

### Reasons for Bottlenecks

#### Shared menory and data locality

Memory is a prominent factor that limits the performance of a shared memory program [] and prevents it from scalable speedup. On scalable architecture, the latency and bandwidth of memory access depend on the locality of data access []. To achieve a good speedup of shared memory, data locality is an essential element. Data locality defines how close compute and input data are []. In distributed systems, initial data distribution determines on which node the memory is placed. Data locality at this level can be strengthened by algorithms such as first touch and explicit page placement.

During execution, data locality is mainly affected by scheduling algorithms and cache friendless. Scheduling algorithms determine which thread access which data. Effective scheduling algorithms such as work stealing [] can achieve good data locality and overall performance. Cache friendliness, on the other way, determines how often the main memory is accessed. In achieving cache friendliness, a high locality of references and low contention is required. The locality of reference is achieved by exploiting the spatial locality and temporal locality, and low cache contention avoids sharing cache lines among different objects. High cache friendliness improves the performance in both serial and parallel loops. Besides cache friendliness, page locality also plays an important role in affecting performance. In applications with full-page locality, pages accessed by a process are on the same node as the process, and no page is accessed by more than one process. Great page locality can bring both low memory latency and high scalability of memory bandwidth.

#### Wait and load unbalance

Unnecessary waiting and load unbalancing will waste computation resources and decrease the parallel performance.

- ##### Mutual exclusion

Mutual exclusion makes sure that if one process is using a shared variable or file, the other processes will be excluded from doing the same thing. In OpenMP, mutual exclusion can be implemented using critical regions. Too many critical regions can cost tremendous time on waiting.

```c
#pragma omp parallel{
    # pragma omp critical{

    }
}
```

- ##### Ordered constructs

In OpenMP, the ordered construct serializes and orders the execution of the ordered regions while allowing code outside the region to run in parallel. Poor use of this keyword may downgrade a parallel program into a serial program.

```c
#pragma omp parallel
{
	#pragma omp for ordered
 	for (n=0;n<10;n++)
  		#pragma omp ordered
}
```

- ##### Barrier and unbalanced loop

A barrier defines a point in code where all active threads will stop until all the threads have arrived at that point. With barrier, certain calculations are guaranteed to finish. A barrier will idle CPU resources if the parallel task is unbalanced.

```c
# pragma omp parallel{
    # pragma omp for 
    for(int i=0; i<4; i++){
        if(i == 0)
      		long_task();
  		else
      		short_task();
    }
    # pragma omp barrier
}
```

### Performance analyze tools

A range of performance profiling tools exists for parallel programs due to their complexity. Parallel machines not only have many copies of resources, such as CPU, and I/O system, that can cause bottlenecks in sequential programs, but they also include unique bottleneck contributors such as interconnected network and coherence protocols. Adding to the complexity is the diversity of the hardware being used in today's parallel computers. In all, they lead to a variety of different approaches in parallel performance tools. In general, these tools can be divided into three categories: performance matrix, search-based tools, and performance visualization.

Performance Matrix tools collect statistical data about a parallel program. Typical profiled resources include CPU utilization, synchronization time, disk operations, cache performances, etc. gprof [] is a tool to collect timing statistics. Basically, it looks into each of the functions and inserts code at the head and end of each one to collect time information. However, gprof requires recompiling the entire application, which may impose much overhead if the program is large. Strace [] is another profiling tool that focuses on monitoring and tampering with interactions between processes and the Linux kernel, which include system calls, signal deliveries, and changes of process state. We use strace to generate syscall dumps per running thread with precise time stamps and duration for each syscall. Valgrind [] is an instrumentation framework for building dynamic analysis tools. It is a great tool for collecting memory and cache-related data.

Search-based tools treat the problem of finding bottlenecks as a search problem. Instead of offering an abundance of statistics. They attempt to identify the problem and provide users with guidance. One example is Performance Consultant [], It uses a hierarchical three-axis search model (the why, where, when of a performance bottleneck). The 'why' bottleneck represents hypotheses about potential bottlenecks in a paralleled program. The 'Where' axis indicates a collection of resource hierarchies, such as CPU, interconnect, and memory, that could cause a bottleneck. The 'when' axis isolates the bottleneck to a specific phase of program execution. We did not find a runnable implementation of Performance Consultant online. Instead, we adopted the idea of the Performance Consultant and emulated the process manually.

Performance visualization displays the consumption of resources in a human-friendly way. One example is PIE [], PIE provides colorful views of parallel computation. It visualizes CPU status at every point of time, and makes it intuitive to know when the CPU is spinning, in use, or blocked.

Perf is a performance profiling tool that provides all three functionalities. It can collect a wide range of statistics, while it also provides an interface to search for bottlenecks using the keyword 'annotate'. Meanwhile, it can generate a call graph that visualizes the resource consumption hierarchy. Moreover, it exploits facilities provided by the Linux kernel to do statistical profiling, which creates a much lower overhead compared with other tools [].

## Proposed Idea

Parallel programs written in OpenMP can be divided into two parts. One part contains serial codes, and the other part contains parallel blocks. The first step is to check whether each parallel block speeds up while the cores and threads increase. This step roughly locates the bottlenecks. The second step is to run profiling tools and get the metrics. The metrics provides insights to programmers to help them understand why their progras does not run fast enough.

From all the research we have done, we have listed multiple types of bottleneck that could theoretically have a negative influence on the program.

> - IO
> - Network
> - Multiple loops
> - Barrier
> - Critical regions
> - Ordered constructs
> - Unbalanced loops

We would analyze the bottleneck and use our insight to determine what kind of events that would occur unusually frequent than they should be in an ideal environment. Then we would measure all those events we have gathered using profiling tools to get the data we need to confirm our judgement.

For each potential bottleneck we construct a example that contains this type of bottleneck. Then we use profiling tools to get the statistics of the execution of each program. With all the profiling statistics we have we could extract the characteristics of each type of bottleneck and use them to determine whether a provided multi-thread program have them or not.

To prove the accuracy of our method, we then construct another program with several parallel section, each presents a different type of bottleneck. Then we analyze this program with our method as an experiment to see if we can correctly get all the bottleneck types presented in this file.

We would also conduct experiments with different hyperparameters like task data size and number of threads if applicable. The trend of the speed up would also be a factor that could help us to make the decision.

And in our experiment we have found that some types of bottlenecks shares very similar traits. We would also map all the statistics to the call graph of the code's excution to see the distribution of the number of events to every function. And this level of detail would give us the better chance to determine the types of bottleneck in the program.

## Experimental Setup

### Profiling tools

- #### Perf

perf is a standard profiling infrastructure on Linux. It supports a huge number of events that could be recorded for measuring the performance of a machien or a task.

> perf event list:
>
> - task-clock: time spent on the profiled task
>
> - context-switches: storing a state of a process.
>
> - mutex_acquired: number of times threads tried to acquire mutex.
>
> - cache-misses: application makes a request to retrieve data from a cache, but that specific data is not currently in cache memory.
>
> - sched:sched_stat_wait: time spent in waiting states
>
> - etc...

We could use the statistics of some events to determine the type of bottleneck in the provided task.

Perf also has a feature called **annotate** which allows our to observe the statistics mapped to compiled instructions or even source code.

> Perf command:
>
> ``` sudo perf record -e task-clock,page-faults,context-switches,sched:sched_stat_blocked,sched:sched_stat_iowait,sched:sched_stat_runtime,sched:sched_stat_sleep,sched:sched_stat_wait,sched:sched_wait_task,sched:sched_wake_idle_without_ipi,syscalls:sys_enter_futex,writeback:writeback_wait -s ${executable} ${number of threads} && sudo perf report -T --sort=dso > ${report_filename} ```
>
> ``` sudo perf stat -e task-clock,page-faults,context-switches,sched:sched_stat_runtime,sched:sched_wake_idle_without_ipi,syscalls:sys_enter_futex ${executable} ${number of threads} ```

- #### valgrind

- #### gprof

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
