#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "rooms.h"
#include "items.h"
#include "characters.h"

// Help command, prints table of commands
void help(){
	printf("\n******************************************************************************************\n\n");
	printf("   help              - Lists available commands\n\n");
	printf("   list              - Lists all rooms, characters and items\n\n");
	printf("   look              - Lists room in each direction of the room the player is in\n");
	printf("                       Lists items and characters in the room the player is in\n\n");
	printf("   go [DIRECTION]    - Moves player in certain direction (north,east,south,west)\n\n");
	printf("   take [ITEM]       - Picks up item in the room (if it's there) and stores in inventory\n\n");
	printf("   drop [ITEM]       - Drops item from inventory (if it's there) to the room\n\n");
	printf("   inventory         - Lists items in player's inventory\n\n");
	printf("   clue [CHARACTER]  - Brings character to the room the player is in\n");
	printf("                       Checks if current room is murder room\n");
	printf("                       Checks if murderer is in the room\n");
	printf("                       Checks if murder weapon is in the room or player's inventory\n");
	printf("                       1 'clue' is used (10 in total)\n\n");
	printf("******************************************************************************************\n\n");
}

// List command to list all rooms, characters, and items
void list(){
	printf("\n******************************************************\n");
	printf("   ROOMS           |  CHARACTERS    |  ITEMS\n");
	printf("                   |                |  \n");
	printf("   Bathroom        |  Butler        |  Knife\n");
	printf("   Study Room      |  Maid          |  Bloody Gloves\n");
	printf("   Kitchen         |  Chef          |  Hammer\n");
	printf("   Living Room     |  Gardener      |  Shovel\n");
	printf("   Family Room     |  Nanny         |  Gun\n");
	printf("   Dining Room     |                |  Broom\n");
	printf("   Bed Room        |                |\n");
	printf("   Closet          |                |\n");
	printf("   Foyer           |                |\n");
	printf("                   |                |  \n");
	printf("******************************************************\n\n");
}

// Look command to see rooms in each direction and items and characters in the room
void look(struct Room* current){
	printf("\n**************************************************\n\n");
	printf("   You are currently in the %s\n",getRoomName(current));
	printf("   You look around you\n\n");

	if(getNorth(current) == NULL){
		printf("   North of the %s is: Nothing\n",getRoomName(current));
	} else {printf("   North of the %s is: %s\n",getRoomName(current),getRoomName(getNorth(current)));}
	if(getWest(current) == NULL){
		printf("   West of the %s is: Nothing\n",getRoomName(current));
	} else {printf("   West of the %s is: %s\n",getRoomName(current),getRoomName(getWest(current)));}
	if(getEast(current) == NULL){
		printf("   East of the %s is: Nothing\n",getRoomName(current));
	} else {printf("   East of the %s is: %s\n",getRoomName(current),getRoomName(getEast(current)));}
	if(getSouth(current) == NULL){
		printf("   South of the %s is: Nothing\n",getRoomName(current));
	} else {printf("   South of the %s is: %s\n",getRoomName(current),getRoomName(getSouth(current)));}

	printf("\n   Items in the %s: ",getRoomName(current));

	struct Item* temp = getNextItem(getItems(current));
	while (temp != NULL){
		printf("%s; ",getItemName(temp));
		temp = temp->next;
	}
	
	printf("\n\n   Characters in the %s: ",getRoomName(current));

	struct Character* tempC = getNextChar(getCharacters(current));
	while (tempC != NULL){
		printf("%s; ",getCharName(tempC));
		tempC = tempC->nextChar;
	}
	printf("\n\n**************************************************\n\n");
}

// Inventory command to show whats in player's inventory
void showInventory(struct Character* avatar){
	struct Item* tempItem = getNextItem(inventory(avatar));
	printf("\n   Your Inventory: ");
	while(tempItem != NULL){
		printf("%s; ",getItemName(tempItem));
		tempItem = getNextItem(tempItem);
	}
	printf("\n\n**************************************************\n\n");
}

