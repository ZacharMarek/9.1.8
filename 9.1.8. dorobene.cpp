#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define ELEM(M,r,c) (M->elem[(M->cols)*r+c]) 

#define MAT_NOT_ROT 0
#define MAT_ROT 1


typedef struct
{
	unsigned int rows;
	unsigned int cols;
	float *elem;
} MAT;



MAT *mat_create_with_type(unsigned int rows, unsigned int cols)
{
	MAT *mat=(MAT *)malloc(sizeof(MAT));
	if (mat==NULL)
		return NULL;
		
	mat->rows=rows;
	mat->cols=cols;
	
	mat->elem=(float *)malloc(sizeof(float)*rows*cols);
	if (mat->elem==NULL)
	{
	
		return NULL;
	}
	
	return mat;
}

void mat_random(MAT *mat)
{
	int i, j;
	
	for (i=0;i<mat->rows;i++)
	{
		for (j=0;j<mat->cols;j++)
		{
			ELEM(mat,i,j)=((float)rand()/(int)(RAND_MAX))*-2.0 + 1.0;
		}
	}	
}

void mat_print(MAT *mat)
{
	int i, j;
	
	for (i=0;i<mat->rows;i++)
	{
		for (j=0;j<mat->cols;j++)
		{
			printf("%3.0f",ELEM(mat,i,j));
		}
		printf("\n");
	}
	printf("\n");
}

void mat_destroy (MAT *mat)
{
	free(mat->elem);
	free(mat);
}

void mat_unit(MAT *mat)
{
	int i,j;
	
	for (i=0;i<mat->rows;i++)
	{
		for (j=0;j<mat->cols;j++)
		{
			if (i==j)
				ELEM(mat,i,j)=1.0;
			else
				ELEM(mat,i,j)=0.0;
		}
	}
}
//rotaèna matica musi splna dve vlatnosti a to matica krat transponovana matica sa musi rovna I druha vlastnos ktora z nej vychadza že det matice = +-1
//takže matica rotacie musi by ortogonálna 
char mat_test_rotation(MAT *mat)
{
	
	int i,j, vysledok =1;
	float trans[i][j]; //transponovana matica
	float kon[i][j];
	float suma =1;
	
	if(mat->cols!=mat->rows)
	{
	for(i=0;i<mat->rows;i++)
	{
		for(j=0;j<mat->cols;j++)
		{
			trans[i][j]=ELEM(mat,i,j);
			//printf("%f",trans[i][j]);
		}
		
	}
	for(i=0;i<mat->rows;i++)
	{
		for(j=0;j<mat->cols;j++)
		{
			for(int x=0;x<mat->cols;x++)
			{
				suma+=(trans[i][j]*ELEM(mat,i,j));
			}
			kon[i][j]=suma;
			suma=0;
		}
	}
	
	for(i=0;i<mat->rows;i++)
	{
		for(j=0;j<mat->cols;j++)
		{
			if(i==j && kon[i][j]!=1 )
			vysledok =0;
			if(i!=j && kon[i][j]!=0)
			vysledok = 0;
		}
	}
	if(vysledok==1)
		return MAT_ROT;
	else
		return MAT_NOT_ROT;
	}
	else
		return MAT_NOT_ROT;
}
main()
{
	MAT *matica;
	float *m;
	srand(time(0));
	matica=mat_create_with_type(5,5);
    //char odpoved = mat_test_rotation(matica);
    
    
	mat_random(matica);
	mat_print(matica);
	
	mat_test_rotation(matica);	
	printf("%i\n",mat_test_rotation(matica));
	
	printf("\n");
	
	mat_unit(matica);	//jednotkova
	mat_print(matica);
	
    mat_test_rotation(matica);
	printf("%i\n",mat_test_rotation(matica));
	
	

}
