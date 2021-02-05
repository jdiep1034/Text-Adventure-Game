#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef ROOM_H
#define ROOM_H

// Struct representing rooms
struct Room{
	char* name;
  struct Room *n;
	struct Room *e;
	struct Room *s;
	struct Room *w;
	struct Item *items;
	struct Character *characters;
};

// Room constructor
struct Room* room(char* roomName, struct Item* item, struct Character* c);

// Function to set name of a room
void setRoomName(struct Room* current, char* roomName);

// Function to set north room
void setNorth(struct Room* current, struct Room* north);

// Function to set east room
void setEast(struct Room* current, struct Room* east);

// Function to set south room
void setSouth(struct Room* current, struct Room* south);

// Function to set west room
void setWest(struct Room* current, struct Room* west);

// Function to set item
void setItem(struct Room* current, struct Item* item);

// Function to return room name
char* getRoomName(struct Room* current);

// Function to return north room name
struct Room* getNorth(struct Room* current);

// Function to return east room name
struct Room* getEast(struct Room* current);

// Function to return south room name
struct Room* getSouth(struct Room* current);

// Function to return west room name
struct Room* getWest(struct Room* current);

// Function to return itemlist in the room
struct Item* getItems(struct Room* current);

// Function to return characters in the room
struct Character* getCharacters(struct Room* current);

// Function to remove character from room
void removeCharacter(struct Character* roomCharList, struct Character* c);

// Function to add character to room
void addCharacter(struct Character* roomCharList, struct Character* c);

#endif