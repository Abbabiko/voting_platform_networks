#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct Voter {
    int voterID;
    char name[50];
    int hasVoted;
};

struct Candidate {
    int candidateID;
    char name[50];
    char position[50];
    int votes;
};

struct Vote {
    int voterID;
    int candidateID;
};

int electionStarted = 0;

/* FUNCTION DECLARATIONS */

void adminMenu();
void voterMenu();
void registerVoter();
void registerCandidate();
void displayCandidates();
void displayPositions();
void vote();
void tallyVotes();
int checkVoter(int id);
int checkCandidate(int id);

/* MAIN FUNCTION */

int main() {

    int choice;

    while(1){

        printf("\n===== SONU ELECTRONIC VOTING SYSTEM =====\n");
        printf("1. Admin Menu\n");
        printf("2. Voter Menu\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                adminMenu();
                break;

            case 2:
                voterMenu();
                break;

            case 3:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

/* ADMIN MENU */

void adminMenu(){

    int choice;

    while(1){

        printf("\n---- ADMIN MENU ----\n");
        printf("1. Register Candidate\n");
        printf("2. View Candidates\n");
        printf("3. Start Election\n");
        printf("4. End Election\n");
        printf("5. View Results\n");
        printf("6. Back\n");

        scanf("%d",&choice);

        switch(choice){

            case 1:
                registerCandidate();
                break;

            case 2:
                displayCandidates();
                break;

            case 3:
                electionStarted = 1;
                printf("Election Started\n");
                break;

            case 4:
                electionStarted = 0;
                printf("Election Ended\n");
                break;

            case 5:
                tallyVotes();
                break;

            case 6:
                return;

            default:
                printf("Invalid option\n");
        }
    }
}

/* VOTER MENU */

void voterMenu(){

    int choice;

    while(1){

        printf("\n---- VOTER MENU ----\n");
        printf("1. Register Voter\n");
        printf("2. Vote\n");
        printf("3. Back\n");

        scanf("%d",&choice);

        switch(choice){

            case 1:
                registerVoter();
                break;

            case 2:
                vote();
                break;

            case 3:
                return;

            default:
                printf("Invalid choice\n");
        }
    }
}

/* REGISTER VOTER */

void registerVoter(){

    struct Voter v;
    FILE *fp;

    fp = fopen("voters.dat","ab");

    printf("Enter Voter ID: ");
    scanf("%d",&v.voterID);

    if(checkVoter(v.voterID)){
        printf("Voter already exists\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf("%s",v.name);

    v.hasVoted = 0;

    fwrite(&v,sizeof(v),1,fp);

    fclose(fp);

    printf("Voter Registered Successfully\n");
}

/* REGISTER CANDIDATE */

void registerCandidate(){

    struct Candidate c;
    FILE *fp;

    fp = fopen("candidates.dat","ab");

    printf("Enter Candidate ID: ");
    scanf("%d",&c.candidateID);

    if(checkCandidate(c.candidateID)){
        printf("Candidate already exists\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf("%s",c.name);

    printf("Enter Position: ");
    scanf("%s",c.position);

    c.votes = 0;

    fwrite(&c,sizeof(c),1,fp);

    fclose(fp);

    printf("Candidate Registered\n");
}

/* DISPLAY CANDIDATES */

void displayCandidates(){

    struct Candidate c;
    FILE *fp;

    fp = fopen("candidates.dat","rb");

    if(fp==NULL){
        printf("No candidates found\n");
        return;
    }

    printf("\nID\tName\tPosition\tVotes\n");

    while(fread(&c,sizeof(c),1,fp)){
        printf("%d\t%s\t%s\t%d\n",c.candidateID,c.name,c.position,c.votes);
    }

    fclose(fp);
}

/* CHECK VOTER */

int checkVoter(int id){

    struct Voter v;
    FILE *fp;

    fp = fopen("voters.dat","rb");

    if(fp==NULL)
        return 0;

    while(fread(&v,sizeof(v),1,fp)){

        if(v.voterID==id){
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* CHECK CANDIDATE */

int checkCandidate(int id){

    struct Candidate c;
    FILE *fp;

    fp = fopen("candidates.dat","rb");

    if(fp==NULL)
        return 0;

    while(fread(&c,sizeof(c),1,fp)){

        if(c.candidateID==id){
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* VOTING FUNCTION */

void vote(){

    if(!electionStarted){
        printf("Election has not started\n");
        return;
    }

    int voterID;
    int candidateID;

    struct Voter v;
    struct Candidate c;

    FILE *vf;
    FILE *cf;

    printf("Enter Voter ID: ");
    scanf("%d",&voterID);

    vf = fopen("voters.dat","rb+");

    while(fread(&v,sizeof(v),1,vf)){

        if(v.voterID==voterID){

            if(v.hasVoted){
                printf("You already voted\n");
                fclose(vf);
                return;
            }

            displayCandidates();

            printf("Enter Candidate ID: ");
            scanf("%d",&candidateID);

            cf = fopen("candidates.dat","rb+");

            while(fread(&c,sizeof(c),1,cf)){

                if(c.candidateID==candidateID){

                    c.votes++;

                    fseek(cf,-sizeof(c),SEEK_CUR);
                    fwrite(&c,sizeof(c),1,cf);

                    v.hasVoted = 1;

                    fseek(vf,-sizeof(v),SEEK_CUR);
                    fwrite(&v,sizeof(v),1,vf);

                    printf("Vote Cast Successfully\n");

                    fclose(cf);
                    fclose(vf);
                    return;
                }
            }

            printf("Candidate not found\n");

            fclose(cf);
            fclose(vf);
            return;
        }
    }

    printf("Voter not found\n");

    fclose(vf);
}

/* TALLY RESULTS */

void tallyVotes(){

    struct Candidate c;
    FILE *fp;

    int maxVotes = -1;
    char winner[50];

    fp = fopen("candidates.dat","rb");

    if(fp==NULL){
        printf("No candidates\n");
        return;
    }

    printf("\n---- RESULTS ----\n");

    while(fread(&c,sizeof(c),1,fp)){

        printf("%s (%s) : %d votes\n",c.name,c.position,c.votes);

        if(c.votes > maxVotes){
            maxVotes = c.votes;
            strcpy(winner,c.name);
        }
    }

    printf("\nWinner: %s with %d votes\n",winner,maxVotes);

    fclose(fp);
}