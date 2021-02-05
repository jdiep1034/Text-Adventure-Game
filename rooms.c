#include "rooms.h"

// Room constructor
// param roomName: char* representing room name
struct Room* room(char* roomName, struct Item* item, struct Character* c){
	struct Room *pointerRoom;
  pointerRoom = (struct Room *) malloc(sizeof(struct Room));

	pointerRoom->name = roomName;
	pointerRoom->items = item;
	pointerRoom->characters = c;

	return pointerRoom;
}

// Function to set north room
void setNorth(struct Room* current, struct Room* north){
	current->n = north;
}

// Function to set east room
void setEast(struct Room* current, struct Room* east){
	current->e = east;
}

// Function to set south room
void setSouth(struct Room* current, struct Room* south){
	current->s = south;
}

// Function to set west room
void setWest(struct Room* current, struct Room* west){
	current->w = west;
}

// Function to return room name
char* getRoomName(struct Room* current){
	return current->name;
}

// Function to return north room name
struct Room* getNorth(struct Room* current){
	return current->n;
}

// Function to return east room name
struct Room* getEast(struct Room* current){
	return current->e;
}

// Function to return south room name
struct Room* getSouth(struct Room* current){
	return current->s;
}

// Function to return west room name
struct Room* getWest(struct Room* current){
	return current->w;
}

// Function to return itemlist in the room
struct Item* getItems(struct Room* current){
	return current->items;
}

// Function to return characters in the room
struct Character* getCharacters(struct Room* current){
	return current->characters;
}
