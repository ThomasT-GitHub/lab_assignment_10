#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
  int count;
  struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie() {
  // Allocates memory for the trie
  struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));

  // If memory allocated correctly set it up
  if (trie != NULL) {
    // Sets count to 0
    trie->count = 0;

    // Sets all children to NULL
    for (int i = 0; i < 26; i++) {
      trie->children[i] = NULL;
    }
  }

  // Returns the trie
  return trie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
  // Returns if no word left to add
  if (strlen(word) == 0) {
    pTrie->count++;
    return;
  }

  // Gets the position for insertion
  int pos = word[0] - 'a';
  if (pTrie->children[pos] == NULL) {
    pTrie->children[pos] = createTrie();
  }

  // Chops off the start of the word
  char *newWord = word + 1;
  insert(pTrie->children[pos], newWord);
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
  // Returns if no word left to add
  if (strlen(word) == 0) return pTrie->count;

  // Gets the position for insertion
  int pos = word[0] - 'a';
  if (pTrie->children[pos] == NULL) {
    return 0;
  }

  // Chops off the start of the word
  char *newWord = word + 1;
  return numberOfOccurances(pTrie->children[pos], newWord);
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
  // Free any children in the trie with allocated memory
  for (int i = 0; i < 26; i++) {
    if (pTrie->children[i] != NULL) {
      deallocateTrie(pTrie->children[i]);
    }
  }

  // Frees the trie
  free(pTrie);

  return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
  FILE *f = fopen(filename, "r");
  if (f != NULL) {
    // Loads the number of words
    int numWords;
    fscanf(f, "%d", &numWords);

    // Loads the words into pInWords
    for (int i = 0; i < numWords; i++) {
      pInWords[i] = (char *)malloc(sizeof(char) * 101);
      fscanf(f, "%s", pInWords[i]);
    }

    // Returns the number of words
    return numWords;

    // Closes the file
    fclose(f);
  }

  // If file didnt open, return NULL
  return -1;
}

int main(void) {
  char *inWords[256];

  // read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i = 0; i < numWords; ++i) {
    printf("%s\n", inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i = 0; i < numWords; i++) {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i = 0; i < 5; i++) {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL) printf("There is an error in this program\n");
  return 0;
}
