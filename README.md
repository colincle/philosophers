# philosophers

A solution to the classic dining-philosophers problem, written in C with POSIX
threads. Philosophers sit around a table alternating between eating, sleeping,
and thinking. Each needs the two forks next to it to eat, and the simulation has
to run without deadlocks and without any philosopher starving. Built as the 42
"philosophers" project.

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

Example:

```sh
./philo 5 800 200 200
```

Each event is logged with a timestamp, for example
`0 1 has taken a fork`, `0 1 is eating`, and `X 3 died`.
