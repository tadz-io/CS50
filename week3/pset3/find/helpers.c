/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0)
    {
        return false;
    }
    
    int midIndex = n;
    // TODO: implement a searching algorithm
    while (midIndex > 0)
    {
        // put index in the middle
        midIndex /= 2; 
    
        if (value == values[midIndex])
        {
            return true;
        }
        else if (value > values[midIndex])
        {
            // pass address of middle element + 1 in array to search
            return search(value, &values[midIndex + 1], n - 1 - midIndex);
        }
        else if (value < values[midIndex])
        {
            return search(value, values, midIndex);
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 * implementation of selection sort
 */
void sort(int values[], int n)
{
    // prototype
    void swap(int array[], int id1, int id2);
    
    int min;
    
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0; i < n - 1; i++)
    {
        int j = i + 1;
        min = i;
        
        // look for minimum value in unsorted part of array
        for ( ; j < n; j++)
        {
            if (values[j] < values[min])
            {
                min = j;
            }
        }
        
        // swap values if minimum is different from itself      
        if (min != i)
        {
            swap(values, i, min);
        }
    }
    return;
}

/**
 * swap two values in an array
 */
void swap(int array[], int id1, int id2)
{
    int tmp = array[id1];
    
    array[id1] = array[id2];
    array[id2] = tmp;
    
    return;
}