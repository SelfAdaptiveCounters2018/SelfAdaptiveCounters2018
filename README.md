## Self-Adaptive Counters 2018
### Introduction

Network measurement provides important information for many applications and has been a hot topic in recent years. To achieve high speed and memory efficiency in real network measurement, various sketches have been developed and allow counters to be randomly shared  by several or many flows like sketches of CM, CU and C. However, the flow size distribution is also drastically skewed in practical scenarios.We don't have any idea of the priori distribution and it is challenging to achieve memory efficiency for skewed network traffic.

Therefore, to solve this problem, we propose a generic technique, named *self-adaptive counters*, that enables memory efficiency and fast processing speed at the same time. Our key idea is simple: When  a  counter  is  going  to  overflow,  we do not increase it one by one, but increase it with predefined probabilities. We have theoretically and experimentally proved that the incurred inaccuracy is negligible compared to the large value of some few flow sizes and memory saved in counters.

This technique has two versions: Static Sign Bits version and Dynamic Sign Bits version. We split each counter into two parts: sign bits and counting bits. For the static version, we fix the length of sign bits in advance and do not change it during insertions. The dynamic version uses a self-adaptive method and can dynamically adjust the length of sign bits according the value the counter needs to represent. (More details about description of our technique are provided in the related paper below)

To verify the effectiveness and efficiency of our technique,we applied our SAC technique to three typical sketches: CM, CU and C. Extensive experimental results show that the SAC technique reduces the Average Relative Error and Average Absolute Error of sketches by up to five to ten times, using the same amount of memory.

### About the source codes,  dataset and parameters setting
The source code contains the C++ implementation of the CM, CU, C  sketch and our corresponding SAC version, including Dynamic Sign Bits version and Static Sign Bits version.We complete these codes on Windows 10 version 1803 and compile successfully using visual studio 2017.




### Requirements



### How to build



### Related paper
*A Generic Technique for Sketches to Adapt to Different Counting Ranges*(submitted to ICNP 2018)
