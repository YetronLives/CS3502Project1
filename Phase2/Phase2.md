# Phase 2:

## [Phase 2 Video - CLICK HERE](https://youtu.be/-gjJkITG4bc)

## Objective
Implement Mutexes to control access to bank accounts, preventing multiple threads from accessing the same account simultaneously.

## Challenges and Solutions

#### Challenge 1:
Doing this in Python initially was better because I struggled to implement the lock on the right function as I was overthinking it and tried to make a function housing both deposit and withdrawal

#### Solution:
It worked out fine and I understood that I needed to integrate the lock call in my class and then class it within each method


## Outcomes:
- I realized that this time, instead of all the threads trying to run simultaneously, the lock we used ensured that each thread's task is completed before the following task is executed which made sense for real life scenarios such as makinh sure enough money is deposited before a withdrawal to avoid an overdraft

- More organized output

- I was able to learn about how the mutex worked in both Python and C and how the are called differently