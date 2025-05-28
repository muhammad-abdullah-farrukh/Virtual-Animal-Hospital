# Virtual-Animal-Hospital
## Overview
A C++ console-based simulation game implementing object-oriented programming principles to manage a virtual animal hospital. Players treat procedurally generated animals, earn coins, and manage limited resources while handling concurrent events.

## Key Features
- **Inheritance Hierarchy**
  - Base `Animal` class with derived `Cat`, `Dog`, `Bird` implementations
  - Species-specific attributes:
    ```cpp
    class Cat : public Animal {
      int claws_status;
      bool neuter_status;
      int coat_status;
      // Species-specific methods...
    };
    ```
  
- **Polymorphic Behavior**
  - Virtual methods for feeding/grooming:
  ```cpp
  void feed() override {
    health += 12; 
    cout << "Cat fed. Health +12" << endl;
  }

-**Resource Economy**
Coin system for treatment actions
Dynamic pricing for grooming points

-**Persistence System**
Dual-file save/load architecture:
TobeTreated.txt → Animals needing care
Treated.txt     → Cured animals

-**Concurrent Events**
Background threads for:
Animal spawning (every 15s)
Adoptions (every 20s)

## How to Run
-**Compilation (Requires C++17):**
g++ -std=c++17 Project.cpp -o AnimalHospital -pthread

-**Execution:**
./AnimalHospital

-**Game Controls:**
1. Feed Animal      : Health++
2. Groom Animal     : GroomingPts++
3. Treat Animal     : Requires 50+ grooming points
4. Buy Points       : 2 coins → 1 grooming point
5. Save State       : Persists to .txt files

-**Dependencies**
C++ Standard Library
POSIX Threads (pthread)

## Project Structure
AnimalHospital/
├── src/
│   ├── Animal.h         # Base class
│   ├── Cat.h            # Derived class
│   ├── Dog.h            # Derived class
│   ├── Bird.h           # Derived class
│   └── AnimalHospital.h # Game engine
├── data/                # Save files
└── README.md

