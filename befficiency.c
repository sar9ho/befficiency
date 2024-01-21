#include <stdio.h>
#include <stdlib.h>
#include <cstring>


const char* format_in = "(%s, %d, %c)";

typedef struct BuildEff{
    char name[63];
    int sqrft;
    float annualelec;
    struct BuildEff *next;
    float ratio;

}BuildEff;

// COMPARATOR 
bool comp(BuildEff* firstn, BuildEff* secn){
    if(firstn -> ratio != secn -> ratio){
        return firstn -> ratio > secn -> ratio;
    }
    else if(strcmp(firstn -> name, secn ->name) < 0){
        return true;
    }
        return false;
    }

// DOES THE ACTUAL INSERTION SORT
BuildEff* insertsorted(struct BuildEff* head, struct BuildEff* newnode){
    if(head == NULL){
        return newnode;
    }
    //newnode before head
    if(comp(newnode,head)){
        newnode ->next = head;
        return newnode;
    }
    
    BuildEff* current = head;
    BuildEff* previous = NULL;
    while((current != NULL) && (comp(current, newnode))){ //if current is bigger or comes first
        previous = current;
        current = current -> next;
    }
    if(current == NULL){
        previous -> next = newnode;
    }
    else{
        previous -> next = newnode;
        newnode -> next = current;
    }
    return head;
}

//ITERATES OVER LINKED LIST ------------

BuildEff* sortList(BuildEff* head){
    struct BuildEff* sorted = NULL; //initialize sorted version
    struct BuildEff* current = head; 
    while(current != NULL){
        BuildEff* new_node = insertsorted(sorted, current);
        sorted = new_node;
    
       // struct BuildEff* next = current -> next;
        current = current -> next;
    }
    //head = sorted;
    return sorted;
}


//MAIN----------------------

int count =0;


int main(int argc, char *argv[]) {
   
    FILE *file = fopen(argv[1], "r");  //getting file from user input
    struct BuildEff* head = NULL;      //setting head

    if(file == NULL){
        printf("error opening file");    //IF FILE IS NULL
        return 1;
    }
        //READING FILE AND SAVING THE INFO -------------------------------------------------------------------------------------------
    while(!feof(file)){     //WHILE NOT AT EOF -- How to specify when reached "DONE" ??
        struct BuildEff* newb = (struct BuildEff*)malloc(sizeof(struct BuildEff)); //ALLOCATE MEMORY TO NEW STRUCT
        newb -> next = NULL; 
        char newname[63];
        int newsqr;
        float newannual;
        fscanf(file, "%s", newname);
        if(strcmp(newname, "DONE") == 0 && count == 0){
            printf("BUILDING FILE IS EMPTY");
        }
        if(strcmp(newname, "DONE") == 0){
            free(newb);
            break;
        }
        else{
        fscanf(file, "%d", &newsqr);   
        fscanf(file, "%f", &newannual);  //READ FILE, SAVE INFORMATION INTO NEW VARIABLES
//if efficency or sqrft is 0
        float newratio;
        if(newannual == 0){
            newratio = 0;
        }
        if(newsqr == 0){
            newratio = 0;
        }
        else{
        newratio = (float)newannual/newsqr; 
        }
      //SAVING INFO INTO STRUCT-----------------------------------------------------------------------------------------------
        strcpy(newb -> name, newname);                                          //SAVE NAME INFORMATION INTO STRUCT
        newb -> sqrft = newsqr;                                                //SAVE SQRT INFORMATION INTO STRUCT
        newb -> annualelec = newannual;                                       //SAVE ANNUAL ELECTRICITY INTO STRUCT
        newb -> ratio = newratio;

        head = insertsorted(head,newb);
        }
        count++;
        }   
        fclose(file);
    while(head != NULL){
        printf("%s %f\n", head ->name, head ->ratio);
        struct BuildEff* temp = head->next;
        free(head);
        head = temp;
    }
    return EXIT_SUCCESS;
    }