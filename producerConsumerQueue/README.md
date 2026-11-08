# producerConsumerQueue

A producer thread and a consumer thread communicating through a shared
queue, using a mutex and a condition variable. No busy-waiting.

## What it does

- **Producer:** pushes numbers 1 to 10 onto a shared queue, one every
  100ms, then sets a `completed` flag.
- **Consumer:** sleeps (via `std::condition_variable::wait`) until the
  queue has something or `completed` is set. Wakes, pops, prints,
  and goes back to sleep.
- The consumer never polls — it's woken only when there's real work,
  which is the same pattern a real event loop uses to wait on a timer
  or an incoming message.

## Build and run

```
g++ -std=c++17 -pthread src/main.cpp -o producerConsumer
./producerConsumer
```

## Expected output

```
Given number: 1
Given number: 2
...
Given number: 10
```
One line roughly every 100ms, then the program exits on its own.

## What I learned

- A condition variable always needs a paired mutex: `wait` releases the
  lock while sleeping and re-acquires it on wake, so the producer can
  safely touch the queue while the consumer sleeps.
- The exit check has to be made right after waking, while still holding
  the lock — checking a "finished" flag in the loop condition instead can
  read a stale value and either hang or skip the last items.
- This is a smaller version of the same problem Part D's `ipc_wait`
  solves: one thread waiting on either new data or a timeout, without
  spinning.