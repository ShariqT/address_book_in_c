#include <stdio.h>
#include <string.h>


//available arguments to pass into the command line
// --list :  to list all of the addresses currently stored
// --edit <num> : to edit a particular saved addresses
// --new <string> : to add a new address to be saved

typedef struct {
	char name[20];
	char address[100];
	char city[20];
	char state[2];
	char zipcode[5];
} ADDRESS;

FILE *address_fp;

ADDRESS userAddresses[20];

void printHelpScreen();
void listFunction();
void newFunction(char inputString[]);
void editFunction( int index);

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
	address_fp = fopen("addresses.data", "r");
	char line[200];
	char name[20];
	char address[100];
	char city[20];
	char state[2];
	char zipcode[5];
	int i = 0;
	int commaCount = 0;
	int address_count = 0;
	int a;
	char c;
	if(address_fp == NULL){
		printf("Error! Can't open data file to read addresses. \n");
		return;
	}

		
	while( fgets(line, 200, address_fp) != 0){
	
		ADDRESS new_addy;
		
		for (a = 0 ; a < 200; a++){
			//first check to see if it is a comma
			if(line[a] == ','){
				commaCount++;
				i=0;
			}

			switch(commaCount){
				//this means we are in the first part of the string
				case 0:
					new_addy.name[i] = line[a];
					i++;
				break;
				case 1:
					if(line[a] != ','){
						new_addy.address[i] = line[a];
						i++;
					}
				break;
				case 2:
					if(line[a] != ','){
						new_addy.city[i] = line[a];
						i++;
					}
				break;
				case 3:
					if(line[a] != ','){
						new_addy.state[i] = line[a];
						i++;
					}
				break;
				case 4:
					if(line[a] != ','){
						new_addy.zipcode[i] = line[a];
						i++;
					}
				break;
			}
		}

		userAddresses[address_count] = new_addy;
		address_count++;
	}

	printf(" the first guy name is %s \n", userAddresses[0].address);

	printf(" the first guy name is %s \n", userAddresses[1].address);
	
}

void editFunction(int index){
	printf("editing %i", index);
}


void newFunction(char inputString[]){
	printf("the input string is %s", inputString);
}

