Submission file structure
=========================

This submission contains the following:

├── output
│   ├── ff_first-names_output
│   ├── bf_first-names_output
│   ├── wf_first-names_output
│   ├── ff_middle-names_output
|   ├── bf_middle-names_output
|   ├── wf_middle-names_output
├── src
│   ├── allocator.c
│   ├── allocator.h
│   ├── linked_list.c
│   ├── linked_list.h
|   ├── utility.h
├── Makefile
├── readme.txt
├── .gitignore

Makefile
--------
Contains commands for code compilation.

src/allocator.c
---------------
Contains the algorithms and main method.

src/allocator.h
---------------
Contains Allocator struct definition and constants.

src/linked_list.c
-----------------
Contains linked list helper methods like create list, create node, insert node, remove node.

src/linked_list.h
-----------------
Contains List and Node struct definitions.

src/utility.h
-------------
Contains helper constants and Boolean struct definition.

ff_first-names_output 
---------------------
The results of the first fit algorithm run on the first names dataset

bf_first-names_output
---------------------
The results of the best fit algorithm run on the first names dataset

wf_first-names_output
---------------------
The results of the worst fit algorithm run on the first names dataset

ff_middle-names_output
----------------------
The results of the first fit algorithm run on the middle names dataset

bf_middle-names_output
----------------------
The results of the best fit algorithm run on the middle names dataset

wf_middle-names_output
----------------------
The results of the worst fit algorithm run on the middle names dataset


The program
============

The program takes 3 command line arguments.
The first is the location of the dataset being used. 
The second is the memory allocation scheme being used. 
The third is the location of the results output file.
The command to run takes the following format:

$ ./allocator [location-of-dataset] [ff | bf | wf ] [location-of-results-output-file]

where:
ff = first fit algorithm
bf = best fit algorithm
wf = worst fit algorithm


How to run
==========

First, compile the code by running make in the root directory:
    $ make

To run first fit, enter:
    $ ./allocator first-names.txt ff results.txt

To run best fit, enter:
    $ ./allocator first-names.txt bf results.txt

To run worst fit, enter:
    $ ./allocator first-names.txt wf results.txt


Output files
============

The output for all algorithms on both datasets have been provided in the output directory.
The output directory includes:
1. ff_first-names_output (The first fit algorithm run on the first names dataset)
2. bf_first-names_output (The best fit algorithm run on the first names dataset)
3. wf_first-names_output (The worst fit algorithm run on the first names dataset)
4. ff_middle-names_output (The first fit algorithm run on the middle names dataset)
5. bf_middle-names_output (The best fit algorithm run on the middle names dataset)
6. wf_middle-names_output (The worst fit algorithm run on the middle names dataset)