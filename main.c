#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

int countWordsOfLength(char* filename, int wordSize) { 
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return -1;

    int count = 0;
    char word[100];
    while (fscanf(file, "%s", word) == 1) {
        if (strlen(word) == wordSize)
            count++;
    }

    fclose(file);
    return count;
}

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return false;

    int count = 0;
    char word[100];
    while (fscanf(file, "%s", word) == 1) {
        if (strlen(word) == wordSize) {
            strcpy(words[count], word);
            count++;
        }
    }

    fclose(file);
    return (count == numWords);
}

int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    while (loInd <= hiInd) {
        int mid = loInd + (hiInd - loInd) / 2;
        int cmp = strcmp(words[mid], aWord);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            loInd = mid + 1;
        else
            hiInd = mid - 1;
    }
    return -1;
}

void freeWords(char** words, int numWords) {
    for (int i = 0; i < numWords; i++)
        free(words[i]);
    free(words);
}

void insertWordAtFront(WordNode** ladder, char* newWord) {
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
    newNode->myWord = strdup(newWord);
    newNode->next = *ladder;
    *ladder = newNode;
}

int getLadderHeight(WordNode* ladder) {
    int height = 0;
    WordNode* current = ladder;
    while (current != NULL) {
        height++;
        current = current->next;
    }
    return height;
}

WordNode* copyLadder(WordNode* ladder) {
    WordNode* copiedLadder = NULL;
    WordNode* current = ladder;
    WordNode* tail = NULL;

    while (current != NULL) {
        WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
        newNode->myWord = current->myWord;
        newNode->next = NULL;

        if (copiedLadder == NULL)
            copiedLadder = newNode;
        else
            tail->next = newNode;

        tail = newNode;
        current = current->next;
    }

    return copiedLadder;
}

void freeLadder(WordNode* ladder) {
    WordNode* current = ladder;
    while (current != NULL) {
        WordNode* temp = current;
        current = current->next;
        free(temp->myWord);
        free(temp);
    }
}

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    LadderNode* newNode = (LadderNode*)malloc(sizeof(LadderNode));
    newNode->topWord = newLadder;
    newNode->next = NULL;

    if (*list == NULL) {
        *list = newNode;
        return;
    }

    LadderNode* current = *list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

WordNode* popLadderFromFront(LadderNode** list) {
    if (*list == NULL)
        return NULL;

    LadderNode* temp = *list;
    *list = (*list)->next;
    WordNode* poppedLadder = temp->topWord;
    free(temp);
    return poppedLadder;
}

void freeLadderList(LadderNode* myList) {
    while (myList != NULL) {
        LadderNode* temp = myList;
        myList = myList->next;
        freeLadder(temp->topWord);
        free(temp);
    }
}

WordNode* findShortestWordLadder(char** words, bool* usedWord, int numWords, int wordSize, char* startWord, char* finalWord) {
    // Create a queue for BFS
    LadderNode* queue = NULL;

    // Mark all words as not visited
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }

    // Mark the startWord as visited and enqueue it
    int startInd = findWord(words, startWord, 0, numWords - 1);
    usedWord[startInd] = true;
    WordNode* startLadder = NULL;
    insertWordAtFront(&startLadder, startWord);
    insertLadderAtBack(&queue, startLadder);

    // Perform BFS
    while (queue != NULL) {
        // Dequeue a ladder from the queue
        WordNode* currLadder = popLadderFromFront(&queue);

        // Get the last word in the ladder
        char* currWord = currLadder->myWord;
        int currInd = findWord(words, currWord, 0, numWords - 1);

        // If we reach the finalWord, return the ladder
        if (strcmp(currWord, finalWord) == 0) {
            return currLadder;
        }

        // Explore all adjacent words of currWord
        for (int i = 0; i < wordSize; ++i) {
            char temp = currWord[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c != temp) {
                    currWord[i] = c;
                    int nextInd = findWord(words, currWord, 0, numWords - 1);
                    if (nextInd != -1 && !usedWord[nextInd]) {
                        // Mark the word as visited and enqueue a new ladder
                        usedWord[nextInd] = true;
                        WordNode* newLadder = copyLadder(currLadder);
                        insertWordAtFront(&newLadder, currWord);
                        insertLadderAtBack(&queue, newLadder);
                    }
                }
            }
            currWord[i] = temp;
        }
    }

    // If no ladder is found, return NULL
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main()
//-----------------------------------------------------
int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // dictionary is always words.txt
    char dict[100];
    strcpy(dict, "words.txt");
    int numWords = countWordsOfLength(dict,wordSize);
    if (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Terminating program...\n");
        return -1;
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
