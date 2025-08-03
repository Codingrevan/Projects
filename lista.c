#include "lista.h"

int i = 1;

int rand_i(int a, int b){
	return (a + rand() % (b - a + 1));
}

node* create(int key){
	node* new = malloc(sizeof(*new));
	if(new == NULL){
		printf("Za mało pamięci na stercie!\n");
		return NULL;
	}
	new -> value = key;
	new -> next = NULL;
	new -> prev = NULL;
	return new;
}

void print_list_next(node* head){
	if(head == NULL){
		printf("Lista jest pusta!\n");
		return;
	}
	for(node* tmp = head; tmp; tmp = tmp -> next){
		printf("Element nr. %d\n", i++);
		printf("Wartość: %d\n", tmp -> value);
		printf("Adres prev: %p\n", tmp -> prev);
		printf("Adres: %p\n", tmp);
		printf("Adres next: %p\n\n", tmp -> next);
	}
    i--;
	return;
}

void print_list_prev(node* head){
	if(head == NULL){
		printf("Lista jest pusta!\n");
		return;
	}
    node* tmp = head;
	for(; tmp -> next; tmp = tmp -> next);
    for(; tmp; tmp = tmp -> prev){
		printf("Element nr. %d\n", i--);
		printf("Wartość: %d\n", tmp -> value);
		printf("Adres prev: %p\n", tmp -> prev);
		printf("Adres: %p\n", tmp);
		printf("Adres next: %p\n\n", tmp -> next);
	}
    i++;
	return;
}

node* add_first(node* head, node* element){
	if(head == NULL)
		return element;
	element -> next = head;
	head -> prev = element;
	return element;
}

node* add_last(node* head, node* element){
	if(head == NULL)
		return element;
	node* tmp = head;
    for(; tmp -> next; tmp = tmp -> next);
    tmp -> next = element;
	element -> prev = tmp;
	return head;
}

node* pull_all_elements(node** head, int var){
	if(*head == NULL){
		printf("Lista jest pusta!\n");
		return NULL;
	}
	node* prev = (*head) -> prev;
	node* tmp = *head;
	node* next = (*head) -> next;
	node* newhead = NULL;
	while(tmp != NULL){
		if(tmp -> value == var){
			tmp -> next = tmp -> prev = NULL;
			newhead = add_first(newhead, tmp);
			if(prev == NULL){
				if(next != NULL){
					next -> prev = prev;
                    *head = next;
                }
				else{
			        *head = NULL;
                    return newhead;  
                }
			}
			else{
				if(next != NULL){
					prev -> next = next;
					next -> prev = prev;
				}
				else
					prev -> next = next;
			}
		}
		tmp = next;
		if(tmp != NULL){
			prev = tmp -> prev;
			next = tmp -> next;
		}
	}
	return newhead;
}

node* pull_one_element(node** head, int var){
	if(*head == NULL){
		printf("Lista jest pusta!\n");
		return NULL;
	}
	node* prev = (*head) -> prev;
	node* tmp = *head;
	node* next = (*head) -> next;
	while((tmp != NULL) && (tmp -> value != var)){
		tmp = next;
		if(tmp != NULL){
			prev = tmp -> prev;
			next = tmp -> next;
		}
	}
	if(tmp != NULL){
        if(tmp == *head) *head = next;
		if(prev != NULL) prev -> next = next;
		if(next != NULL) next -> prev = prev;
        tmp -> next = tmp -> prev = NULL;
		return tmp;
	}
	return NULL;
}

void add_sort(node** head, node* element){
	if(*head == NULL){
		*head = element;
		return;
	}
	node* tmp = *head;
	if(element -> value <= tmp -> value){
		*head = element;
		element -> next = tmp;
		tmp -> prev = element;
		return;
	}
	node* prev = tmp;
	tmp = tmp -> next;
	while(tmp != NULL){
		if(element -> value <= tmp -> value){
			prev -> next = element;
			element -> prev = prev;
			element -> next = tmp;
			tmp -> prev = element;
			return;		
		}
		prev = tmp;
		tmp = tmp -> next;
	}
	prev -> next = element;
	element -> prev = prev;
	return;			
}

