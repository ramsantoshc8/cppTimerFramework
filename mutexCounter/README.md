# mutexCounter

Demonstrates a race condition and its fix with std::mutex.

## What it does

Two threads each increment a shared `int counter` 100,000 times. The correct
total is always 200,000.

- **Without a lock:** the final count is unpredictable and usually below
  200,000, because `counter++` is really three steps (read, add, write),
  and the two threads can interleave mid-step, losing increments.
- **With a lock (`std::lock_guard`):** each increment runs as one
  uninterrupted step, so the result is exactly 200,000 every run.

## Build and run

```
g++ -std=c++17 -pthread src/main.cpp -o mutexCounter
./mutexCounter
```

## What I observed

| Run | Lock? | Result |
|---|---|---|
| 1 | No | (varies, below 200000) |
| 2 | Yes | 200000, every time |

(Paste your real numbers here.)

## What I learned

- A race condition isn't about threads running "at the same time" in general
  — it's about two threads reading and writing the *same* data without
  coordination.
- A mutex doesn't make code run in any particular order. It only guarantees
  that one thread finishes touching the shared data before another starts.