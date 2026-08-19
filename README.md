CS-300: Data Structures and Algorithms

This repository contains my portfolio work from CS-300 at Southern New Hampshire University. The two artifacts here are the runtime and memory analysis from Project One, and the working C++ program from Project Two that loads, sorts, and prints a list of Computer Science courses.

Contents
Project One - Runtime and Memory Analysis.docx — pseudocode and a Big O analysis comparing a vector, a hash table, and a binary search tree for the same problem, along with a recommendation.
ProjectTwo.cpp — the finished advising program. Reads course data from a CSV file into a binary search tree, prints the full course list in alphanumeric order, and looks up individual courses along with their prerequisites.
The Problem

ABC University (ABCU) needed an advising assistance program for their Computer Science department. Academic advisors wanted to be able to do two things quickly during a conversation with a student: pull up a full list of every course in the program sorted in alphanumeric order, and look up a single course to see its title and what prerequisites it requires. The course data came from a CSV file where each line held a course number, a course title, and zero or more prerequisites.

My Approach

The interesting part of this project was that the requirements did not tell you which data structure to use. Before writing any real code, I worked through the same problem three separate times in pseudocode, once for a vector, once for a hash table, and once for a binary search tree, then analyzed the worst case runtime of each.

That process is what made the value of understanding data structures actually click for me. All three structures can hold the same course data and technically satisfy both requirements, but they are not equally good at it. A hash table has the fastest average lookup of the three, but it stores data in whatever order the hash function decides, so producing a sorted course list means pulling every course back out and sorting it separately. A vector is simple and loads quickly, but it has no ordering either and requires a linear scan to find a single course. A binary search tree keeps its data ordered by design, so an in order traversal returns the sorted list with no separate sorting step at all, while still giving a reasonable O(log n) average search.

I recommended the binary search tree, not because it is the fastest structure at any single operation, but because it was the best fit for the specific combination of things this program needed to do. That distinction, choosing based on the actual problem rather than defaulting to whatever seems fastest or most familiar, was the biggest takeaway from the course.

Roadblocks

The hardest concept for me was removing a node from a binary search tree when that node has two children. Deleting a leaf or a node with a single child is straightforward, but the two child case requires finding the in order successor, copying its value into the node being deleted, and then removing the successor from its original position. Reading about it was not enough. What finally made it make sense was tracing through a small example by hand and then deliberately testing the ugliest case I could think of, deleting the root node of a populated tree and running a traversal afterward to confirm every remaining item was still present and still in sorted order.

The other roadblock was less about algorithms and more about environment. On Project Two I spent a frustrating amount of time on a file that would not open, only to eventually find that the path I was pasting in had quotation marks around it from Windows' "Copy as path" feature. Once I found it, I did not just remove the quotes and move on, I added logic to the program to strip them automatically, since any real user could reasonably hit the same thing. That turned an annoying dead end into a small improvement in the program's input handling.

How This Changed My Approach to Design

Before this course I would generally start coding and figure out the structure as I went. Working through three full pseudocode designs before writing a single line of C++ changed that. By the time I actually implemented Project Two, most of the hard thinking was already done and I was mainly translating a design I had already reasoned through and justified.

It also changed how I think about performance. Seeing selection sort take almost a full second on a data set where quicksort finished in a fraction of that time made the difference between O(n²) and O(n log n) feel concrete instead of theoretical. I now think about how a program will behave as the data grows, not just whether it produces the right answer on a small test file.

Maintainability, Readability, and Adaptability

A few habits came out of this course that I have carried forward.

I now separate responsibilities into distinct functions rather than writing one long block of logic. In Project Two, parsing a line, trimming whitespace, normalizing case, loading the file, and printing the menu are all their own functions, which means I can change how the file is parsed without touching how courses are stored.

I also treat input validation as part of the job rather than an afterthought. The program checks that menu input is actually numeric before converting it, verifies that the data file opened successfully, skips malformed lines instead of crashing on them, and requires data to be loaded before allowing a search. None of that is required for the program to work on well behaved input, but all of it is required for the program to be usable by someone who is not the person who wrote it.

Finally, I have gotten more deliberate about comments. My earlier habit was either commenting almost nothing or narrating every line. What I aim for now is explaining the intent behind a section, the why rather than the what, since the code already says what it does.
