# steady-beat-timers

Two periodic timers, a fast "sensor" (500 ms) and a slow "status" (5000 ms), run from one thread.
The program sleeps until the next timer is due instead of busy-waiting.

## How it works

- `Timer` is a class that stores its period (`sleepTime`) and the next time it's due (`nextDue`).
- Each loop, `main` compares the two `nextDue` times to see which timer is due first.
- It calls `sleep_until` on that time, then reports the timer that fired.
- Only the timer that fired has its `nextDue` pushed forward by its period.
- Because `sleep_until` is anchored to a stored time, lateness doesn't accumulate.

## Build and run

```
g++ -std=c++17 src/main.cpp -o steady-beat
./steady-beat
```

## Example output

```
nextDue (sensor): 500 -- nextDue (status): 5000 ---- sensor (WIN) completed 500ms
time elapsed: 500.9
...
 ---- status (WIN) completed 5000ms
time elapsed: 5001.2
```

(Paste your real output here.)

## Notes

- `customSleep()` is the earlier version that uses `sleep_for`. It's left in but commented out in `main`. Each loop adds its own overhead, so it drifts.
- Windows timer granularity adds roughly 10-15 ms of jitter per wake-up, but it doesn't build up.
- Limitation: it's hard-coded for exactly two timers. See [threeTimer](../ThreeTimer) for the generalised version which accompany any number of timers.