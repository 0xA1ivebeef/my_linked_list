
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_node
{
	size_t 			val;
	struct s_node* 	next;
} t_node;

/*
 * interface
t_node* create_node(size_t val);
void populate(t_node* head, int node_c);
void reverse_node_list(t_node* head);
void sort_node_list(t_node* head);
*/

void dump_list(t_node* head);
void free_linked_list(t_node* head);

static t_node* head = NULL;

t_node* create_node(size_t val)
{
	t_node* res = (t_node*)malloc(sizeof(t_node));
	if (!res)
	{
		printf("ERROR: create_node malloc failed\n");
		exit(EXIT_FAILURE);
	}	
	res->val = val;
	return res;
}

void populate(t_node* head, int node_c)
{
	if (!head)
	{
		printf("ERROR: populate invalid head, create_node head first\n");
		return;
	}

	t_node* curr = head;
	int i = 0;
	while (i < node_c)
	{
		t_node* new_node = create_node(rand()%100);
		if (!new_node)
		{
			printf("ERROR: populate malloc failed\n");
			free_linked_list(head);
			exit(EXIT_FAILURE);
		}

		// link new node
		curr->next = new_node;
		curr = new_node;

		++i;
	}
}

void free_linked_list(t_node* head)
{
	t_node* curr = head;
	t_node* tmp = NULL;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}

void dump_node(t_node* n) 
{
    if (n)
        printf("DUMP NODE: %p, val: %ld, next:%p\n", n, n->val, n->next);
}

void dump_list(t_node* head)
{
	t_node* curr = head;
	while (curr)
	{
		printf("%p, val: %ld\n", curr, curr->val);
		curr = curr->next;
	}
}

t_node* reverse_node_list(t_node* head)
{
    if (!head || !head->next)
        return head;

    // three ptr
    t_node* prev = NULL;
    t_node* curr = head;
    t_node* tmp;

    // using a stack is also possible and very intuitive but not optimal
    while (curr)
    {
        // point back from curr.next to prev
        tmp = curr->next;
        curr->next = prev;

        // step
        prev = curr; 
        curr = tmp; 
    }

    return prev;
}

// !!! this function mutates the given linked list
t_node* split(t_node* head)
{
    if (!head || !head->next)
    {
        fprintf(stderr, "split: head invalid or single node\n");
        return NULL; // cant be split
    }

    t_node* slow = head;
    t_node* fast = head->next; 

    // when fast reaches end, slow is at half
    while (fast && fast->next)
    {
        slow = slow->next; 
        fast = fast->next->next;
    }

    t_node* tmp = slow->next;
    slow->next = NULL; // NULL terminate list
    return tmp; // return node where split has to happen
}

t_node* merge_sort_node_list(t_node* head)
{
    if (!head || !head->next)
    {
        printf("mergesort return head back single node list or NULL\n");
        return head; // single node
    }

    t_node* mid = split(head);

    t_node* left = merge_sort_node_list(head);
    t_node* right = merge_sort_node_list(mid);
    
    t_node dummy = {0, NULL};
    t_node* tail = &dummy;
    while (left && right)
    {
        if (left->val <= right->val)
        {
            tail->next = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right = right->next; 
        }
        tail = tail->next;
    }

    tail->next = left ? left : right;

    return dummy.next;
}

int main()
{
	srand(69); // time(0));

	head = create_node(42);
	populate(head, 2);

	printf("original: \n");
	dump_list(head);	

	head = reverse_node_list(head);
	printf("reversed: \n");
	dump_list(head);	

    merge_sort_node_list(head);
	printf("sorted: \n");
	dump_list(head);	

	free_linked_list(head);

	return 0;
}
