#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFMAX 100
typedef struct tree
{
	int v[3][3];
	struct tree *child[9];
	int nr_c;
	int terminat;
	int sisau;
}*Tree;

Tree initTree(int (*v)[3])
{
	int i, j;
	Tree tree = (Tree) calloc(1, sizeof(struct tree));
	tree->nr_c = 0;
	tree->terminat = 0;
	for(i = 0; i <= 2; i ++) 
		for(j = 0; j <= 2; j ++) 
			tree->v[i][j] = v[i][j];
	tree->sisau = 0;
	for(i = 0; i <= 2; i ++)
		for(j = 0; j <= 2; j ++)
			if(tree->v[i][j] == -1)
				tree->nr_c ++;
	return tree;
}

Tree verif_terminare(Tree tree)
{
	int i, j;
	i = 1; j = 1;
	if(tree->v[i-1][j] == tree->v[i][j] && tree->v[i+1][j] == tree->v[i][j] && tree->v[i][j] != -1)
		tree->terminat = 1;
	if(tree->v[i-1][j-1] == tree->v[i][j] && tree->v[i+1][j+1] == tree->v[i][j] && tree->v[i][j] != -1) 
		tree->terminat = 1;
	if(tree->v[i+1][j-1] == tree->v[i][j] && tree->v[i-1][j+1] == tree->v[i][j] && tree->v[i][j] != -1) 
		tree->terminat = 1;
	if(tree->v[i][j-1] == tree->v[i][j] && tree->v[i][j+1] == tree->v[i][j] && tree->v[i][j] != -1) 
		tree->terminat = 1;

	if(tree->v[0][0] == tree->v[0][1] && tree->v[0][1] == tree->v[0][2] && tree->v[0][0] != -1)
		tree->terminat = 1;
	if(tree->v[0][0] == tree->v[1][0] && tree->v[1][0] == tree->v[2][0] && tree->v[0][0] != -1) 
		tree->terminat = 1;
	if(tree->v[0][2] == tree->v[1][2] && tree->v[1][2] == tree->v[2][2] && tree->v[0][2] != -1) 
		tree->terminat = 1;
	if(tree->v[2][0] == tree->v[2][1] && tree->v[2][1] == tree->v[2][2] && tree->v[2][0] != -1) 
		tree->terminat = 1;
	return tree;
}
void prelucrare(int nr_c, Tree tree, char jucator)
{
	int i, j, k, l;
	int ct = 0;
	int v[3][3];
	tree = verif_terminare(tree);
	if(tree->terminat == 0)
	for(i = 0; i < 3; i ++)
		for(j = 0; j < 3; j ++)
		{
			for(k = 0; k < 3; k ++)
				for(l = 0; l < 3; l ++)
					v[k][l] = tree->v[k][l];
			
			if(tree->v[i][j] == -1)
			{
				
				if(jucator == 'X')
				{
					v[i][j] = 1;
					tree->child[ct] = initTree(v);
					tree->child[ct] = verif_terminare(tree->child[ct]);
					if(tree->child[ct] != NULL && !tree->child[ct]->terminat)
						prelucrare(tree->child[ct]->nr_c,  tree->child[ct], 'O');
					ct ++;
				}
				else
				{
					v[i][j] = 0;
					tree->child[ct] = initTree(v);
					tree->child[ct] = verif_terminare(tree->child[ct]);
					if(tree->child[ct] != NULL && !tree->child[ct]->terminat)
						prelucrare(tree->child[ct]->nr_c,  tree->child[ct], 'X');
					ct ++;
				}
			}
		}
}

void afisare_treec1(Tree tree, int numar_taburi, FILE *g)
{
	int i, j, k;
	
	for(i = 0; i < 3; i ++)
	{
		for(k = 0; k < numar_taburi; k ++)
		{
			printf("\t");
			fprintf(g, "\t");
		}
		for(j = 0; j < 3; j ++)
		{
			if(tree->v[i][j] == 1) { printf("X"); fprintf(g, "X"); }
			if(tree->v[i][j] == 0) { printf("0"); fprintf(g, "O"); }
			if(tree->v[i][j] == -1) { printf("-"); fprintf(g, "-"); }
			if(j != 2) { printf(" "); fprintf(g, " "); }
		}
		printf("\n");
		fprintf(g, "\n");

	}
	if(tree->terminat);
		fprintf(g, "\n");
	printf("%d\n", tree->terminat);
	for(k = 0; k < tree->nr_c; k ++)
		if(tree->child[k] != NULL)
			afisare_treec1(tree->child[k], numar_taburi + 1, g);

}

