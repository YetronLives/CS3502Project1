# Phase 3:

## [Phase 3 Video - CLICK HERE](https://youtu.be/YcdDh0NHxME)

## Objective
Simulate deadlock by having transactions lock one account and wait for access to another

## Challenges and Solutions

#### Challenge 1:
I did a good amount of updating of my code on this phase. I believe I did a good job relying less on my Python code but I run to a lot of stumbling blocks as C has a more sophisticated way of passing arguments to functions

#### Solution:
I decieded to learn the long way later and decided to focus on the simulation of the transfer from one account to the other and made 2 separate functions that would do so

#### Challenge 2:
Before I begun this Phase, it had been a few days since I started and I lost track and access to my VM for some reason and could not event get it to open

#### Solution:
I deleted the Ubuntu instance and created another one, making sure to allocate the right amount of space and processors needed.


## Outcomes:
- I had called two different methods and what had happened was because I called the lock on each account after the first transaction. This is because the lock prevented another thread from accessing the function. The only way to resolve this was to unlock after the thread stopped running which we covered in Phase 4