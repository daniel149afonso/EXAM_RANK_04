#include <stdio.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int accept(char **s, char c)
{
    if (**s)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

int atonbr(char c)
{
	switch (c)
	{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		default:
			break;
	}
	return (-1);
}
int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return i;	
}

void	ft_putnode(node *n)
{
	if (!n)
		return;
	ft_putnode(n->l);
	if (n->type == VAL)
		printf("%d ", n->val);
	else if (n->type == ADD)
		printf("+ ");
	else if (n->type == MULTI)
		printf("* ");
	ft_putnode(n->r);
}

/* MODIFIED: parse_expr initialise un pointeur local et vérifie la fin de la chaîne */
node *parse_expr(char *s)
{
	
	node *ret = malloc(sizeof(node));
	if (!ret)
		return NULL;
	ret->r = NULL;
	ret->l = NULL;
	if (!s) 
	{
		printf("Bonjour\n");
		destroy_tree(ret);
		return (NULL);
	}

	int len = ft_strlen(s);
	node *tmp = ret;
	int i = 0;
	
	while (i < len)
	{
		if (s[i + 1])
			ret->r = malloc(sizeof(node));
		else
			ret->r = NULL;
		if (isdigit(s[i]))
		{
			ret->type = VAL;
			ret->val = atonbr(s[i]);
		}
		else
		{
			if (s[i] == '+')
				ret->type = ADD;
			else if (s[i] == '*')
				ret->type = MULTI;
			else
			{
				unexpected(s[i]);
				return NULL;
			}
		}
		ret = ret->r;
		i++;
	}
	
	return tmp;
}

int eval_tree(node *tree)
{
	switch (tree->type) {
		case ADD:   return eval_tree(tree->l) + eval_tree(tree->r);
		case MULTI: return eval_tree(tree->l) * eval_tree(tree->r);
		case VAL:   return tree->val;
	}
	return 0;  // should no happen, but who know's ?
}
