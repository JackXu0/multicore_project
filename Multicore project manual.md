# Manual: Bottlenecks in Parallel Programs

## Environment

Operating system: Ubuntu: 20.04.2

Git repository: https://github.com/JackXu0/multicore_project.git

## Profiling Software Install

##### Install Perf

```bash
sudo apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r`
```

##### Install Strace

```bash
sudo apt-get install strace
```

##### Install Valgrind

```bash
sudo apt-get install valgrind
```

#### Switch on kernel flag for sharing scheduler statistics

```bash
sudo sysctl kernel.sched_schedstats=1
```

## Locate Bottlenecks

```bash
gcc -fopenmp - Wall -std=c99 -pg -o example example.c
```

#### Step 1: Check whether each pragma section speeds up with the increased thread count

This step coarsely locates the bottleneck to paralleled block level. If one paralleled block has bottleneck inside, it can hardly achieve speed up with the increase number of threads.

Added time collection code before and after each pragma section

```c
# add above a pragma section
struct timeval stop, start;
gettimeofday(&start, NULL);

# add below a pragma section
gettimeofday(&stop, NULL);
printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
```

change the thread count to 1,2,4,8, etc.

```bash
export OMP_NUM_THREADS=4
```

check the results to see if each pragma section speeds up with the increased thread count. 

#### Step 2: run profling tools to find out the reason for the bottleneck

Step 1 if not enough, especially when the parallel block is long. In step 2, we run several profiling tools to find out the reason for the bottlenecks and make it easier to locate problems.

##### Strace

###### Running Strace to generate the time distribution of system calls

```bash
sudo strace -c -o example_log ./example
```

Here is an example, the result indicates too much time is wasted on futex for this parallel block. 

<img src="/Users/zhuocheng/Library/Application Support/typora-user-images/image-20210421154757154.png" alt="image-20210421154757154" style="zoom:50%;" />

###### Running Strace to get the time distribution of system calls for each thread

```bash
strace -tt -ff -T -o strace-dump -- ./example
```

This command will store the time distribution of system call in a seperate log for each thread. Then we can explore whether one thread speed too much time running, waiting ,reading, etc. Here is an example to check the total time spent by one thread waiting for mutex to unlock

```bash
grep futex strace-dump.3740 > futex.dump
sed -i 's/.*<//g' futex.dump
sed -i 's/>//g' futex.dump
paste -s -d+ futex.dump | bc
```

##### Perf

We use perf to get all the statistics of events listed in our report. And user could modify the command according to their need.

```bash
sudo perf record -e task-clock,page-faults,context-switches,sched:sched_stat_blocked,sched:sched_stat_iowait,sched:sched_stat_runtime,sched:sched_stat_sleep,sched:sched_stat_wait,sched:sched_wait_task,sched:sched_wake_idle_without_ipi,syscalls:sys_enter_futex,writeback:writeback_wait -s -g ./example ${number of threads} ${task data size} && sudo perf report -T --sort=dso > ${report_filename}

sudo perf stat -e task-clock,page-faults,context-switches,sched:sched_stat_runtime,sched:sched_wake_idle_without_ipi,syscalls:sys_enter_futex -r ${number of iteration} -x ${separator} -o ${output filename} ./example ${number of threads} ${task data size}
```

These two commands would give us the data we need for our analysis. Perf also provides an **annotate** tool that could map the statistics to the source code. To use this tool, first we need to add a flag **-ggdb** that would give us information for debugging. And after running the **record** command, **annotate** would use the generated data file to map to each code lines. But this tool only support a small number of events, such as task-clock. To use this tool simply type in the command

```bash
sudo perf annotate -d example
```

##### Valgrind

We use valgrind to get the information of cache and memory references and misses during the excution of the code. We only use the tool **cachegrind** though valgrind also provides a lot of tools for error detection and memory leaks detection.

```bash
sudo valgrind --tool=cachegrind ./example ${number of threads} ${task data size}
```

By all the data and information we have gathered from the above, with our analysis method presented in the report. We would get the basic idea of the bottlenecks in the given program.
