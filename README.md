# cpp-timer-framework

Small C++ experiments building toward a single-threaded periodic timer scheduler.
Timers fire at fixed periods without busy-waiting: the program sleeps until the next one is due.

## Projects

| Folder | What it does |

| [basicTimer](./basicTimer) | Two timers using a class. Shows how `sleep_for` drifts over time. |
| [threeTimer](./ThreeTimer) | Three timers (200 ms, 500 ms, 1000 ms) in a struct and vector. Picks the soonest due timer and uses `sleep_until`, so there's no drift. |

## Build and run

Each folder is self-contained. From inside a folder:

```
g++ -std=c++17 src/main.cpp -o timers
./timers
```

## What I learned

- `sleep_until` stays anchored to a stored due time. `sleep_for` accumulates drift.
- Each timer stores its next due time. Only the one that fires gets pushed forward.
- Windows timing adds about 10-15 ms of jitter, but it doesn't accumulate.

