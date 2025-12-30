# Applications of Data Structures

This repository contains simple C++ implementations that demonstrate how **fundamental data structures** can be applied to solve real-world and algorithmic problems.

The goal of this project is to:
- Strengthen understanding of **data structure concepts**
- Show how they are used in **practical applications**
- Provide **clear, readable example programs**

---
### 🔹 1️⃣ Graphs
This folder contains two C++ programs that use **graphs** to model transportation networks and find routes.

## 1. `1.cpp` — City Route with Price & Time

- Represents cities as **nodes** and roads as **edges** with:
  - `price` (cost of traveling)
  - `time` (travel time)
- Builds an adjacency list of edges.
- Uses a graph search (with a queue of states) to find a valid route from a start city to a target city while tracking:
  - total price
  - total time
- Reconstructs the chosen path using a `parent` array and prints it as:
```bash
CityA->CityB->CityC
```
## 2. `2.cpp` — Metro / Station Network

- Represents a metro system as a **graph**:
- **Nodes**: stations
- **Edges**: rides between adjacent stations, each with:
  - travel `time`
  - a `line` identifier
- Maps station names and line names to numeric IDs for graph storage.
- For multiple starting stations (friends), computes travel costs over the network:
- runs shortest-path–style DP / BFS over states `(station, line)`
- considers ride times and line changes
- Chooses a meeting station that minimizes the **total travel cost** for all friends and prints each friend’s route as a sequence of stations:
```bash
A->B->C->D
```
---

### 🔹 2️⃣ Linked List
This folder contains two C++ programs that manage **music playlists** using sequential data structures, with a focus on **linked lists** in `1.cpp`.

## 1. `1.cpp` — Linked-List Based Playlist(s)

`1.cpp` implements multiple music playlists using a **singly linked list**:

- Each **node** (`song`) stores:
  - `name` (song title)
  - `next_song` (pointer to the next node)
- A `playlist` class maintains:
  - `first_song` (head of the list)
  - `last_song` (tail of the list)

### Supported Operations

- **Add song to a playlist (`ADD ls`)**  
  Takes the current text buffer as the song name and appends it to playlist `ls`.

- **Print playlist (`SAVE ls`)**  
  Outputs all songs in playlist `ls` in order, or reports if it’s empty.

- **Move cursor in text buffer (`CURSOR i L/R`)**  
  Moves a cursor left or right inside a temporary string buffer used to build song names character by character.

- **Move a song within a playlist (`MOVE ls p i L/R`)**  
  Removes the song at position `p` and re-inserts it `i` positions to the left or right inside playlist `ls`.

- **Reverse in groups (`REVERSE ls k`)**  
  Reverses the playlist `ls` in blocks of size `k` using pointer manipulation on the linked list.

- **Typing characters**  
  Any input that is not a recognized command is treated as a **typed character**, inserted into the buffer at the cursor position.

This file showcases typical **linked list operations**: insert at position, remove at position, moving nodes, and segment-wise reversal.

---

## 2. `2.cpp` — Circular Play Queue (Vector Version)

`2.cpp` implements a similar **playlist / play queue**, but using a `vector<Song>` instead of a linked list:

- Each `Song` stores:
  - `name`
  - `duration` (seconds)
- All songs are stored in a dynamic array (`vector`), representing the current play order.

### Supported Commands

- **ADD_SONG N d i**  
  Insert song `N` with duration `d` at index `i` (0-based).  
  If `i` is out of range, the song is appended.

- **DELETE_SONG N**  
  Remove the song named `N` if it exists, otherwise print:
  `Song not found`

- **SKIP S**  
  Rotate the playlist by `S` positions (circularly), effectively skipping ahead in the queue.

- **REVERSE**  
  Reverse the entire order of songs in the playlist.

- **PLAY t**  
  Simulate playing for `t` seconds on a loop:
  - Sums up total cycle duration.
  - Determines which song is playing at time `t`.
  - Prints:  
    `Currently playing: <song_name>`

- **DISPLAY**  
  Prints the playlist contents and the total duration in seconds.

