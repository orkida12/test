#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char name[20];
    char surname[20];
    char dep[5];
    int status;
    float GPA;

    struct Student *next;
};


void printData(char *filename, struct Student *head, int status, char *dep)
{
    FILE *fp;
    fp=fopen(filename, "w");
    if(fp==NULL)
    {
        printf("Cannot open file2!");
        return;
    }

    while(head!=NULL)
    {
        if(head->status==1 && (strcmp(dep, head->dep)==0))
        {
            fprintf(fp, "%s %s %s %f\n", head->name, head->surname, head->dep, head->GPA);
        }
        head=head->next;

    }

    fclose(fp);
}
void calcAvg(float sum, struct Student *newSt)
{
    newSt->GPA=sum/3.0;
    if(newSt->GPA>=2.8)
        newSt->status=1;
    else
        newSt->status=0;
}

void getData(char *filename, struct Student **head)
{
    FILE *fp;
    fp=fopen(filename, "r");
    if(fp==NULL)
    {
        printf("File 1 does not exists!");
        return;
    }

    int n;
    float y1, y2, y3, sum;
    fscanf(fp, "%d", &n);

    struct Student *newnode, *prev;

    for(int i=0; i<n; i++)
    {
        newnode=(struct Student*)malloc(sizeof(struct Student));
        fscanf(fp,"%s%s%s", newnode->name, newnode->surname, newnode->dep);
        fscanf(fp,"%f%f%f", &y1, &y2, &y3);
        newnode->next=NULL;
        sum=y1+y2+y3;

        calcAvg(sum, newnode);
        //check if the modifications done in  calcAvg are saved
        //printf("%f %d     ", newnode->GPA, newnode->status);

        if(*head==NULL)
        {
            *head=newnode;
        }
        else
        {
            prev->next=newnode;
        }
        prev=newnode;
    }

    fclose(fp);
}

int main(int argc, char *argv[])
{
    if(argc<5)
    {
        printf("Not enough arguments!");
        return 0;
    }
    else if(argc>5)
    {
        printf("Too many arguments!");
        return 0;
    }


    int status = atoi(argv[4]);
    struct Student *head=NULL;

    getData(argv[1], &head);
    printData(argv[2], head, status, argv[3]);

    /*
        ///prints the number of arguments
        printf("%d\n", argc);
        ///prints the actual arguments in char array format
        for(int i=0; i<argc; i++)
            printf("%s ", argv[i]);*/

    return 0;
}