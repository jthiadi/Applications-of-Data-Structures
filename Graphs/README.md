# 🛤 Metro Meet‑Up (NTHUOJ 14639)

Find the optimal station for a group of friends to meet with minimum total metro travel time, considering ride durations and line‑transfer penalties.

---

## 📖 Problem Description

Didier and friends start at different metro stations in Taipei. They want to meet at a single station so the sum of their travel times (rides + transfers) is minimized.  
The metro network is a graph:

- **Nodes**: stations  
- **Edges**: direct rides between adjacent stations on the same line  
  - Each edge has a ride time (minutes) and a line name (e.g. Red, Blue)  
- Transferring from one line to another at a station incurs a fixed penalty **P**, though the initial boarding line does _not_ incur a penalty 

Your goal:

1. Determine the optimal meeting station.  
2. Output the minimum total travel time and each friend’s path.

Tie-breaking: If multiple stations yield the same total time, compare individual travel times in input order to break ties 

---

## 📥 Input Format

m f P
from to time lineName
... (m connections)
friend_1_starting_station
...
friend_f_starting_station

- `m`: number of edges (1–88)  
- `f`: number of friends (2–5)  
- `P`: transfer penalty (1–20)
- Edges are bidirectional between `from` and `to`
- Then `f` lines, each with a friend's start station

---

## 📤 Output Format

<minimal-total-time> <meeting-station> <route-1> ... <route-f> ```
minimal-total-time: total minutes sum for all friends (rides + penalties)

meeting-station: chosen station

Routes are sequences of stations separated by "->" (no spaces)

