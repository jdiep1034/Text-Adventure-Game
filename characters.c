#include "characters.h"

// Character constructor
struct Character* character(char* name, struct Item* item){
	struct Character *pointerChar;
  pointerChar = (struct Character *) malloc(sizeof(struct Character));

	pointerChar->name = name;
	pointerChar->inventory = item;

	return pointerChar;
}

// Function to move character to a room upon clue command
void move_character(struct Character* roomFrom, struct Character* c, struct Character* roomTo){
	removeCharacter(roomFrom,c);
	addCharacter(roomTo, c);
}

// Function to set room character is in
void setCharRoom(struct Character* c, struct Room* room){
	c->currentRoom = room;
}

// Function to get room character is in
struct Room* getCharRoom(struct Character* c){
	return c->currentRoom;
}

// Function to get character name
char* getCharName(struct Character* c){
	return c->name;
}

// Function to get character's inventory (only for avatar)
struct Item* inventory(struct Character* c){
	return c->inventory;
}

// Function to get next character
struct Character* getNextChar(struct Character* c){
	return c->nextChar;
}

// Function to remove character from room
void removeCharacter(struct Character* roomCharList, struct Character* c){
		// Store head node 
    struct Character* prev = roomCharList;
		struct Character* temp = roomCharList->nextChar;
  
    // Search for the character to be deleted, keep track of the 
    // previous node to change 'prev->next' 
    while (temp != NULL && (temp->name != c->name)) 
    { 
      prev = temp; 
      temp = temp->nextChar; 
    }
  
    // Unlink the node from linked list 
    prev->nextChar = temp->nextChar; 
		temp->nextChar = NULL;
}

// Function to add character to room
void addCharacter(struct Character* roomCharList, struct Character* c){
	if(roomCharList->nextChar == NULL){
		roomCharList->nextChar = c;
	} else {
		addCharacter(roomCharList->nextChar,c);
	}
}