#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef ITEM_H
#define ITEM_H

// Struct representing items
struct Item{
  char *name;
	struct Item *next;
};

// Item constructor
struct Item* item(char* itemname);

// Function to get item name
char* getItemName(struct Item* item);

// Function to get next item
struct Item* getNextItem(struct Item* item);

// Function to add item to linked list, room item list or avatar inventory
void add_item(struct Item* item, struct Item* list);

// Funciton to remove item from linked list, room item list or avatar inventory
int drop_item(struct Item* item, struct Item* list);

#endif