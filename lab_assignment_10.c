#include <stdio.h>
#include <stdlib.h>

struct Trie
{
    struct Trie *children[26];
    char tWord;
    int branch;
};

void insert(struct Trie **ppTrie, char *word)
{
    if(*ppTrie==NULL)
    {
        struct Trie* newNode = (struct Trie*) calloc (1, sizeof(struct Trie));
        for (int i=0; i<26; i++)
        {
            newNode->children[i] = NULL;
        }
        newNode->branch = 0;
        newNode->tWord = '\0';
        *ppTrie = newNode;
    }
    
    struct Trie* tmp = *ppTrie;

   for(int i =0; word[i]!='\0'; i++)
   {
        int indx = (int)word[i]-'a';
        if(tmp->children[indx] == NULL)
        {
            struct Trie* newNode = calloc (1, sizeof(struct Trie));
            for (int i=0; i<26; i++)
            {
                newNode->children[i] = NULL;
            }
            newNode->branch = 0;
            newNode->tWord = word[i];
            tmp->children[indx] = newNode;
        }
        tmp=tmp->children[indx];
   }

   tmp->branch = 1;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* tmp = pTrie;

    for(int i =0; word[i]!='\0'; i++)
    {
        int indx = (int)word[i]-'a';
        if(tmp->children[indx] == NULL)
        {
            return 0;
        }
        tmp=tmp->children[indx];
    }
    if(tmp!=NULL && tmp->branch == 1)
    {
        return 1;
    }
    return 0;
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    
    for(int i=0; i<sizeof(pTrie); i++) 
    {
        free(pTrie->children[i]);
        pTrie->children[i] = NULL;
    }
    free(pTrie);
    pTrie = NULL;
    
    return pTrie;
}

int main()
{
    struct Trie* trie =  NULL;
    //read the number of the words in the dictionary
    //parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    
    for (int i=0;i<5;i++)
    {
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    
    if (trie != NULL)
       printf("There is an error in this program\n");
    
    return 0;
}