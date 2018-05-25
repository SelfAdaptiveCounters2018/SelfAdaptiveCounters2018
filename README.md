## Self-Adaptive Counters 2018
### Introduction

Network measurement provides important information for many applications and has been a hot topic in recent years. To achieve high speed and memory efficiency in real network measurement, various sketches have been developed and allow counters to be randomly shared  by several or many flows. However, the flow size distribution is also drastically skewed in practical scenarios.We don't have any idea of the priori distribution and it is challenging to achieve memory efficiency for skewed network traffic.

Therefore, to solve this problem, we propose a generic technique, named *self-adaptive counters*, that enables memory efficiency and fast processing speed at the same time. Our key idea is simple: When  a  counter  is  going  to  overflow,  we do not increase it one by one, but increase it with predefined probabilities. We have theoretically and experimentally proved that the incurred inaccuracy is negligible compared to the large value of some few flow sizes and memory saved in counters.

This technique has two versions: Static Sign Bits version and Dynamic Sign Bits version. 

### About this repo
This repo contains all the algorithms used in our experiments, as shown in the following table.

|   Task   |  Algorithms    |
| ---- | ---------- |
|      |      |
|      |      |
|      |      |

### Requirements



### How to build



### Related paper
*A Generic Technique for Sketches to Adapt to Different Counting Ranges*