This file contrasts the linked-list implementation by solving a similar playlist problem using a **dynamic array**, highlighting different trade-offs in data structure choice.

### 🔹 3️⃣ Sorting
This folder contains C++ programs that use **sorting algorithms and custom comparison rules** to rank players and sports teams based on performance statistics.

## 🏀 `1.cpp` — Player & Team Performance Ranking

This program tracks **basketball player statistics**, updates their records after each game, and supports
ranking queries for either **players** or **teams**.

### 📌 Data Tracked per Player
- Total & average **points**
- Total & average **rebounds**
- Total & average **assists**
- Total & average **fouls**
- Number of games played  
- Team ID

### ⭐ Overall Player Score
Each player also has a **weighted performance score**:
```bash
overall = (0.5 * points + 0.3 * rebounds + 0.2 * assists − 0.2 * fouls) / games
```

### 📌 Data Tracked per Team
- Team ID
- All members
- Team **average performance** (mean of member overall scores)

### 🧠 Commands Supported
The program reads a series of commands such as:

#### **Game Record**
```bash
Play <PlayerName> <TeamID> <Points> <Rebounds> <Assists> <Fouls>
```

Updates the player’s stats (creates the player or team if new).

#### **Ranking Queries**
Rank **players**:
```bash
All
Score
Rebound
Assist
Foul
```

Rank **teams**:
```bash
Team
```

---

### 📊 Output
For each ranking request, the program:

✔ sorts using a **custom quick-sort implementation**  
✔ applies tie-breaking (averages → name / team ID)  
✔ prints the **top 3** results with 2-decimal precision

Examples:
Tom 9.60
Timmy 10.60
2 13.25
1 11.27

This file demonstrates **custom sorting with complex metrics + pointer-based data management**.

---

## 🏆 `2.cpp` + `14643.h/.cpp` — League Standings Sorting

These files implement a **sports league ranking system** where teams are sorted based on record and detailed tie-breaking rules.

### 📌 Each Team Stores
- Team name
- Division
- Wins & losses
- Division wins & losses
- Point-differential
- Internal team ID

## 🧮 Ranking Rules

Teams are ordered by:

1️⃣ **Higher win rate**  
2️⃣ **Higher point differential**  
3️⃣ **Higher division win rate**  
4️⃣ **Alphabetical name**

## 👑 Retro Mode — Division Leaders First

If `retro = true`, then:

✔ Current **division leaders are ranked ahead of non-leaders**  
✔ Remaining rules still apply inside each group

Division leaders are determined **from current results at sort time**.

## ⚙️ Sorting Method
Sorting is done using:

✔ a **custom comparator**  
✔ applied through `std::sort` (conceptually merge-sort-style ordering)  
✔ clear rule-based ordering logic

## 🖥 Program Flow
1. Read team names & divisions  
2. Read game results and update stats  
3. Determine division leaders (if retro mode)  
4. Sort teams using the comparator  
5. Output ranked standings, e.g.:
```bash
Lakers 10-2
Suns 9-3
Kings 8-4
```

## 🎯 Key Concepts Practiced
- Custom **comparison functions**
- Sorting with **multi-level tie-breaking**
- Aggregating statistics
- Using **structures, vectors, and maps**
- Designing ranking logic from real-world rules

This folder highlights how **different sorting strategies** can solve real problems such as ranking players and league teams.

---

### 🔹 4️⃣ Stack & Queue
This program simulates multiple **registration queues** where families line up to enter a place.  
Each queue is implemented using a **FIFO queue data structure**, and the program processes
arrivals, registrations, special-case handling, and people who quit the line.

## 🧮 Input Overview

The program reads:
```bash
F X Y M
```
Where:
| `F` | Number of registration places (queues) |
| `X` | Maximum queue length threshold used when removing families who waited too long |
| `Y` | Threshold used to determine **special families** (fee waived) |
| `M` | Total simulation time (in minutes) |

