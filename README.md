# Programming Fundamentals 2 (C++) – COP3503C

This repository contains my work from **Programming Fundamentals 2 (C++)** at the University of Florida. It includes all labs (2–5) and projects (1–3) completed during Spring 2025 under instructor **Tima Tavassoli**.

---

## 📝 Labs

### Lab 2
- **Part 1:** 🚗 Implementing a Vehicle class with required attributes and functions (make, model, year, price, mileage)  
- **Part 2:** 🏢 Implementing a Showroom class that manages a collection of Vehicle objects with a vector, supports adding/displaying/inventory valuation, and capacity checks  
- **Part 3:** 🚙 Building a Dealership class to manage multiple showrooms and vehicles, supporting average price calculation and overall inventory display  
*Focus: Object-oriented class design in C++, use of vectors, constructors/destructors, dynamic memory*

### Lab 3
- 📇 Building a Contact and ContactBook system using pointers, static arrays, and operator overloading  
  - Contact class stores name and number, with required methods (constructor, getName, getNumber, display)  
  - ContactBook class uses an array of Contact pointers, supports add/remove/find/alphabetize/display, copy constructors, assignment operator, equality/not-equality, operators for combining books and contacts  
*Focus: Deep dive into pointers, references, operator overloading, static vs dynamic storage*

### Lab 4
- 🥞 **Array-Based Stack (ABS)** and 🏰 **Array-Based Queue (ABQ)** template classes supporting push/pop and enqueue/dequeue operations with dynamic resizing and exception handling  
  - Implement The Big Three: Copy Constructor, Assignment Operator, Destructor  
  - Use a scale factor for resizing arrays to optimize performance  
  - Throw runtime_error exceptions for incorrect use  
*Focus: Templates, dynamic memory, container design, exception handling*

### Lab 5
- 🛸 Binary File I/O: Read binary files describing starship data and weapons  
  - Load starship records (name, class, length, shield, warp speed, weapons) from binary files  
  - Output all ships, the ship with the most powerful weapon, most/least powerful ships, and unarmed ships  
  - Emphasis on handling binary string formats and dynamic data  
*Focus: Binary data reading/parsing, dynamic memory, structured output, file format specification*

---

## 🚀 Projects

### 🔗 Project 1 – Linked Lists
- Implement a **Linked List class** in C++ with all standard list behaviors  
- Must include construction, destruction, copy constructor, assignment operator, accessors, insertions, removals, and operators  
- Support printing forward/reverse (recursive/iterative), node counting, searching (FindAll, Find), indexed access, and exception handling  
- **Special focus:** Complete implementation of dynamic memory management ("Big Three"), recursive printing, and robust API  
[attached_file:7]

### 🖼️ Project 2 – Image Processing (TGA Manipulation)
- Command-line program for binary **TGA image file manipulation**  
- Two milestones:  
  - **Milestone 1:** Implement algorithms for pixel-wise image blending, channel adjustment, splitting/composing images, flipping, clamping, and rounding  
  - **Milestone 2:** Build a user-friendly CLI supporting multiple operations, chaining, and robust error/help messaging  
- **Special focus:** File format mastery, algorithmic pixel manipulation, Makefile/automation, robust error handling  
[attached_file:5]

### 💣 Project 3 – Minesweeper Game (SFML GUI)
- Complete GUI-based **Minesweeper game** using C++ and SFML  
- Three windows: Welcome (name input/validation), Game (full Minesweeper logic, tile reveal/flagging, restart, pause/debug, timer, leaderboard access), Leaderboard (top scores display, leaderboard saving)  
- Features include dynamic board sizing/configuration, mine/flag counter (can go negative), timer, strict input validation, mouse-driven controls, file IO for saved scores  
- Multiple development milestones, Makefile build, required README with full project metadata  
- **Special focus:** Object-oriented design, asset management, event-driven programming, graphical interface with robust state handling  
[attached_file:6]

---

## 🧠 Topics Covered

- **Object-Oriented Programming:** Classes, constructors/destructors, copy constructors, assignment operators, encapsulation  
- **Dynamic Memory & Pointers:** Deep copy vs shallow copy, operator overloading, arrays vs vectors, memory management  
- **Templates:** Array-based Stack and Queue implementation, generic programming, resizing strategies  
- **Data Structures:** Linked lists, dynamic arrays, stacks, queues  
- **File I/O:** Binary file reading, parsing structured binary data, handling errors in input/output  
- **Algorithms & Logic:** Searching, sorting, recursive functions, exception handling  
- **GUI Programming (SFML):** Event-driven design, mouse/keyboard input handling, timers, dynamic rendering, state management  
- **Image Processing:** Pixel manipulation, TGA file format, binary-to-decimal conversions, RLE encoding/decoding, CLI tools  
- **Game Development:** Blackjack (console), Minesweeper (GUI), board management, game rules, statistics tracking  
- **Debugging & Error Handling:** Exception throwing/catching, validation checks, robust user input handling, edge case considerations  

---

*Completed as part of COP3503C at the University of Florida, Spring 2025.*
