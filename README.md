# CSCI2270-Final-Project
--------------------------------------Dungeon Crawler Item Management--------------------------------------

# Project Introduction
For my personal project for **CSCI2270: Data Structures C++**, I built a dungeon crawler inspired item management system.

This project combines multiple data structures and algorithms:
- **Hash Table (Separate chaining / Linked Lists)** to map a character name → the character’s inventory
- **Priority Queue (Heap)** to store each character’s items and efficiently retrieve the strongest from their inventory
- **Graph** to represent a dungeon room as vertices and enemy encounters as edges 
- **Dijkstra’s Algorithm** to compute the easiest route from start → end, where edge weights come from an enemy’s strongest item damage

The main program is a terminal based application that allows users to interact with the system through a menu of numbered options where you can load items from a file, manage character inventories, and compute the easiest dungeon route.

  **======Main Menu======**
  **1. Build data structure**
  **2. Add new item**
  **3. Peek most powerful item**
  **4. Exit**

# Features
* Load character inventories from a file
* Add new items to a character’s inventory
* Peek the most powerful item (max damage)
* Remove the most powerful item
* Print all items belonging to a character from their inventory
* Display hash table structure and collision count
* Load a dungeon graph from file
* Compute the easiest route using Dijkstra’s

# Want to Play?
Follow these steps to set up and run the project on your own.

## Prerequisites
- C++11 compatible compiler (g++)
- CMake (recommended)
- Make

# Installation
1. Clone the repo:
  ```bash
  git clone https://github.com/<your-username>/<your-repo-name>.git
  ```
2. Navigate into the Project Directory:
  ```bash
  cd <your-repo-name>
  ```
3. Create a Build Directory, Generate Build Files, Compile:
  ```bash
  cd build
  cmake ..
  make
  ```

# How to Run
From inside the 'build/' directory:

```bash
./crawl ../test.txt 10
```

## Arguments
- `../test.txt` → Items input file  
- `10` → Hash table size
