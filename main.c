
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_node
{
	size_t 			val;
	struct s_node* 	next;
} t_node;

// interface
t_node* create_node(size_t val);
void populate(t_node* head, int node_c);
void free_linked_list(t_node* head);
void dump_list(t_node* head);
void reverse_node_list(t_node* head);
void sort_node_list(t_node* head);

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

void dump_list(t_node* head)
{
	t_node* curr = head;
	while (curr)
	{
		printf("%p, val: %ld\n", curr, curr->val);
		curr = curr->next;
	}
}

void reverse_node_list(t_node* head)
{
	// TODO implement

}

void sort_node_list(t_node* head)
{
	// TODO implement
}

int main()
{
	srand(69); // time(0));

	head = create_node(42);
	populate(head, 20);

	printf("original: \n");
	dump_list(head);	

	reverse_node_list(head);
	printf("reversed: \n");
	dump_list(head);	

	sort_node_list(head);
	printf("sorted: \n");
	dump_list(head);	

	free_linked_list(head);

	return 0;
}
