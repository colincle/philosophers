# philosophers

A solution to the classic dining-philosophers problem, written in C with POSIX
threads. Philosophers sit around a table alternating between eating, sleeping,
and thinking. Each needs the two forks next to it to eat, and the simulation has
to run without deadlocks and without any philosopher starving. Built as the 42
"philosophers" project.

## Requirements

A C compiler, `make`, and a POSIX threads implementation. Builds and runs on both
macOS and Linux.

## How it works

- Each philosopher runs in its own thread.
- Each fork is a mutex, so two neighbours can never hold the same fork at once.
- Forks are always taken in a consistent order, which avoids the circular wait
  that would otherwise deadlock the table.
- A separate monitor thread (the "reaper") watches every philosopher and stops
  the whole simulation the moment one goes too long without eating, or once all
  of them have eaten enough.
- Shared state (each philosopher's last-meal time and the alive flag) is guarded
  by mutexes so the monitor and the philosopher threads never race on it.

## Build

```sh
cd philo
make
```

Produces the `philo` binary.

## Run

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]
```

- `number_of_philosophers` — how many philosophers (and forks).
- `time_to_die` — milliseconds a philosopher can go without eating before dying.
- `time_to_eat` — milliseconds it takes to eat.
- `time_to_sleep` — milliseconds spent sleeping.
- `meals` — optional. If given, the simulation stops once every philosopher has
  eaten this many times.

Each event is logged as the timestamp in milliseconds followed by the
philosopher and the action, for example `0 Philosopher 1 has taken a fork`,
`0 Philosopher 1 is eating`, and `804 Philosopher 1 has died`.

## Examples

Each of these outcomes is dictated by the rules, not by luck, so a correct build
always behaves as described. If a run does something else, that is a bug.

- `./philo 1 800 200 200`
  One philosopher, one fork. Eating requires two forks, so it can never eat and
  starves. Expected: it takes its single fork, then dies at about 800 ms, having
  never eaten.

- `./philo 4 100 200 100`
  `time_to_die` (100) is smaller than `time_to_eat` (200), so no philosopher can
  possibly finish a meal before its clock runs out. Expected: a philosopher dies
  at about 100 ms.

- `./philo 5 800 200 200`
  `time_to_die` (800) leaves plenty of slack over one eat-and-sleep cycle (400),
  so every philosopher can always get to the forks in time. Expected: no one ever
  dies, and the simulation runs until you stop it.

- `./philo 5 800 200 200 7`
  Same timing, but capped at seven meals each. Expected: no death, and the
  simulation ends on its own once all five have eaten seven times.
