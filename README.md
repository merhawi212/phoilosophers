# About Project
Philosophers, often refer to a classic synchronization problem known as the "Dining Philosophers Problem.". This solves the complexities of resource allocation and concurrency control in multi-threaded.

In the problem, a group of philosophers sits around a dining table, and they alternate between three actions: thinking, eating and sleeping. Each philosopher needs two forks to eat, one for each hand, and the forks are considered shared resources. Every philo have time to eat, sleep and died. 



Key Concepts:

Concurrency: Philosophers represent concurrent entities, often implemented as threads, that need to access shared resources (forks) while avoiding conflicts and data races.

Mutex: Mutexes are used to protect shared resources, like forks, ensuring that only one philosopher can access a resource at a time. This prevents data races and maintains synchronization.

Deadlock Prevention: A central challenge in the Dining Philosophers Problem is preventing deadlock, where philosophers are stuck in a state where they can't make progress. Proper resource allocation and synchronization mechanisms, often involving mutexes, are crucial for deadlock prevention.

Greedy Philosopher Prevention: To prevent selfish behavior where a philosopher attempts to monopolize forks and starve others, each philosopher maintains a unique identifier as their state. This identifier ensures that a philosopher refrains from accessing a fork if its value matches their identifier. It's essential to update this identifier when a philosopher puts down a fork, marking it as "ate." This approach is on top of the deadlock prevention, promotes fair resource sharing and discourages self-serving behavior among philosophers.



##USAGE

``
```
cd philo && make

```

` ./philo 5 800 200 200 `


