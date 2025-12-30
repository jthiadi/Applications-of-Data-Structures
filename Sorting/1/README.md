# 🏀 Basketball League Leaderboard (NTHU OJ Problem 14632)

This project solves the [Basketball League Leaderboard](https://acm.cs.nthu.edu.tw/problem/14632/) problem from NTHU Online Judge. It implements a system to track basketball players' performance and generate dynamic rankings based on various criteria.

---

## 📋 Problem Overview

You are required to process a sequence of commands to maintain and display player or team rankings:

- **`Play PlayerName TeamID Points Rebounds Assists Fouls`**  
  Records a new game for a player and updates their cumulative statistics.

- **Ranking Commands**:  
  - `All`: Rank players by overall weighted performance.  
  - `Score`: Rank players by average points.  
  - `Rebound`: Rank players by average rebounds.  
  - `Assist`: Rank players by average assists.  
  - `Foul`: Rank players by lowest average fouls.  
  - `Team`: *(Optional – only in some test cases)* Rank teams by the average performance of their players.

---

## 🧮 Performance Formula

Performance = ((TotalPoints × 0.5)
             + (TotalRebounds × 0.3)
             + (TotalAssists × 0.2)
             - (TotalFouls × 0.2))
             / TotalMatches
All averages and scores should be rounded to two decimal places.

---

## 🧾 Input Format
N
command_1
command_2
...
command_N
Example:

mathematica
Copy
Edit
14
Play Bill 1 15 5 5 2
All
Play Aurick 1 16 6 6 2
All
Score
Rebound
Assist
Foul
Play Charles 2 20 2 1 1
All
Play John 2 25 1 1 1
All
Team

---

## 📤 Output Format
For each ranking command, output up to the top 3 players or teams with their score or average. Break ties by lexicographical order (for players) or lowest TeamID (for teams).

Sample Output:
Bill 9.60
Aurick 10.60
Aurick 16.00
Bill 15.00
...
2 13.25
1 11.27
