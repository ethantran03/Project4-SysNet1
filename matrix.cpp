#include <iostream>
#include <ctime>
#include <chrono>

const int ROWS = 20480;
const int COLS = 4096;  // Each row has one page (4096 bytes)
char matrix[ROWS][COLS];

// Function to measure execution time using clock_gettime
long long measureExecutionTime(void (*operation)()) {
    struct timespec start, end;
    
    // Start timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Execute the operation
    operation();

    // Stop timer
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate time elapsed in microseconds
    long long elapsedTime = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_nsec - start.tv_nsec) / 1000;
    return elapsedTime;
}

// Operation: Write row-major order
void writeRowMajor() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = 'A';  // Assign a character
        }
    }
}

// Operation: Write column-major order
void writeColMajor() {
    for (int j = 0; j < COLS; ++j) {
        for (int i = 0; i < ROWS; ++i) {
            matrix[i][j] = 'A';  // Assign a character
        }
    }
}

// Operation: Read row-major order
void readRowMajor() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            volatile char temp = matrix[i][j];  // Read value (volatile to prevent optimization)
        }
    }
}

// Operation: Read column-major order
void readColMajor() {
    for (int j = 0; j < COLS; ++j) {
        for (int i = 0; i < ROWS; ++i) {
            volatile char temp = matrix[i][j];  // Read value (volatile to prevent optimization)
        }
    }
}

// Wrapper to execute operations multiple times and get average time
long long getAverageExecutionTime(void (*operation)(), int repetitions = 10) {
    long long totalDuration = 0;
    for (int i = 0; i < repetitions; ++i) {
        totalDuration += measureExecutionTime(operation);
    }
    return totalDuration / repetitions;
}

int main() {
    // Repeat experiments 10 times and calculate average time
    long long avgWriteRow = getAverageExecutionTime(writeRowMajor);
    long long avgWriteCol = getAverageExecutionTime(writeColMajor);
    long long avgReadRow = getAverageExecutionTime(readRowMajor);
    long long avgReadCol = getAverageExecutionTime(readColMajor);

    // Output the average times for each operation
    std::cout << "Average Execution Times (microseconds):" << std::endl;
    std::cout << "1. Write Row-Major: " << avgWriteRow << " μs" << std::endl;
    std::cout << "2. Write Col-Major: " << avgWriteCol << " μs" << std::endl;
    std::cout << "3. Read Row-Major: " << avgReadRow << " μs" << std::endl;
    std::cout << "4. Read Col-Major: " << avgReadCol << " μs" << std::endl;

    return 0;
}
