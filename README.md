## CS-300: Data Structures and Algorithms — ABCU Advising Program

## Overview

A C++ console application built for a simulated university advising department. The program loads Computer Science course data from a CSV file into a binary search tree, prints the full course catalog in alphanumeric order, and allows advisors to look up individual courses along with their prerequisites.

## The Problem It Solves

Academic advisors at ABC University needed a fast way to do two things during student conversations: pull up a sorted list of every course in the program, and look up a specific course to see its title and prerequisites. The solution needed to handle both operations efficiently without manual sorting.

## My Approach

Before writing any code I analyzed three data structures in pseudocode -- a vector, a hash table, and a binary search tree -- and compared their worst-case runtimes for both operations.

All three can store the same data, but they are not equally good at it. A hash table has the fastest average lookup but stores data in hash order, meaning a sorted list requires pulling everything out and sorting separately. A vector loads quickly but requires a linear scan for lookups. A binary search tree keeps data ordered by design, so an in-order traversal returns the sorted list with no extra sorting step while still giving O(log n) average search.

I chose the binary search tree -- not because it was fastest at any single operation, but because it was the best fit for the specific combination of requirements. Choosing based on the actual problem rather than defaulting to the fastest-sounding structure was the biggest takeaway from this project.

## Technical Highlights

CSV parsing with input validation -- skips malformed lines, handles quoted paths from Windows "Copy as path" feature
Binary search tree implementation including insertion, in-order traversal, search, and node deletion with two-child case handling
Pseudocode-first design approach -- full algorithm analysis completed before any C++ was written
Input validation throughout -- numeric menu input verification, file open confirmation, data load requirement before search

## Technologies Used

C++ · Binary Search Tree · Hash Table Analysis · Vector Analysis · Big-O Analysis · CSV File Parsing · Object-Oriented Design

## What I Learned

How to select data structures based on problem requirements rather than general performance reputation
The practical difference between O(n²) and O(n log n) sorting -- seeing selection sort take nearly a second on a dataset where quicksort finished in a fraction of that time made Big-O concrete rather than theoretical
Separating responsibilities into focused functions so individual pieces can change without affecting the whole program
Writing comments that explain intent rather than narrating what the code already shows

## Artifacts

Project One -- Runtime and memory analysis comparing vector, hash table, and binary search tree with Big-O justification and recommendation
Project Two -- Fully functional advising program implementing the recommended binary search tree solution
