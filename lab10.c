/*
    Carson Davie
    Lab 10
    04/18/2024
    Torosdagli
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *newNode = (struct Trie *)malloc(sizeof(struct Trie));

    if (newNode)
    {
        newNode->count = 0;

        // initialize children to null
        for (int i = 0; i < 26; i++)
        {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{

    int len = strlen(word);
    struct Trie *currentNode = pTrie;

    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL)
        {
            // create new node if necessary
            currentNode->children[index] = createTrie();
        }
        currentNode = currentNode->children[index];
    }
    // mark the end of the word
    currentNode->count++;
}

// computes the number of occurances of the word
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    int len = strlen(word);
    struct Trie *currentNode = pTrie;

    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL)
        {
            // word not found
            return 0;
        }
        currentNode = currentNode->children[index];
    }
    // return the count of the last node
    return currentNode->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    // recursively free children
    if (pTrie != NULL)
    {
        for (int i = 0; i < 26; i++)
        {
            deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int numwords;
    FILE *fp = fopen(filename, "r");

    fscanf(fp, "%d", &numwords);

    // allocate memory for each word
    for (int i = 0; i < numwords; i++)
    {
        pInWords[i] = (char *)malloc(25 * sizeof(char));
        fscanf(fp, "%s", pInWords[i]);
    }

    fclose(fp);
    return numwords;
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}