void sort_divided(node** head){
    if((*head) -> next == NULL){
        return;
    }
    bool flag = false;
	node* tmphead = *head;
	node* tmpwstaw, *prevwstaw, *prev, *next;
	for(node* tmp = tmphead -> next; tmp; tmp = next){
		prev = tmp -> prev;
		next = tmp -> next;
		tmpwstaw = tmphead;
		prevwstaw = tmphead -> prev;
		if(tmp -> value % 2 == 0){
			while((tmpwstaw != NULL) && (tmpwstaw -> value % 2 == 0) && 
                  (tmpwstaw -> value <= tmp -> value)){
				prevwstaw = tmpwstaw;
				tmpwstaw = tmpwstaw -> next;
			}
            if(prevwstaw != tmp){
			    prev -> next = next;
			    if(next != NULL) next -> prev = prev;
			    if(prevwstaw == NULL){
				    tmphead = tmp;
				    tmp -> prev = NULL;
				    tmp -> next = tmpwstaw;
                    tmpwstaw -> prev = tmp;
                    flag = true;
			    }
			    else{
				    prevwstaw -> next = tmp;
				    tmp -> prev = prevwstaw;
				    if(tmpwstaw != NULL)
                        tmpwstaw -> prev = tmp;
				    tmp -> next = tmpwstaw;
			    }
            }
		}
		else{
            if(flag == false){
			    while((tmpwstaw != NULL) && (tmpwstaw -> value <= tmp -> value) &&
                      ((tmpwstaw -> value % 2 == 1) || (tmpwstaw -> value % 2 == -1))){
				    prevwstaw = tmpwstaw;
				    tmpwstaw = tmpwstaw -> next;
			    }
            }
            else{
			    while((tmpwstaw != NULL) && 
                      ((tmpwstaw -> value % 2 == 0) || (tmpwstaw -> value <= tmp -> value))){
				    prevwstaw = tmpwstaw;
				    tmpwstaw = tmpwstaw -> next;
			    }
            }
            if(prevwstaw != tmp){
			    prev -> next = next;
			    if(next != NULL) next -> prev = prev;
			    if(prevwstaw == NULL){
				    tmphead = tmp;
				    tmp -> prev = NULL;
				    tmp -> next = tmpwstaw;
                    tmpwstaw -> prev = tmp;
			    }
			    else{
				    prevwstaw -> next = tmp;
				    tmp -> prev = prevwstaw;
				    if(tmpwstaw != NULL)
                        tmpwstaw -> prev = tmp;
				    tmp -> next = tmpwstaw;
			    }
            }
		}
	}
    *head = tmphead;
	return;
}

void sort_notdivided(node** head){
    if((*head) -> next == NULL){
        return;
    }
    bool flag = false;
	node* tmphead = *head;
	node* tmpwstaw, *prevwstaw, *prev, *next;
	for(node* tmp = tmphead -> next; tmp; tmp = next){
		prev = tmp -> prev;
		next = tmp -> next;
		tmpwstaw = tmphead;
		prevwstaw = tmphead -> prev;
		if((tmp -> value % 2 == 1) || (tmp -> value % 2 == -1)){
			while((tmpwstaw != NULL) && (tmpwstaw -> value <= tmp -> value) &&
                  ((tmpwstaw -> value % 2 == 1) || (tmpwstaw -> value % 2 == -1))){
				prevwstaw = tmpwstaw;
				tmpwstaw = tmpwstaw -> next;
			}
            if(prevwstaw != tmp){
			    prev -> next = next;
			    if(next != NULL) next -> prev = prev;
			    if(prevwstaw == NULL){
				    tmphead = tmp;
				    tmp -> prev = NULL;
				    tmp -> next = tmpwstaw;
                    tmpwstaw -> prev = tmp;
                    flag = true;
			    }
			    else{
				    prevwstaw -> next = tmp;
				    tmp -> prev = prevwstaw;
				    if(tmpwstaw != NULL)
                        tmpwstaw -> prev = tmp;
				    tmp -> next = tmpwstaw;
			    }
            }
		}
		else{
            if(flag == false){
			    while((tmpwstaw != NULL) && (tmpwstaw -> value % 2 == 0) && 
                      (tmpwstaw -> value <= tmp -> value)){
				    prevwstaw = tmpwstaw;
				    tmpwstaw = tmpwstaw -> next;
			    }
            }
            else{
			    while((tmpwstaw != NULL) && ((tmpwstaw -> value % 2 == 1) ||  
                      (tmpwstaw -> value % 2 == -1) || (tmpwstaw -> value <= tmp -> value))){
				    prevwstaw = tmpwstaw;
				    tmpwstaw = tmpwstaw -> next;
			    }
            }
            if(prevwstaw != tmp){
			    prev -> next = next;
			    if(next != NULL) next -> prev = prev;
			    if(prevwstaw == NULL){
				    tmphead = tmp;
				    tmp -> prev = NULL;
				    tmp -> next = tmpwstaw;
                    tmpwstaw -> prev = tmp;
			    }
			    else{
				    prevwstaw -> next = tmp;
				    tmp -> prev = prevwstaw;
				    if(tmpwstaw != NULL)
                        tmpwstaw -> prev = tmp;
				    tmp -> next = tmpwstaw;
			    }
            }
		}
	}
    *head = tmphead;
	return;
}

void sort(node** head){
    if((*head) -> next == NULL){
        return;
    }
	node* tmphead = *head;
	node* tmpwstaw, *prevwstaw, *prev, *next;
	for(node* tmp = tmphead -> next; tmp; tmp = next){
		prev = tmp -> prev;
		next = tmp -> next;
		tmpwstaw = tmphead;
		prevwstaw = tmphead -> prev;
	    while((tmpwstaw != NULL) && (tmpwstaw -> value <= tmp -> value)){
		    prevwstaw = tmpwstaw;
			tmpwstaw = tmpwstaw -> next;
		}
        if(prevwstaw != tmp){
		    prev -> next = next;
		    if(next != NULL) next -> prev = prev;
		    if(prevwstaw == NULL){
			    tmphead = tmp;
			    tmp -> prev = NULL;
			    tmp -> next = tmpwstaw;
                tmpwstaw -> prev = tmp;
		    }
		    else{
			    prevwstaw -> next = tmp;
			    tmp -> prev = prevwstaw;
			    if(tmpwstaw != NULL)
                    tmpwstaw -> prev = tmp;
			    tmp -> next = tmpwstaw;
		    }
        }
	}
    *head = tmphead;
	return;
}

void free_list(node** head){
	node* tmp = NULL;
	while(*head != NULL){
		tmp = *head;
		*head = (*head) -> next;
		free(tmp);
	}
	tmp = NULL;
}


