// Jeu de la Vie.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <random>
#include <sstream>

class Cell {
public:
    bool isAlive; // Indicates if the cell is currently alive
    bool willBeAlive; // Indicates if the cell will be alive in the next generation

    Cell() : isAlive(false), willBeAlive(false) {} // Default constructor

    Cell(bool isAlive) : isAlive(isAlive), willBeAlive(false) {}  // Initialization : isAlive flag based on the input and willBeAlive flag to false
};

class GameOfLife {
private:
    std::vector<std::vector<Cell>> grid; // Represents the grid of cells
    int rows; // Number of rows in the grid
    int cols; // Number of columns in the grid

public:
    GameOfLife(int rows, int cols) : rows(rows), cols(cols) {
        InitializeGrid();
    }

    // Method to initialize the grid randomly
    void InitializeGrid() {
        std::random_device rd; // Random device for generating random numbers
        std::mt19937 gen(rd()); // Mersenne Twister random number engine
        std::uniform_int_distribution<> dis(0, 1); // Uniform distribution to generate random values between 0 and 1

        grid.resize(rows, std::vector<Cell>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                bool isAlive = dis(gen) == 0; // Generates a random value(0 or 1) to determine if the cell is alive
                grid[i][j] = Cell(isAlive); // Creates a new Cell object and assigns it to the grid
            }
        }
    }

    // Method to print the grid on the interface
    void PrintGrid() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << (grid[i][j].isAlive ? "+ " : "- "); // Prints '+' if the cell is alive, '-' otherwise
            }
            std::cout << std::endl; // Moves to the next line after printing each row of the grid
        }
    }

    // Method to count live neighbors of a cell
    int CountLiveNeighbors(int row, int col) {
        int liveNeighbors = 0;
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (i != row || j != col)  // Exclude the current cell from the neighbor count
                    if (i >= 0 && i < rows && j >= 0 && j < cols) // Check if the neighbor cell is within the grid boundaries
                        if (grid[i][j].isAlive) // Check if the neighbor cell is alive
                            liveNeighbors++; // Increment the count of live neighbors
            }
        }
        return liveNeighbors;
    }

    // Method to generate the future grid 
    void CalculateNextGeneration() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int liveNeighbors = CountLiveNeighbors(i, j); // Get the count of live neighbors for the current cell
                if (grid[i][j].isAlive) // Apply the rules for a live cell
                    if (liveNeighbors == 2 || liveNeighbors == 3)
                        grid[i][j].willBeAlive = true;
                    else
                        grid[i][j].willBeAlive = false;
                else // Apply the rules for a dead cell
                    if (liveNeighbors == 3)
                        grid[i][j].willBeAlive = true;
                    else
                        grid[i][j].willBeAlive = false;
            }
        }

        // Update the state of each cell based on the calculated next generation
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid[i][j].isAlive = grid[i][j].willBeAlive;
            }
        }
    }
};

int main() {

    while (true) {
        int rows = 0, cols = 0;
        std::string input;

        // Prompt the user to enter the number of rows
        while (true) {
            std::cout << "Enter the number of rows: ";
            std::getline(std::cin, input);
            std::stringstream ss(input);

            if (ss >> rows) // Test if the number of rows is an integer 
                break;

            std::cout << "Invalid input. Please enter a valid integer value." << std::endl;
        }

        // Prompt the user to enter the number of columns
        while (true) {
            std::cout << "Enter the number of columns: ";
            std::getline(std::cin, input);
            std::stringstream ss(input);

            if (ss >> cols) // Test if the number of columns is an integer 
                break;

            std::cout << "Invalid input. Please enter a valid integer value." << std::endl;
        }

        std::cout << std::endl;

        // Create a GameOfLife object with the specified number of rows and columns
        GameOfLife game(rows, cols);

        // Simulate 10 generations
        for (int generation = 1; generation <= 10; generation++) {
            std::cout << "Generation " << generation << ":" << std::endl;

            // Print the current grid state
            game.PrintGrid();
            std::cout << std::endl;

            // Calculate the next generation
            game.CalculateNextGeneration();
        }

        // Ask the user if they want to restart the game
        std::cout << "Do you want to restart the game? (y/n): ";
        std::getline(std::cin, input);

        if (input != "y" && input != "Y")
            break; 

        std::cout << std::endl;
    }

    system("pause");
    return 0;
}