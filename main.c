#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WCHUNK 10  //static chunk of space for the word

struct tNode{
    struct tNode *left, *right;
    int count;
    char *word;
};

char *getWord(FILE *in){
    char *tempWord = NULL;
    int pChar, cCtr; //parse char, char ctr
    size_t size; //word size (size_t is unsigned... positive only)


    //fgetc() = "from file get char"; isalpha() = check if char is alphanumeric
    for (pChar = fgetc(in); !isalpha(pChar); pChar = fgetc(in)){
        if(pChar == EOF)
            return NULL;
    }

    size = WCHUNK;
    tempWord = malloc(size);
    if(tempWord == NULL)
        return NULL;

    //store characters upon parse
    for(cCtr = 0; isalpha(pChar); pChar = fgetc(in)){
        if (cCtr == size - 1){  //Hold on! This word may have more than 10 letters!!
            char *tempWord2; //Make a pointer to make our temp word bigger!

            tempWord2 = realloc(tempWord, size+=WCHUNK); //double the space

            if(tempWord2 == NULL) //Make sure our new pointer is not null
                return NULL;
            else
                tempWord = tempWord2; //make our original tempWord bigger
        }

        *(tempWord+cCtr++) = pChar;
    }

    // Null terminate the word
    *(tempWord+cCtr) = 0;
    //put our non-alphas back - needed? or does pChar live on the stack?
    ungetc(pChar, in);

    return tempWord;
}

int insert(char *str, struct tNode **root){
    struct tNode *tempNode = malloc(sizeof *tempNode);

    if(tempNode == NULL)
        return 0; //new node needs space... return 0 if no more space

    //Init tempNode
    tempNode->left = tempNode->right = NULL;
    tempNode->word = str; //Our temp node is now 'holding' the string to be inserted
    tempNode->count = 1;

    //No nodes yet? Then we make our root
    if(*root == NULL)
        *root = tempNode;

        //Root does exist
    else{
        struct tNode *prevNode = NULL, *curNode = *root;
        int sort;

        while(curNode != NULL){
            prevNode = curNode; //Traverse down the tree

            /* strcmp() returns 0 if identical
             ** returnVal<0 if curNode < tempNode
             ** returnVal>0 if curNode > tempNode */
            sort = strcmp(curNode->word, tempNode->word);

            if(sort == 0){
                curNode->count += 1; //word exists in tree; count and return
                free(tempNode);
                return 0; // no new nodes created
            }
            else {
                if (sort < 0){
                    curNode = curNode->left;
                    prevNode->left = tempNode; //check logic here
                }

                else{ //sort > 0
                    curNode = curNode->right;
                    prevNode->right = tempNode; //and here
                }
            }
        }
    }

    return 1;

}

void delete(struct tNode *root){

    if(root == NULL)
        return;

    delete(root->right);

    // TODO print this to file
    // fprintf(outFile, ...)
    printf( "%s: %d\n",root->word, root->count);

    delete(root->left);
    free(root->word);
    free(root);

}

//argc is the # of arguments, "argument count" passed into cmd line
// argv is the definition of those arguments

int main(int argc, char *argv[]) {

    //FILE *inFile, *outFile; // input file
    //char *ifName = "./input02.txt";
    //char *ofName; //name of output file



    if(argc != 2){
        printf("usage: %s [filename]", argv[0]);
        return 1;
    }

    else{
        //ifName = argv[1];

        FILE *inFile = fopen(argv[1], "r");


        if (inFile == NULL){
            printf("infile not found");
            return 1;
        }

        else {
            struct tNode *root = NULL;
            //Parse the filename to make output file
            char *aWord;

            while((aWord = getWord(inFile)) != NULL){
                insert(aWord, &root);

            }
            delete(root);
            fclose(inFile);
        }
    }
    return 0;
}
