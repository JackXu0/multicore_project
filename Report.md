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

### Profiling tools:

> - perf
> - valgrind
> - gprof

## Experiments & Analysis

## Conclusions

## References
