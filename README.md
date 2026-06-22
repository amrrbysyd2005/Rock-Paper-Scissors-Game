# 🎮 Rock-Paper-Scissors Game (C++)

A professional console-based **Rock-Paper-Scissors** game written in C++. The project is engineered following clean code principles, featuring robust input handling and interactive color-coded feedback to elevate the user experience.

---

## ✨ Technical Features

The game is built using modern C++ best practices and includes:
* **Robust Input Validation:** Complete protection against invalid inputs, floating points, and unexpected characters to prevent infinite buffer loops and ensure stable execution.
* **Structured Data Management (Structs & Enums):** Rounds and tournament statistics are cleanly managed using advanced structs and array tracking, passing data by reference (`&`) to prevent unnecessary memory overhead.
* **Optimized Game Logic (Ternary Operators):** Leverages clean ternary shorthand alongside explicit control flow breaks (`return`) to isolate round outcomes (Win, Loss, Draw) safely without logical bugs.
* **Interactive UI Color Coding:** Integrates native Windows API (`<windows.h>`) to visually highlight round states—Green for victories, Red for defeats, and Yellow for draws—along with a dedicated calming cyan theme for game-over sequences.

---

## 🕹️ How to Play

1. **Set Rounds:** Upon starting, enter the desired number of rounds you want to play (constrained securely between 1 and 10).
2. **Make Your Move:** In each round, choose your hand by typing the corresponding number:
   * **1** for **Stone**
   * **2** for **Paper**
   * **3** for **Scissor**
3. **Instant Feedback:** The system immediately evaluates the AI's random choice against yours, colors the terminal, and prints the round winner.
4. **Final Match Statistics:** Once all rounds conclude, the game calculates overall score leaderboards, tracking player wins, computer wins, and total draw counts.
5. **Replayability:** You can smoothly restart a fresh new tournament or exit cleanly, resetting the console screen buffers dynamically.

---

## 🛠️ Requirements & Setup

* **Operating System:** Windows (Required due to the dependency on `<windows.h>` for console color formatting).
* **Compiler:** Any compiler supporting C++11 or newer (e.g., GCC, MSVC via Visual Studio).
