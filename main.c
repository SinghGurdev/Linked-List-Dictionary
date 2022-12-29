//Written by Gurdev Singh 
//Application Creates a Dictionary of User entered Words
//Uses Linked List as Data Structure 

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <ctype.h>
char clear[] = "cls";
#endif

#ifdef linux
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char clear[] = "clear";
#endif


//Structs needed for Linked List and data
struct entry{
    int size;
    char word[5];
};
struct Node {
    struct entry data;
    struct Node* next;
};

//Global Varaiables
struct Node* head; //Node Pointer to the head of the Linked List
struct Node* tempPointer; //Temp pointer to be used as a helper 
char tempString[300];
struct entry tempEntry;
char input[300];
int tempInt;
int again = 1;

//Function Declerations
void serach(char*,int); //Takes a string to search and what mode to use 
void nuke(); //Deletes Linked List
void printList(); //Prints out all Data entries in the Linked List 
void insert(char*);//Takes a string and adds it to the Dictionary 
void menu(); //Displays options the Application can do

int main(void){
    while(1){
        if(again == 0)while ((getchar()) != '\n');
        again = 1;
        printf("Please Enter in a Sentence: \n");
        fgets(input, sizeof(input), stdin);
        insert(input);
        while(again){
            menu();
        }
    };
}

//Function Defination 
void search(char* str,int mode){
    //Gets the ponter to the first Node in the Linked List
    tempPointer = head;
    //Creates string array for case insensitive serach mode
    char search[4], data[4];
    int i;
    //Creates a Loop to go through each entry in the Linked List 
    while (tempPointer != NULL){
        //Checks to see what mode is being used 
        if(mode){
            for(i = 0; i < 4; i++){
                search[i] = toupper(str[i]);
                data[i] = toupper(tempPointer->data.word[i]);
            }
            if(strncmp(search,data,4) == 0){
                printf("Found: %s \n",str);
                return;
            }else 
                tempPointer = tempPointer->next;
        }else{
            if(strncmp(str,tempPointer->data.word,4) == 0){
                printf("Found: %s \n",str);
                return;
            }else 
                tempPointer = tempPointer->next;
        }
    }
    //If no matches are found 
    printf("Mo Matches Found\n");
}
void nuke(){
    //Loops throught the Linked List
    while(head != NULL){
        tempPointer = head;
        head = head->next;
        //Frees the memoray alocation of each node;
        free(tempPointer);  
    }
    again = 0;
    system(clear); //Clears the Command Prompt
}
void printList(){
    tempPointer = head;
    printf("List: \n");
    //Loops through Linked List Printing the First 4 Letters of the word and the size of the word
    while(tempPointer != NULL){
        printf("%s %d\n",tempPointer->data.word,tempPointer->data.size);
        tempPointer = tempPointer->next;
    }
    printf("\n");
}
void insert(char* arr){
    memset(tempString,NULL,300);
    memset(tempEntry.word,NULL,5);
    tempEntry.size = 0;
    int i = 0,j = 0,q = 0;

    for(i = 0; i < strlen(arr); i++){
        //Checks to see if char is a space or new line
        if(arr[i] == ' ' || arr[i] == '\n'){
            //Empties the temp Entry and inserts new data into it 
            memset(tempEntry.word,NULL,5);
            tempEntry.size = strlen(tempString);
            strncpy(tempEntry.word,tempString,4);
            j = 0;
            //Creates a node to be added in the Linked List
            struct Node* tempNode = (struct Node*)malloc(sizeof(struct Node));
            tempNode->data = tempEntry;
            tempNode->next = NULL;

            if(head == NULL){
                head = tempNode;
            } else {
                tempPointer = head;
                struct Node *prevNode = NULL;
                while (tempPointer != NULL) {
                    q = strcmp(tempNode->data.word, tempPointer->data.word);
                    if (q > 0) {
                        if (tempPointer->next == NULL) {
                            tempPointer->next = tempNode;
                            break;
                        } else {
                            prevNode = tempPointer;
                            tempPointer = tempPointer->next;
                        }
                    } else {
                        if (prevNode == NULL) {
                            tempPointer = head;
                            head = tempNode;
                            tempNode->next = tempPointer;
                            break;
                        } else {
                            prevNode->next = tempNode;
                            tempNode->next = tempPointer;
                            break;
                        }
                    }
                }
            }
            memset(tempString, NULL, tempEntry.size);
        }else {
            if(isalpha(arr[i]) != 0)
                tempString[j] = arr[i];
            j++;
        }
    }
}
void menu(){
    //Clear the Input array
    memset(input, NULL, 300);
    //Clear the Command Prompt Screen 
    system(clear);
    //Print out the menu
    printf("Choose an option:\n");
    printf("1) Search for an Word\n");
    printf("2) Add more words\n");
    printf("3) Print List\n");
    printf("4) Delete and start over\n");
    //Get input from the User
    scanf("%d", &tempInt);
    switch (tempInt) {
        case 1:
            system(clear);
            printf("Enter a word to serach for: \n");
            scanf("%s", input);
            while ((getchar()) != '\n');
            printf("Search Case Sensitive (0) or Case Insensitive (1)\n");
            scanf("%d", &tempInt);
            search(input, tempInt);
            printf("Press Enter\n");
            while ((getchar()) != '\n');
            while ((getchar()) != '\n');
            break;
        case 2:
   
            system(clear);
            printf("Please Enter in a Sentence or Words: \n");
            while ((getchar()) != '\n');
            fgets(input, sizeof(input), stdin);
            //printf("%s", input);
            printf("New Words Added \n");
            printf("Press Enter\n");
            while ((getchar()) != '\n');
            break;
        case 3:
            system(clear);
            printList(head);
            printf("Press Enter\n");
            while ((getchar()) != '\n');
            while ((getchar()) != '\n');
            break;
            case 4:
            nuke();
            break;
        default:
            printf("Invaild Choice. Please Choose Again \n\n\n");
            break;
    }
}