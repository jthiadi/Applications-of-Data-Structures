## 📝 Problem Description

Governments periodically announce new tariff policies for different countries. This system is designed to:
- **Announce** a new set of tariffs for the current policy state.
- **Switch** to a previously announced policy using a specific date.
- **Check** the historical tariff rates for a country across all ancestors of the current policy.

## 📥 Input Format

N
<command_1>
<command_2>
...
<command_N>

Each command is one of the following:
- `tariff announce <country_count> <date>`
- `tariff switch <date>`
- `tariff check <country_name> <asc|desc>`

### Example Input:
7
tariff announce 3 2023-01-15
usa 10%
china 15%
japan 12%
tariff check usa asc
tariff announce 2 2023-02-20
usa 8%
canada 11%
tariff check usa desc


## 📤 Output Format

For each command, print the appropriate response:

- `announce`:  
  `New policy announced on <date>`
- `switch`:  
  - If found: `Switched to Policy on <date>`
  - If not: `No policy found on <date>`
- `check`:  
  - If data found:  
    ```
    Tariff history for <country_name>:
    <rate_1>
    <rate_2>
    ...
    ```
  - If not:  
    `No tariff policy for <country_name>`

### Example Output:
New policy announced on 2023-01-15
Tariff history for usa:
10%
New policy announced on 2023-02-20
Tariff history for usa:
8%
10%

## 🧠 Data Structures Used

- **Policy Tree**: Each node represents a tariff snapshot on a specific date.
- **Trie**: Used within each policy node to efficiently store and retrieve tariff rates per country.
