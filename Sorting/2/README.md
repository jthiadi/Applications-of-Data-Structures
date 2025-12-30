## 📖 Problem Overview

Simulate an NBA-style seeding system for Western Conference teams:

- Process teams with their name and division.
- Record game results (scores) to update teams':
  - Win-loss record
  - Cumulative point differential
  - Division-specific win percentage  
- Finally, rank teams based on NBA-style rules:
  1. **Win percentage**
  2. **Point differential** (higher is better)
  3. **Division win percentage**
- apply **Retro Rules** (pre-2006): each division leader automatically secures a top-3 seed even if their win percentage is lower

---

## 📝 Input Format
N G
<teamName> <division> # repeated N times
<teamA> <teamB> <scoreA> <scoreB> # repeated G times
<retroFlag>

- `N`: number of teams
- `G`: number of games
- `division`: Northwest, Pacific, or Southwest
- `retroFlag`: `true` or `false` (apply retro-rules)

---

## 📤 Output Format

After processing:
<TeamName> wins-losses

<TeamName> wins-losses
...
N. <TeamName> wins-losses

---

## 🛠️ Solution Overview

1. Read and store team info (name, division).
2. Track for each team:
   - Wins & Losses
   - Point differential (`points_for - points_against`)
   - Division-specific wins/losses
3. Process each game:
   - Update wins/losses
   - Update cumulative point differential
   - Update division stats if both teams share the same division
4. After processing all games:
   - Calculate overall and division-winning percentages
   - Sort using:
     1. Win percentage
     2. Point differential
     3. Division win percentage
   - If `retroFlag = true`, ensure each division’s top team is among the top 3 seeds before final sort.
5. Print the ordered list and records.

