#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef CHAR_H
#define CHAR_H

// Struct representing characters
struct Character{
  char *name;
	struct Room *currentRoom;
	struct Item *inventory;
	struct Character *nextChar;
};

// Character constructor
struct Character* character(char* name, struct Item* item);

// Function to move character to a room upon clue command
void move_character(struct Character* roomFrom, struct Character* c, struct Character* roomTo);

// Function to set room character is in
void setCharRoom(struct Character* c, struct Room* room);

// Function to get room character is in
struct Room* getCharRoom(struct Character* c);

// Function to get character's inventory (only for avatar)
struct Item* inventory(struct Character* c);

// Function to get character name
char* getCharName(struct Character* c);

// Function to get next character
struct Character* getNextChar(struct Character* c);

// Function to remove character from room
void removeCharacter(struct Character* roomCharList, struct Character* c);

// Function to add character to room
void addCharacter(struct Character* roomCharList, struct Character* c);

#endif