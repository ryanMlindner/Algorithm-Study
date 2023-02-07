##pros
# O(n lg n) running time
# sorts in place
# heap property is useful for structuring priority queues
##cons
# not the most efficient way to sort (quicksort beats it almost every case)
# maintaining a heap is constant memory/time usage
# no guarantee that it maintains the original array while sorting

##definitions for heapsort
# heap property states that for every node (i) other than the root
# of the tree (A[1]), A[parent(i)] >= A[i]
# heapsort uses heapify() to turn an array into a heap, and then sorts by taking the first item of the heap
# swapping it with the last item of the array, and decrementing heap size
# so that a shrinking heap is replaced with a growing sorted list in the same array

##import packages, dependencies
# numpy for efficient arrays, csv for file read/write,
import numpy as np
import csv

##obtain input of a (probably) unsorted list of items through I/O or from file

#placeholder
sourceArray = np.array([10,5,3,5,24,1,19,34,6,42,22])

##readability help
def valueOf(A, arrayIndex):
    return A[arrayIndex-1]

def exchangeValue(A, swap0, swap1):
    index0 = swap0
    index1 = swap1
    A[index0], A[index1] = A[index1], A[index0]

##inline macros for moving around the heap
def left(index): return 2*index
def right(index): return 2*index + 1
def parent(index): return int(index/2)

##build a heap with the size of the array
def buildHeap(A):
    heapSize = A.len()
    startingIndex = int(heapSize/2)
    while (startingIndex >= 1):
        heapifyRecursive(heapSize, A, startingIndex)
# for each index in the array from max length down to 1
# heapify recursively(max binary log of size nested calls) or iteratively goes through a dynamic length stack
# when heapify ends the array will satisfy the heap property

##heapifyRecursive changes the order of items in the array in order to maintain the heap property
def heapifyRecursive(heapSize, A, index):
    # at any given index (i) in the heap, find left and right children
    l = left(index)
    r = right(index)
    # compare the values of i and the left and right children of i
    # determine the largest
    if l <= heapSize and valueOf(A, l) > valueOf(A, index):
        largest = l
    else:
        largest = index
    if r <= heapSize and valueOf(A, r) > valueOf(A, index):
        largest = r
    # if the largest is NOT the value at the original index
    # swap the largest and the index positions in the heap
    if largest != index:
        exchangeValue(A, index, largest)
        # heapify the new index of largest to fix any violations of the heap property
        # caused by exchanging (left or right) with i
        heapifyRecursive(heapSize, A, largest)
    # if the largest is the original index, the tree at (i) is a heap, no further action required by heapify


##TODO iterative
##heapifyIterative has the same goal, but uses a control loop instead of recursion
# define a stack to use for flagging the end of the loop
# pop the first item, do internal logic of heapify
# (compare left, right, i -> largest goes to A[i])
# if largest is NOT original index
# swap largest and original, add the index of largest to the stack
# ends when stack is empty

##TODO heapsort
##heapsort uses the built heap to sort into an ordered array of size n
# iterate over the array from max length down to index (2)
# take the element at A[1] and replace it with A[i]
# call heapify at A[1] with the new value to restore the heap property
# result is a sorted list of items

##TODO flow control for calling the sort, regardless of if this is the __main__ module