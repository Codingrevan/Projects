#include "lista.h"

int main(void){

	srand(time(NULL));
	node* head = NULL;
	node* new = NULL;

    new = create(8);
	if(new != NULL) head = add_first(head, new);
	node* phead = pull_all_elements(&head, 8);
	print_list_next(phead);
    print_list_prev(phead);
    if(phead != NULL) free_list(&phead);
	print_list_next(head);
	print_list_prev(head);

    new = create(8);
	if(new != NULL) head = add_first(head, new);
    new = create(1);
	if(new != NULL) head = add_last(head, new);
    new = create(2);
	if(new != NULL) head = add_first(head, new);
	new = create(3);
	if(new != NULL) head = add_last(head, new); 
    new = create(8);
	if(new != NULL) head = add_first(head, new);
	new = create(8);
	if(new != NULL) head = add_last(head, new);
    
    new = NULL;
	print_list_next(head);
	print_list_prev(head);

	phead = pull_all_elements(&head, 8);
	print_list_next(phead);
    print_list_prev(phead);
    if(phead != NULL) free_list(&phead);
	print_list_next(head);
	print_list_prev(head);
	
    node* element = pull_one_element(&head, 3);
    if(element != NULL){
	    printf("Wyciągnięty element: %d\n", element -> value);
        free(element);
    }
	print_list_next(head);
	print_list_prev(head); 
    new = create(4);
	if(new != NULL) head = add_last(head, new);
   
    element = pull_one_element(&head, 1);
    if(element != NULL){
	    printf("Wyciągnięty element: %d\n", element -> value);
        free(element);
    }
	print_list_next(head);
	print_list_prev(head);	
    new = create(3);
	if(new != NULL) head = add_last(head, new);
    
    element = pull_one_element(&head, 2);
    if(element != NULL){
	    printf("Wyciągnięty element: %d\n", element -> value);
        free(element);
    }
    element = NULL;
	print_list_next(head);
	print_list_prev(head);
    new = create(1);
	if(new != NULL) head = add_last(head, new);

    new = create(6);
    if(new != NULL)
	    add_sort(&head, new);	
	print_list_next(head);
	print_list_prev(head);
	
    new = create(-1);
    if(new != NULL)
	    add_sort(&head, new);	
	print_list_next(head);
	print_list_prev(head);
    
	new = create(2);
    if(new != NULL)
	    add_sort(&head, new);	
    
    new = create(-2);
	if(new != NULL) head = add_last(head, new);
    new = create(7);
	if(new != NULL) head = add_first(head, new);
    
    sort_divided(&head);
	print_list_next(head);
	print_list_prev(head);
    
    sort_notdivided(&head);
	print_list_next(head);
	print_list_prev(head);
    
    sort(&head);
	print_list_next(head);
	print_list_prev(head);

    new = NULL;
	free_list(&head);
	return 0;
}
