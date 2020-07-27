#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <stdio_ext.h>


struct Tree
{
	char ch;
	int count;
	struct Tree *link[128];
};

int z=1;
int count_var = 0;
int done = 1;
int delete = 1;

typedef struct Tree Tree; 


Tree *create_node(char c, int start_index)
{
	Tree* new_tree;
	new_tree = (Tree*)malloc(sizeof(Tree));
	new_tree->ch = c;
	new_tree->count = start_index;
	for(int i=0;i<128;i++)
	{
		new_tree->link[i] = NULL;
	}
	return new_tree;
}

void print_tree(Tree* root, char a[], int *arr)
{
	int loc;
	Tree *temp = root;
	for(int i=0;i<strlen(a);i++)
	{
		if (a[i] >= 'A' && a[i] <= 'Z')
	         		a[i] = a[i] + 32;
		if(temp->link['0'-48+a[i]] == NULL)
		{
			loc = -1;
			break;
		}
		else
		{
			temp = temp->link['0'-48+a[i]];
			loc = temp->count;
		}
	}
	if(loc == -1 && done)
	{
		done = 0;
	}
	int p=strlen(a);
	int q = 1;
	for(int i=0;i<=count_var;i++)
		if(arr[i] == loc-p+1)
		{
			q = 0;
			break;
		}
		if((q || (loc-p+1 == 0 && delete)) && loc >-1)
		{
			delete = 0;
			arr[count_var] = loc-p+1;
			count_var = count_var+1;
		}

}

void search(Tree *root, char c, char a[], int arr[])
{
	for(int i=0;i<128;i++){
		if(root->link[i] == NULL)
			continue;
		else if(root->link[i]->ch == c){
			print_tree(root, a, arr);
			search(root->link[i], c,a, arr);
		}
		else
		search(root->link[i],c,a, arr);}
}

int main()
{
	Tree *root, *temp;
	root = create_node('\0', -1);
	int inp_count;
	char inp[4001];
	fgets(inp, 4001, stdin);	
	for(int j=0;j<strlen(inp);j++)
	{
	if (inp[j] >= 'A' && inp[j] <= 'Z')
        	inp[j] = inp[j] + 32;
	}
	scanf("%d", &inp_count);
	int copy_inp = inp_count;
	while(inp_count+1)
	{
		int arr[25] = {-1};
		count_var = 0;
		char *string = (char*)malloc(4001*sizeof(char));
		fgets(string, 4001, stdin);			
		string[(int)strlen(string)-1]='\0';
		for(int i=0;i<strlen(inp)-1;i++)
		{
			temp = root;
			for(int j=i;j<strlen(inp)-1;j++)
			{
				char d = '0'-48 + inp[j];
				if(temp->link[d] == NULL)
				{
					temp->link[d] = create_node(inp[j], j);
					temp = temp->link[d];
				}
				else
					temp = temp->link[d];
			}
		}
		Tree* temp1 = root;
		print_tree(temp1, string, arr);
		char first = string[0];
		search(temp1, first, string, arr);		
		if(copy_inp != inp_count)	
		{
			for(int r=0;r<count_var;r++)
				printf("%d ", arr[r]);
			if(count_var == 0)
				printf("-1");
			printf("\n");
	}
	inp_count = inp_count-1;
	}
	return 0;
}
