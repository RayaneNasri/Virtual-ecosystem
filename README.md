# Virtual Ecosystem

This is a mini C programming project proposed during the second year of the Bachelor's program at **Sorbonne University**. The goal is to implement functions for manipulating linked lists and use them to develop a simple ecosystem simulation.

The ecosystem model we implemented is not meant to be realistic, but it helped us understand the concept of balance, which is fundamental in an ecosystem.

Our ecosystem contains two types of virtual entities: prey and predators. Predators are capable of eating prey. The ecosystem is represented as a discrete world in the form of a torus (displayed as a rectangle in the terminal), composed of multiple cells identified by their integer coordinates `(x, y)`. Each prey and predator occupies a specific cell and is able to move. At any given moment, a cell can contain multiple prey and predators. Additionally, each cell may contain grass, which serves as food for the prey.

Our ecosystem simulation is built upon various data structures and functions that we developed. The simulation relies on two linked lists—one for prey and one for predators—along with a two-dimensional static array representing the world.

## Educational Objectives

The primary educational objectives of this project are to provide students with practical experience in implementing and manipulating linked lists in C and to introduce them to the complexities of simulating dynamic systems. Through this project, students also gain insights into the importance of parameter tuning and system balance, which are crucial in both theoretical and applied computer science.

## Program Execution

To run the program, follow these steps after downloading the Git repository:

1. Extract the compressed file (`.zip`).
2. Open the extracted folder in a terminal.
3. Compile the source code using: `make`
4. Execute the program with: `./ecosys`
