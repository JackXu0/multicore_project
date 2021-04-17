# Project Report

## Abstract

Parallel computing is usually taken as a method of acceleration in order to deminish the running time of a program. However, it requires excellent implementation and ideal execution environment to get the desired speedup. There're many factors that could influence the performance of a multi-threaded program and those with negative effect have the potential to be the bottleneck of the entire program. In this project, we use multiple tools to profile a parallel program and analyze the result to determine what could be the potential bottleneck of this specific program.

## Introduction

Parallel computing is a surging topic in science and engineer for faster application processing. Parallel computing breaks a computational problem into multiple pieces and solves each of them on a separate CPU simultaneously. OpenMP is a simple and flexible API for creating paralleled programs. Paralleled blocks typically start with the keyword "#pragma omp". Inside such blocks, programmers can define tasks to parallelize. Creating an OpenMP program can be easy, but the resulting code may not deliver the expected level of performance. Ideally, tasks defined in each OpenMP block will achieve nearly X times speed up with X computation resources (CPUs or cores). However, this is more often not the case. 

Lots of factors can negatively affect the performance of a parallel computing task, such as memory conflicts, synchronization overhead, load unbalancing, and limited shared resources. These problems appear on the code as bottlenecks, which refer to lines or blocks of code that constrain the parallel computing task to scale or speed up. Programmers can eliminate many of these bottlenecks if they know where these bottlenecks are. This project aims to find a way to locate potential bottlenecks in parallel programs and helps programmers improve the code.











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

### Profiling tools:

> - perf
> - valgrind
> - gprof

## Experiments & Analysis

## Conclusions

## References