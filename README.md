# GreenChain: Eco-Currency System 🌱

A lightweight command-line interface (CLI) application written in C that simulates an eco-friendly rewards platform. Users can register accounts, log in, "recycle" different materials (glass, plastic, aluminum) for virtual credits, and compete against others on a community leaderboard. 

This project was built to demonstrate core computer science fundamentals, including dynamic memory allocation, data structures, and persistent storage.

## 🚀 Features

* **User Authentication & Persistence:** Registration and login functionality. User data (balances, total recycled weight) is saved persistently to disk using basic File I/O (`users.txt`).
* **Recycling Engine:** Calculates credits dynamically based on the material type and weight provided by the user.
* **Session History:** Tracks the user's actions and transactions during the current session using a dynamic Linked List.
* **Community Leaderboard:** Ranks all registered users based on their total kilograms recycled, implemented via a Bubble Sort algorithm.

## 🛠️ Tech Stack & Concepts Demonstrated

* **Language:** C
* **Core Concepts:** Pointers, Structs, Dynamic Memory Allocation (`malloc`), Linked Lists, Standard I/O, and Sorting Algorithms.

## 💻 How to Run

1. Clone the repository to your local machine.
2. Compile the C source file using GCC (or your preferred C compiler):
   ```bash
   gcc greenchainupdated.c -o greenchain
