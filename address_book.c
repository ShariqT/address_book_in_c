#include <stdio.h>
#include <string.h>
const char *dataFile = "addresses.dat";
typedef struct{
	char *name;
	char *address;
	char *city;
	char *state;
	int  zipcode;
} ADDRESS_ENTRY;

ADDRESS_ENTRY createNewAddress(char name[], char address_line1[], char address_line2[]);
void readDataLine(FILE *addresses_from_file);
void initMenu(int contacts);
int checkAnswer(char answer[]);
void addNewContact();

int num_of_contacts;
//we hold 20 addresses at one time for v1
ADDRESS_ENTRY my_addresses[20];

int main(){
	FILE *addresses_from_file;

	//let's check to see if we have addresses in the data file
	num_of_contacts = 0;	
	if( (addresses_from_file = fopen(dataFile, "r")) == NULL){
		//the addresses file doesn't exist, this is the first time the 
		//user is using this thing
		initMenu(num_of_contacts);
	}else{
		//we have some addresses, let's put them into structs
		readDataLine(addresses_from_file);
		initMenu(num_of_contacts);
	}

}

void initMenu(int contacts){
	char answer[1];
	printf("\n");
	printf("You can edit entries by pressing 'E' \n");
	printf("You can create new entries by pressing 'N' \n");
	printf("Total number of contacts: %i \n", contacts);
	scanf("%s", answer);
	if( checkAnswer(answer) == 0 ){
		printf("That is not a recoginzed command!");
		initMenu(contacts);
	}else{
		switch(answer[0]){
			case 'E':
				printf("We are doing the editing function");
			break;
			case 'N':
				printf("We are doing the new function");
				addNewContact();
			break;
		}
	}
}


void addNewContact(){
	printf("Adding a new contact. \n");
	printf("Enter name: ");
	
}

int checkAnswer(char answer[]){
	if((char) answer[0] != 'E' && (char) answer[0] != 'N'){
		return 0;
	}else{
		return 1;
	}
}


void readDataLine(FILE *addresses_from_file){
	char line[100];
	char addyline1[100];
	char addyline2[100];
	char name[100];
	int i = 0;
	while( (fgets(line, 100, addresses_from_file)) != 0){
		sscanf(line, "%[^\t\n] %[^\t\n] %[^\t\n]", name, addyline1, addyline2);
		my_addresses[i] = createNewAddress(name, addyline1, addyline2);
		num_of_contacts++;
	}
}

ADDRESS_ENTRY createNewAddress(char name[], char addyline1[], char addyline2[]){
	ADDRESS_ENTRY new_address;
	char city[100];
	char state[10];
	char zip[5];
	char fun_name[100];

	new_address.name = name;
	new_address.address = addyline1;

	sscanf(addyline2, "%[^,\n\t],%[^,\n\t],%[^\n\t]", city, state, zip );
	new_address.city = city;
	new_address.state = state;
	new_address.zipcode = (int)zip;
}