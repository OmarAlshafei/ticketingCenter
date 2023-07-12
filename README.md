# Ticketing Center Program

This program reads in information about customers and determines at what time each customer will check out.

## Description

The program is designed to handle customer checkout operations. It prompts the user to enter information about customers, such as their checkout time, line number, name, and number of tickets. Based on this information, the program determines the order in which customers will check out and displays their checkout times.

## Functionality

The program performs the following tasks:

1. Initializes and loads a queue.
2. Creates customer objects using user input.
3. Adds customers to the appropriate line in the queue.
4. Finds the queue with the customer who has the smallest checkout time.
5. Displays the customer's checkout information.
6. Dequeues the customer from the queue.
7. Continues until all customers have been processed.

## Input Format

The program expects the following input format:

1. The number of test cases (`testCases`).
2. For each test case:
- The number of customers (`nCustomers`).
- For each customer:
  - The customer's checkout time (`time`).
  - The customer's line number (`lineNum`).
  - The customer's name (`name`).
  - The number of tickets (`numTickets`).

## Output Format

The program outputs the following information for each customer:

- Customer's name from line `lineNum` checks out at time `time`.

## Limitations

- The program supports a maximum of 25 test cases.
- Each test case can have up to 500,000 customers.
- The program exits if any of the following conditions are met:
- The `time` is greater than `MAX_TIME`.
- The `lineNum` is greater than `TOTAL_LINES`.
- The `numTickets` is greater than `MAX_ITEMS`.
- The `testCases` is greater than 25.
- The `nCustomers` is greater than 500,000.

## Memory Management

The program utilizes dynamic memory allocation for storing customer and queue data.

## How to Use

1. To compile & run this code, first download the main.c file and any requisite input files to the same directory.

2. Use "gcc -g main.c" to generate a program file from the .c file.

3. You can now run the program while passing in your input file with this command: "./a.out < in.txt > out.txt".

4. The expected output will be shown in the "out.txt" file.

## Author

This project is created by Omar Alshafei.

