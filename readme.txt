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