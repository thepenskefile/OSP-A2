# Operating Systems Principles - COSC1114 - Assignment 2

Assignment 2 - Memory allocation strategies

## Allocation and deallocation lists

You will use two linked lists to manage memory allocation:

* A linked list of memory blocks allocations - allocMBList
* A linked list of memory blocks that have been allocated but deallocated later - freedMBList

In each of the lists, you need to keep track of the memory block information (e.g., the starting address in memory and the size).

## Memory allocation

Given a piece of information (like your_first_name), the memory allocation will:

  1. Search for a memory block in freedMBList (i.e., a memory block allocated previously and deallocated later), which is suitable according to a particular allocation strategy (detailed below). If the memory block is available, store the information in the memory block and update both freedMBList and allocMBList; if not, go to 2.
  2. Allocate a new memory block using `sbrk` or `brk` to store the information; update the allocMBList accordingly.

## Memory deallocation

Given a piece of information currently stored in a memory block, when it needs to be deallocated, the content currently in the memory block will be deleted. This can be done by deleting the corresponding node from allocMBList and adding a new node in freedMBList.

*Note the memory blocks in freedMBList should be merged into one memory block if they are consecutive in memory.*

## Allocation strategies

As a part of memory allocation, you will need to implement the following allocation strategies:

### First fit

Find the first memory block in freedMBList that is big enough. Split the block and allocate content to a chunk that is as large as necessary. Then, add the rest of the block back to freedMBList.

### Best fit

Find a memory block in freedMBList whose size is the closest match to the memory allocation needed. Split the block and allocate content to a chunk that is as large as necessary. Then, add the rest of the block back to freedMBList.

### Worst fit

Find the largest memory block in freedMBList. Split the block and allocate content to a chunk that is as large as necessary. Then, add the rest of the block back to freedMBList.

## Experiments

Implement the memory allocation and deallocation as required above for different allocation strategies. Run them on two data sets: **first-names.txt** and **middle-names.txt**.

In each data set, each line contains a name. Each name is a piece of information which needs to be stored in memory. You should follow the introductions below:

 1. For the first 1000 names, directly allocate memory blocks and update allocMBList
 2. Randomly delete 500 names, update allocMBList and freedMBList
 3. Then, read from the data set the next 1000 names. For each name, allocate memory blocks following “Memory allocation” above. Update allocMBList and freedMBList.
 4. Randomly delete 500 names, update allocMBList and freedMBList.
 5. Repeat 3 and 4 until the end of the data set.

Run each allocation strategy on each data set and your code should save the following information in an output file at the end of processing:

* The total memory allocated using `sbrk` or `brk`.
* The starting address and size of all nodes in freedMBList, each node per line.
* The starting address, size and content of all nodes in allocMBList, each node per line

## How to run

1. Compile the code by running `make` in the same directory as the `makefile`.
2. The program takes 3 command line arguments. The first is the location of the dataset being used. The second is the memory allocation scheme being used. The third is the location of the results output file. The command to run takes the following format:

    ```
    ./allocator [location-of-dataset] [ff | bf | wf ] [location-of-results-output-file]
    ```

### To use the first fit allocation strategy

```
./allocator first-names.txt ff results.txt
```

### To use the best fit allocation strategy

```
./allocator first-names.txt bf results.txt
```

### To use the worst fit allocation strategy

```
./allocator first-names.txt wf results.txt
```
