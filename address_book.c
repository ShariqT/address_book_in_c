#include <stdio.h>
#include <string.h>
#include <ctype.h>


//available arguments to pass into the command line
// --list :  to list all of the addresses currently stored
// --edit <num> : to edit a particular saved addresses
// --new <string> : to add a new address to be saved

typedef struct {
	char name[20];
	char address[100];
	char city[20];
	char state[3];
	char zipcode[6];
} ADDRESS;

FILE *address_fp;

ADDRESS userAddresses[20];
int address_count = 0;
void printHelpScreen();
void listFunction();
void newFunction(char inputString[]);
void editFunction( int index);
void printUserAddresses();
char str_slice(char input[], int start, int stop);
ADDRESS createAddressEntry( char line[]);

int main(int argc, char *argv[]){
	if(argc != 1){
		//we'll only have three arguments at most, so let's check for that
		if(argc > 3){
			printf("Too many arguments! \n");
			return 1;
		}

		if( strcmp(argv[1], "--list") == 0){
			if(argc == 3){
				printf("--list flag does not take arguments! \n");
				return 1;
			}

			listFunction();
		}

		if( strcmp(argv[1], "--edit") == 0){
			if( isdigit(*argv[2]) == 0 ){
				printf("--edit flag argument needs to be a number! \n");
				return 1;
			}

			editFunction( atoi(argv[2]) );
		}

		if( strcmp(argv[1], "--new") == 0){
			if(isalpha(*argv[2]) == 0){
				printf("--new flag argument needs to be letters and numbers! \n");
			}

			newFunction(argv[2]);
		}


	}else{
		printHelpScreen();
	}

}

void printHelpScreen(){
	printf("These are the available commands for address book. \n");
	printf("\t \t --list : to list all of the addresses currently saved \n");
	printf("\t \t --edit <number> : to edit a particular saved address \n");
	printf("\t \t --new <address_string> : to add a new address to be saved \n");
	printf("A valid address string will be comma separated with no spaces \n");
	printf("An example of a address string is John Doe,1234 Anytown Street,New York,NY,12345");
}

void listFunction(){
	address_fp = fopen("addresses.dat", "r");
	char line[100];
	if(address_fp == NULL){
		printf("Error! Can't open data file to read addresses. \n");
		return;
	}

		
	while( fgets(line, 100, address_fp) != 0){
		userAddresses[address_count] = createAddressEntry(line);
		address_count++;
	}
	printf("%s \n", userAddresses[0].state);
	printUserAddresses();
	
}

void editFunction(int index){
	printf("editing %i", index);
}


void newFunction(char inputString[]){
	printf("the input string is %s", inputString);
}


void printUserAddresses(){
	int i;
	for(i = 0; i < address_count; i++){
		printf("%i) %s, %s, %s, %s %s \n", i, userAddresses[i].name, userAddresses[i].address, 
											userAddresses[i].city, userAddresses[i].state, 
											userAddresses[i].zipcode);
	}

	return;
}

ADDRESS createAddressEntry(char line[]){
	char name[20];
	char address[100];
	char city[20];
	char state[3];
	char statetmp[2];
	char zipcode[6];
	int a,b = 100;
	ADDRESS new_addy;

		sscanf(line, "%[^','\t\n],%[^','\t\n],%[^','\t\n],%[^','\t\n],%[^','\t\n]", name, address, city, statetmp, zipcode);
		
		//this is a noob hack because scanf was reading way more information than
		//I wanted, so I just sliced out the first two elements of what came from sscanf
		//and put it in another variable to copy over to the new_addy struct
		state[0] = statetmp[0];
		state[1] = statetmp[1];
		state[2] = '\0';
		
		strcpy(new_addy.name, name);
		strcpy(new_addy.address, address);
		strcpy(new_addy.city, city);
		strcpy(new_addy.state, state);
		strcpy(new_addy.zipcode, zipcode);
	return new_addy;
}

