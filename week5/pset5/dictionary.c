/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define APOSTROPHE_INDEX 26
#define ARRAY_SIZE 27

typedef struct node
{
    bool is_word;
    struct node *children[ARRAY_SIZE];
}node;

node* free_memory(node *current_node);

node root = {false, {NULL}};
node *const ptrRoot = &root;

unsigned int sizeDictionary = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    int i = 0;
    
    // traverse pointer
    node *ptrTrav = ptrRoot;
    
    while(word[i] != '\0')
    {
        int c = word[i];
        // convert chars to key; case-insensitive
        if (isalpha(word[i]))
        {
            c = (islower(word[i])) ? word[i] - 'a' : word[i] - 'A';
        }
        else
        {
            c = APOSTROPHE_INDEX;
        }
    
        if (ptrTrav->children[c] == NULL)
        {
            return false;
        }
        else
        {
            ptrTrav = ptrTrav->children[c];
        }
        
        i++;
    }
    
    return ptrTrav->is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    FILE* fptr = fopen(dictionary, "r");
    
    if (fptr == NULL)
    {
        return false;
    }
    
    // traverse pointer
    node *ptrTrav = ptrRoot;
    int c;
    
    // read dictionary into TRIE
    while ((c = fgetc(fptr)) != EOF)
    {
        // end of word
        if (c == '\n')
        {
            ptrTrav->is_word = true;
            ptrTrav = ptrRoot;
            sizeDictionary++;
            
        }
        else
        {
            // convert chars to key
            c = (isalpha(c)) ? c-'a' : APOSTROPHE_INDEX;
            
            if (ptrTrav->children[c] == NULL)
            {
                ptrTrav->children[c] = calloc(1, sizeof(node));
            }
            
            ptrTrav = ptrTrav->children[c];
        }
        
    }
    
    if (ferror(fptr))
    {
        fclose(fptr);
        return false;
    }
    fclose(fptr);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return sizeDictionary;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    node* temp = ptrRoot;
    temp = free_memory(temp);
    
    return (temp == NULL);
    
}

node* free_memory(node *current_node)
{
    for (int i = 0; i < ARRAY_SIZE; i++)    
    {    
        if (current_node->children[i] != NULL)
        {
            current_node->children[i] = free_memory(current_node->children[i]);
        }
    }
    // do not free root pointer since it is not on the heap
    if (current_node != ptrRoot)
    {
        free(current_node);    
    }
    
    return NULL;
    
}