int main(){

	// Win condition checks
	int win = 0;
	int clues = 10;
	
	// Create 9 rooms
	struct Room* bathroom = room("bathroom",item("dummy"),character("dummy",item("dummy")));
	struct Room* study = room("study room",item("dummy"),character("dummy",item("dummy")));
	struct Room* kitchen = room("kitchen",item("dummy"),character("dummy",item("dummy")));
	struct Room* living = room("living room",item("dummy"),character("dummy",item("dummy")));
	struct Room* family = room("family room",item("dummy"),character("dummy",item("dummy")));
	struct Room* bedroom = room("bed room",item("dummy"),character("dummy",item("dummy")));
	struct Room* closet = room("closet",item("dummy"),character("dummy",item("dummy")));
	struct Room* foyer = room("foyer",item("dummy"),character("dummy",item("dummy")));
	struct Room* dining = room("dining room",item("dummy"),character("dummy",item("dummy")));

	// Create 5 characters
	struct Character* butler = character("butler",item("dummy"));
	struct Character* maid = character("maid",item("dummy"));
	struct Character* chef = character("chef",item("dummy"));
	struct Character* nanny = character("gardener",item("dummy"));
	struct Character* housekeeper = character("nanny",item("dummy"));
	struct Character* charArray[] = {butler,maid,chef,nanny,housekeeper};

	// Create avatar
	struct Character* avatar = character("Avatar",item("Inventory"));

	// Create 6 items
	struct Item* knife = item("knife");
	struct Item* gloves = item("bloody gloves");
	struct Item* shovel = item("shovel");
	struct Item* hammer = item("hammer");
	struct Item* pistol = item("gun");
	struct Item* broom = item("broom");
	struct Item* itemArray[] = {knife,gloves,shovel,hammer,pistol,broom};

	// Array of nine rooms to make the map
	struct Room* map[] = {bathroom,study,kitchen,living,family,bedroom,closet,foyer,dining};

	// Shuffle map
	srand(time(0));
	for(int i = 0; i < 9; i++){
		int index = rand()%9;

		struct Room* temp = map[i];
		map[i] = map[index];
		map[index] = temp;
	}

	// Link the rooms
	setEast(map[0],map[1]); setSouth(map[0],map[3]);
	setWest(map[1],map[0]); setEast(map[1],map[2]); setSouth(map[1],map[4]);
	setWest(map[2],map[1]); setSouth(map[2],map[5]);
	setNorth(map[3],map[0]); setEast(map[3],map[4]); setSouth(map[3],map[6]);
	setWest(map[4],map[3]); setNorth(map[4],map[1]); setSouth(map[4],map[7]); setEast(map[4],map[5]);
	setWest(map[5],map[4]); setNorth(map[5],map[2]); setSouth(map[5],map[8]);
	setNorth(map[6],map[3]); setEast(map[6],map[7]);
	setWest(map[7],map[6]); setEast(map[7],map[8]); setNorth(map[7],map[4]);
	setWest(map[8],map[7]); setNorth(map[8],map[5]);
	
	// Randomize character locations and add to rooms
	for(int i = 0; i < 5; i++){
		int index = rand()%9;
		// Add room to character
		setCharRoom(charArray[i],map[index]);
		// Add character to room
		addCharacter(getCharacters(map[index]), charArray[i]);
	}
		
	// Randomize item locations and add to rooms
	for(int i = 0; i < 6; i++){
		int index = rand()%9;
		// to ensure 1 item per room
		while(getItems(map[index])->next != NULL){
			index = rand()%9;
		}
		add_item(itemArray[i],getItems(map[index]));
	}

	// Randomize location of Avatar
	setCharRoom(avatar, map[rand()%9]);

	// Randomize winning set
	char* winSet[] = {getRoomName(map[rand()%9]),getCharName(charArray[rand()%5]),getItemName(itemArray[rand()%6])};

	// Introduction
	printf("\n   There has been a murder...\n   Find the room where the murder took place, the murderer, and the murder weapon to win\n");
	printf("   You have 10 clues, use them wisely...\n");
	printf("   You are currently in the %s\n",getRoomName(getCharRoom(avatar)));
	printf("   Enter 'help' at anytime to see table of commands\n");

	char *buffer;
  size_t bufsize = 32;

  buffer = (char *)malloc(bufsize * sizeof(char));
  if( buffer == NULL)
  {
    perror("Unable to allocate buffer");
    exit(1);
  }

  while(win == 0 && clues != 0){

		// Prompt player for a command
 		printf("   Enter a command: ");

		// Get input
    getline(&buffer,&bufsize,stdin);

		// Separate input into two parts
		char *command = strtok(buffer," ");
		char *object = strtok(NULL,"\n");
		//printf("You command: '%s'\n",command);
		//printf("You object: '%s'\n",object);


		// If input is 'quit' (for testing purposes)
		if(strcmp(command,"quit\n")==0 || strcmp(command,"quit")==0){
			win = 3;

			// If input is 'help'
		} else if(strcmp(command,"help\n")==0 || strcmp(command,"help")==0){
			help();

			// If input is 'list'
		} else if (strcmp(command,"list\n")==0 || strcmp(command,"list")==0){
			list();

			// If input is 'look'
		} else if (strcmp(command,"look\n")==0 || strcmp(command,"look")==0){
			look(getCharRoom(avatar));

			// If input is 'inventory'
		} else if (strcmp(command,"inventory\n")==0 || strcmp(command,"inventory")==0){
			showInventory(avatar);

			// If input is 'go'
		} else if (strcmp(command,"go\n")==0 || strcmp(command,"go")==0){

			// Check if direction is null
			if (object != NULL){

				// If direction is north
				if ((strcmp(object,"north\n")==0 || strcmp(object,"north")==0)){
					if(getNorth(getCharRoom(avatar)) == NULL){
						printf("\n   No room to the north\n\n");
					} else{
						setCharRoom(avatar, getNorth(getCharRoom(avatar)));
						printf("\n   You walk north\n");
						printf("   You enter the %s\n\n",getRoomName(getCharRoom(avatar)));
					}

					// If direction is west
				} else if ((strcmp(object,"west\n")==0 || strcmp(object,"west")==0)){
					if(getWest(getCharRoom(avatar)) == NULL){
						printf("\n   No room to the west\n\n");
					} else{
						setCharRoom(avatar, getWest(getCharRoom(avatar)));
						printf("\n   You walk west\n");
						printf("   You enter the %s\n\n",getRoomName(getCharRoom(avatar)));
					}

					// If direction is east
				} else if ((strcmp(object,"east\n")==0 || strcmp(object,"east")==0)){
					if(getEast(getCharRoom(avatar)) == NULL){
						printf("\n   No room to the east\n\n");
					} else{
						setCharRoom(avatar, getEast(getCharRoom(avatar)));
						printf("\n   You walk east\n");
						printf("   You enter the %s\n\n",getRoomName(getCharRoom(avatar)));
					}

					// If direction is south
				} else if ((strcmp(object,"south\n")==0 || strcmp(object,"south")==0)){
					if(getSouth(getCharRoom(avatar)) == NULL){
						printf("\n   No room to the south\n\n");
					} else{
						setCharRoom(avatar, getSouth(getCharRoom(avatar)));
						printf("\n   You walk south\n");
						printf("   You enter the %s\n\n",getRoomName(getCharRoom(avatar)));
					}

					// If direction is gibberish
				} else {
					printf("\n   Please enter a valid direction after 'go' (north,west,east,south)\n\n");
				}
			} else {
				printf("\n   Please enter a valid direction after 'go' (north,west,east,south)\n\n");
			}

			// If input is 'take'
		} else if (strcmp(command,"take\n")==0 || strcmp(command,"take")==0){

			// Check if item is null
			if (object != NULL){
				int itemCheck = 0;
				struct Item* tempItem = item("dummy");

				// If item exists then set tempItem to that item
				for(int i = 0; i<6; i++){
					if(strcmp(itemArray[i]->name,object)==0){
						tempItem = itemArray[i];
					}
				}

				// Attempt to remove item from room, returns 1 if successful, 0 if not
				itemCheck = drop_item(tempItem, getItems(getCharRoom(avatar)));

				// If removal from room was successful
				if(itemCheck == 1){
					printf("\n   You pick up the %s and store it in your inventory",getItemName(tempItem));
					add_item(tempItem, inventory(avatar));
					showInventory(avatar);

					// If item was not in the room
				} else {
					printf("\n   That object is not in the room\n   It could be in another room or in your inventory\n   Enter 'inventory' to check your inventory\n\n");
				}

				// If item was gibberish
			} else {
				printf("\n   Please enter a valid item. Enter 'list' to view the list of items\n\n");
			}

			// If input is 'drop'
		} else if (strcmp(command,"drop\n")==0 || strcmp(command,"drop")==0){
			
			// Check if item is null
			if (object != NULL){
				int itemCheck = 0;
				struct Item* tempItem = item("dummy");

				// If item exists then set tempItem to that item
				for(int i = 0; i<6; i++){
					if(strcmp(itemArray[i]->name,object)==0){
						tempItem = itemArray[i];
						itemCheck = 2;
					}
				}

				// Attempt to remove item from inventory, returns 1 if successful, 0 if not
				itemCheck = drop_item(tempItem, inventory(avatar));

				// If removal from inventory was successful
				if(itemCheck == 1){
					printf("\n   You drop the %s",getItemName(tempItem));
					add_item(tempItem, getItems(getCharRoom(avatar)));
					showInventory(avatar);

					// If item was not in the room
				} else {
					printf("\n   That object is not in your inventory\n   Enter 'inventory' to check your inventory\n\n");
				}

			// If item was gibberish
			} else {
				printf("\n   Please enter a valid item. Enter 'list' to view the list of items\n\n");
			}

			// If input is 'clue'
		} else if (strcmp(command,"clue\n")==0 || strcmp(command,"clue")==0){
			
			// Check if character is null
			if (object != NULL){
				int charCheck = 0;
				struct Character* tempChar;

				// If character exists then set tempChar to that character
				for(int i = 0; i<5; i++){
					if(strcmp(getCharName(charArray[i]),object)==0){
						tempChar = charArray[i];
						charCheck = 1;
					}
				}

				// Move character to room player is in
				if (charCheck == 1){
					move_character(getCharacters(getCharRoom(tempChar)), tempChar, getCharacters(getCharRoom(avatar)));
					setCharRoom(tempChar, getCharRoom(avatar));
					printf("\n   The %s is now in the %s\n",getCharName(tempChar),getRoomName(getCharRoom(avatar)));
				} else {
					printf("\n   Please enter a valid character name. Enter 'list' to view the list of characters\n\n");
					continue;
				}

				// Check for matches
				int roomMatch = 0;
				int charMatch = 0;
				int itemMatch = 0;
				
				// If room matches
				if(strcmp(winSet[0],getRoomName(getCharRoom(avatar))) == 0){
					printf("\n   Room Match: You are in the murder room...");
					roomMatch = 1;
				} else {
					// If room is not the murder room
					printf("\n   %s is NOT the murder room",getRoomName(getCharRoom(avatar)));
				}

				// If murderer is in the room
				struct Character* tempC = getNextChar(getCharacters(getCharRoom(avatar)));
				while(tempC != NULL){
					if(strcmp(winSet[1],getCharName(tempC)) == 0){
						printf("\n   Character Match: The murderer is in the room...");
						charMatch = 1;
						break;
					}
					tempC = tempC->nextChar;
				}
				// If murderer not in the room
				if(charMatch == 0){
					printf("\n   The murderer is NOT in the room");
				}

				// If murder weapon is in the room
				struct Item* tempI = getItems(getCharRoom(avatar));
				while(tempI != NULL){
					if(strcmp(winSet[2],getItemName(tempI)) == 0){
						printf("\n   Item Match: The murder weapon is in the room or your inventory...\n\n");
						itemMatch = 1;
						break;
					}
					tempI = tempI->next;
				}
				// If murder weapon is in player inventory
				tempI = inventory(avatar);
				while(tempI != NULL){
					if(strcmp(winSet[2],getItemName(tempI)) == 0){
						printf("\n   Item Match: The murder weapon is in the room or your inventory...\n");
						itemMatch = 1;
						break;
					}
					tempI = tempI->next;
				}
				// If murder weapon not in room or player inventory
				if(itemMatch == 0){
					printf("\n   The murder weapon is NOT in the room or your inventory\n");
				}

				// If all three matched
				if(roomMatch + charMatch + itemMatch == 3){
					win = 1;
				}

				clues -= 1;
				printf("   You have %i clues remaining...\n\n",clues);
				printf("******************************************\n\n");

			}	else {
				printf("\n   Please enter a valid character name. Enter 'list' to view the list of characters\n\n");
			}
		}
	}

	// If player matched room, character, and item correctly 
	if(win == 1){
		printf("   You WIN\n   The %s was the murder room\n   The %s was the murderer\n   The %s was the murder weapon\n\n\n",winSet[0],winSet[1],winSet[2]);

	// If player used up all their clues
	} else if (win == 3){
		printf("   You quit the game\n");

	// If player quit the game
	} else {
		printf("   You LOSE, you ran out of clues\n   The %s was the murder room\n   The %s was the murderer\n   The %s was the murder weapon\n\n\n",winSet[0],winSet[1],winSet[2]);
	}

	// Free memory
	for(int r = 0; r < 9; r++){
		free(map[r]);
		if(r<5){
			free(charArray[r]);
		}
		if(r<6){
			free(itemArray[r]);
		}
	}

	// End
	return 0;
}