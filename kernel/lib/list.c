#include	"../kernel.h"
//#include	"list.h"


struct	hlist_head {
	struct hlist_node	*first;
};

struct	hlist_node {
	struct hlist_node	*next, **pprev;
};


void	hlist_add_before(
		struct hlist_node	*n,
		struct hlist_node	*next)
{
	n->pprev = next->pprev;
	n->next = next;
	next->pprev = &n->next;
}


void	hlist_remove(
		struct hlist_node	*n)
{
	struct hlist_node	*next = n->next;
	struct hlist_node	**pprev = n->pprev;
	*pprev = next;
	if (next != NULL)
		next->pprev = pprev;
}


struct	node {
	struct node	*next;
};


void	add_node(
		struct node	*prev,
		struct node	*n)
{
	n->next = prev->next;
	prev->next = n;
}


#define	remove_node(n)	__remove_node((n)->prev)


void	__remove_node(
		struct node	*prev)
{
	prev->next = prev->next->next;
}


struct node	*endof_list(
		struct node	*head)
{
	struct node	*curr;
	for (curr = head->next; curr->next != NULL; curr = curr->next);
	return	curr;
}
/*struct node	*add_node(
		struct node	*list,
		struct node	*node)
{
	node->next = list->next;
	list->next = node;
}*/


