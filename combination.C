#include<stdio.h>
#include<math.h>

Bool_t combination
{
int argc;
 char *argv[];
    char *A[] = { "a1", "b1", "a2", "b2", "a3", "b3", "a4", "b4" };
    
    int array_length = 8;
    int pair_length = 2;
    int total_pairs = (array_length/pair_length);
    int no_of_pairs = (total_pairs*total_pairs);
    int e_index = 0;

 
    
	for(int i=0;i<no_of_pairs;i++) {
		printf("{ ");
		for(int j=0;j<total_pairs;j++) {
			e_index = (int)(((int)(floor(( i / (no_of_pairs/pow(2,j+1))))) % 2) + (j*pair_length));
	        printf("%s ", A[e_index]);
		}
		printf("}\n");
	}
}