Then for **each minute (0 → M)** and for **each place**, the input line contains 0 or more arriving families written as:
```bash
A,P
```
where  
`A = number of people in the family`  
`P = fee they should pay`

## 🔁 What Happens Each Minute
For every queue, in every minute:

### ✅ 1. Registration (front of queue)
- A counter tracks how many registration checks occurred
- **Every second registration call**, the **front family enters**
- When a family enters:
  - Their fee is added to total money (unless special = free)
  - Their people count is added to total-entered
  - They are removed from the queue and recorded in history

### ⭐ 2. Special Family Rule
When a new family joins the line:
They become **special** (their fee becomes 0) **if**:
- there exists a **contiguous block of families at the end of the queue, including them**
- whose **total fees = `Y`**
- and **none of those families were already special**

This family enters for **free**.

### ⏳ 3. People Who Quit the Queue
A family **at the back of the queue** will quit if:
- they have waited **60 minutes or more**, **and**
- they are **not** a special family, **and**
- the queue currently has **more than `X` families**

Families with **100+ people never quit**.

Multiple families can quit in one minute (processed from the back).

Their people count is added to **Total People Quit**.

### 🧍 4. New Arrivals
Any families listed in that minute’s input are appended to the queue.

## 📊 Output Summary

After all `M` minutes, the program prints for each place:
```bash
Place <index> Summary
Total Money: <amount>
Total People Entered: <count>
Total People Quit: <count>
Current People Queuing: <count>

Entered Families :
Family <id> with <people>
...
```
(Entered families are listed **in reverse order of entry**.)

## 🧠 Data Structures Used
- **Queue of families** — models real-world waiting lines
- Arrays track:
  - entered family IDs
  - number of people
- Logic demonstrates:
  - queue operations (enqueue / dequeue)
  - time-based removal
  - conditional fee waiving
  - simulation flow

## 🎯 Key Concepts Practiced
✔ Queue data structure  
✔ Event-driven simulation  
✔ State tracking & statistics  
✔ Conditional processing logic  

This program is a realistic example of how **queues** are used to manage real-world waiting-line systems.

---

### 🔹 5️⃣ Trees
## 📝 `1.cpp` (Git Version Control Simulation)

### 📚 Description
This program simulates a simplified **Git-like version control system** using:

- **Trie** — stores filenames and maps them to file-change objects  
- **General Tree (`GitNode`)** — stores commit history as a parent-linked structure  

It supports committing changes, switching commit states, and reconstructing file contents from history.

### ⭐ Key Features
#### 🗂 Commit Storage
- Filenames stored in a Trie  
- Each file maps to a list of insert/delete operations  

#### 🕓 History Tracking
- Each commit node points to its parent  
- Enables backward traversal through commit history  

#### 📄 File Reconstruction
- `open <filename>` walks from root → current commit  
- Applies all line modifications to rebuild the file  

### 📟 Commands
| Command | Description |
|--------|-------------|
| `commit <total_files>` | Record insertions/deletions for multiple files |
| `switch <commit_index>` | Change current state to a previous commit |
| `open <filename>` | Output reconstructed file content |

---

## 🌏 `2.cpp` (Tariff & Trade Policy System)
### 📚 Description
This program manages government tariff announcements and allows historical policy lookup using:
- Policy Tree — tracks policy updates over time
- Trie (per-policy node) — efficiently stores country names & tariff rates
- Lookup is O(L) where L = length of country name

### ⭐ Key Features
#### 🔎 Policy Lookup
Fast search for tariff rates by country.

#### ⏳ Time-Travel Policies
tariff switch jumps to past policy states.

#### 📜 Policy History Checks
tariff check traces historical rates for a country.

### 📟 Commands
| Command | Description |
| `tariff announce <count> <date>` |	Add a new tariff dataset for multiple countries
| `tariff switch <date>` |	Activate policy snapshot from a historical date
| `tariff check <country> <asc|desc>` |	Display tariff history for a country

---
## ⚙️ Requirements

- C++ compiler (e.g., `g++`, `clang++`)
- Standard Library support (C++11 or later recommended)

---