int verificare_castigator(Tree tree, char jucator)
{
	int joc;
	if(jucator == 'X') joc = 1;
	else joc = 0;
	if(tree->v[0][0] == tree->v[1][1] && tree->v[2][2] == tree->v[1][1] && tree->v[1][1] == joc)
		return 1;
	if(tree->v[0][1] == tree->v[1][1] && tree->v[1][1] == tree->v[2][1] && tree->v[1][1] == joc) 
		return 1;
	if(tree->v[2][0] == tree->v[1][1] && tree->v[1][1] == tree->v[0][2] && tree->v[1][1] == joc) 
		return 1;
	if(tree->v[1][0] == tree->v[1][1] && tree->v[1][1] == tree->v[1][2] && tree->v[1][1] == joc) 
		return 1;

	if(tree->v[0][0] == tree->v[0][1] && tree->v[0][1] == tree->v[0][2] && tree->v[0][0] == joc)
		return 1;
	if(tree->v[0][0] == tree->v[1][0] && tree->v[1][0] == tree->v[2][0] && tree->v[0][0] == joc) 
		return 1;
	if(tree->v[0][2] == tree->v[1][2] && tree->v[1][2] == tree->v[2][2] && tree->v[0][2] == joc) 
		return 1;
	if(tree->v[2][0] == tree->v[2][1] && tree->v[2][1] == tree->v[2][2] && tree->v[2][0] == joc) 
		return 1;
	return 0;
}

void si_sau(Tree tree, int contor, char jucator)
{
	int i;
	if(tree->nr_c == 0 && tree != NULL)
		if(verificare_castigator(tree, jucator)) tree->sisau = 1;
	if(tree->nr_c)
	{
		for(i = 0; i < tree->nr_c; i ++)
			if(tree->child[i] != NULL)
				si_sau(tree->child[i], contor + 1, jucator);
		if(contor % 2 == 0)
			for(i = 0; i < tree->nr_c; i ++)
				if(tree->child[i] != NULL && tree->child[i]->sisau == 1) 
				{
					tree->sisau = 1;
					break; 
				}
		if(contor % 2 == 1)
		{
			tree->sisau = 1;
			for(i = 0; i < tree->nr_c; i ++)
				if(tree->child[i] != NULL && tree->child[i]->sisau == 0) 
				{ 
					tree->sisau = 0; 
					break; 
				}
		}
		
	}
}
void afisare_treec2(Tree tree, int numar_taburi, FILE *g)
{
	int k;
	for(k = 0; k < numar_taburi; k ++)
		fprintf(g, "\t");
	if(tree->sisau == 1) fprintf(g, "T");
	else fprintf(g, "F");
	fprintf(g, "\n");
	for(k = 0; k < tree->nr_c; k ++)
		if(tree->child[k] != NULL)
			afisare_treec2(tree->child[k], numar_taburi + 1, g);
}
void freeTree(Tree tree)
{
	int i;
	for(i = 0; i < tree->nr_c; i ++)
		if(tree->child[i] != NULL)
			freeTree(tree->child[i]);
	free(tree);

}

int main (int argc, char **argv)
{
	Tree tree;
	int i, j, cerinta;
	int v[3][3];
	FILE *f, *g;
	char jucator, nulll;
	char buffer[700000];
	f = fopen(argv[2], "r");
	g = fopen(argv[3], "w");
	if(argv[1][2] == '1') cerinta = 1;
	if(argv[1][2] == '2') cerinta = 2;
	if(argv[1][2] == '3') cerinta = 3;
	printf("\n%d\n", cerinta);
	fscanf(f, "%c", &jucator);
	printf("%c\n", jucator);
	fscanf(f, "%c", &nulll);
	for(i = 0; i < 3; i ++)
	{
		fgets(buffer, BUFFMAX, f);
		for(j = 0; j < strlen(buffer); j += 2)
		{
			if(buffer[j] == 'X') v[i][j/2] = 1; 
			if(buffer[j] == 'O') v[i][j/2] = 0;
			if(buffer[j] == '-') v[i][j/2] = -1;
		}
	}
	tree = initTree(v);

	if(cerinta == 1)
	{
		prelucrare(tree->nr_c, tree, jucator);
		afisare_treec1(tree, 0, g);
	}
	if(cerinta == 2)
	{
		prelucrare(tree->nr_c, tree, jucator);
		si_sau(tree, 0, jucator);
		afisare_treec2(tree, 0, g);
	}
	fclose(f);
	fclose(g);

	freeTree(tree);
	return 0;
}
