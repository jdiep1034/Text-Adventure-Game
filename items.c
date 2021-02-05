#include "items.h"

// Item constructor
struct Item* item(char* itemName){
	struct Item *pointerItem;
  pointerItem = (struct Item *) malloc(sizeof(struct Item));

	pointerItem->name = itemName;

	return pointerItem;
}

// Function to get item name
char* getItemName(struct Item* item){
	return item->name;
}

// Function to get next item
struct Item* getNextItem(struct Item* item){
	return item->next;
}

// Function to add item to linked list, room item list or avatar inventory
void add_item(struct Item* item, struct Item* list){
	if(list->next == NULL){
		list->next = item;
	} else {
		add_item(item,list->next);
	}
}

// Funciton to remove item from linked list, room item list or avatar inventory
int drop_item(struct Item* item, struct Item* list){
	// Store head node 
  struct Item* prev = list;
	struct Item* temp = list->next;
	
	// If nextItem is not NULL
	if (temp != NULL){
		// If name is not equal
		if(temp->name != item->name){
			// Call again further down list
			return drop_item(item,temp);
			// Else unlink node
		} else if (temp->name == item->name){
			prev->next = temp->next;
			temp->next = NULL;
			return 1;
		}
	}
	return 0;
}