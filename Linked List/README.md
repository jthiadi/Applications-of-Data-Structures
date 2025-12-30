
## 🚀 Problem Overview 2

Develop a **circular (rotating) play queue** that supports dynamic insertion, deletion, skipping, reversing, and simulated playback operations.  
At start, the queue is empty and evolves through a series of commands.

### Supported Commands

- **ADD_SONG N d i**  
  Insert a song named `N` (string) with duration `d` (seconds) at index `i` (0-based).  
  If `i` is greater than current list size, append to end.

- **DELETE_SONG N**  
  Remove the song named `N` from the list.  
  If not found, print:  
Song not found

- **SKIP S**  
Move the first `S` songs from the front to the end of the queue.

- **REVERSE**  
Reverse the current order of songs.

- **PLAY t**  
(Not detailed in sample; likely to simulate playback for `t` seconds—see problem)

Each command may require printing a specific output (see *Output Specification* below) and always ends with a newline.

## 📥 Input Format

A sequence of commands, one per line.  
- `ADD_SONG` commands are formatted as:  
ADD_SONG N d i

- Other commands follow their respective formats (`DELETE_SONG N`, `SKIP S`, `REVERSE`, `PLAY t`).
- There is **no fixed count** of commands; process until EOF.

## 📤 Output Format

For each command that produces output:

- **DELETE_SONG**:  
- If song exists—no output unless stated otherwise.  
- If missing:  
  ```
  Song not found
  ```

- **PLAY t**:  
Simulate playing songs in order until `t` seconds elapse, wrapping around the circular queue repeatedly until time runs out.  
Print the names of all songs that have been *started* (not necessarily finished) during this period, each on its own line and in the sequence they are played.

## 💡 Sample Usage

**Input**:
ADD_SONG hello 5 0
ADD_SONG world 7 1
SKIP 1
REVERSE
PLAY 20
DELETE_SONG foo