#include <stdio.h>

int main(){
	// Taking Input of first matrix
	int rows1,cols1;
	printf("Enter the no. of Rows for 1st Matrix");
	scanf("%d",&rows1);
	printf("Enter the no. of Cols for 1st Matrix");
	scanf("%d",&cols1);
	float Mat1[rows1][cols1];
	for (int i = 0;i<rows1;i++){
		
		for (int j=0;j<cols1;j++){
			printf("Enter values for %dth Column of %d Row\n",j+1,i+1);
			scanf("%f",&Mat1[i][j]);
		}
	}
	printf("\n\n\n");
	// Taking Input of first matrix
	int rows2,cols2;
	printf("Enter the no. of Rows for 2nd Matrix");
	scanf("%d",&rows2);
	printf("Enter the no. of Cols for 2nd Matrix");
	scanf("%d",&cols2);
	float Mat2[rows2][cols2];
	for (int i = 0;i<rows2;i++){
		
		for (int j=0;j<cols2;j++){
			printf("Enter values for %dth Column of %d Row\n",j+1,i+1);
			scanf("%f",&Mat2[i][j]);
		}
	}
	if (cols1!=rows2) {
		printf("For two matrix to multiply the cols of Mat1 should be equal to rows of Mat2");
		return 1;
	}

	float Mat3[rows1][cols2] ,temp;
	for (int i = 0;i<rows1;i++){
		
		for (int j=0;j<cols2;j++){
			temp = 0;
			for (int k=0;k<rows2;k++){
				temp+=Mat1[i][k]*Mat2[k][j];
			}
			Mat3[i][j] = temp;
		}
	}
	for (int i=0;i<rows1;i++){
		printf("|");
		for (int j=0;j<cols2;j++){
			printf("%f ",Mat3[i][j]);
		}
		printf("|\n");
	}

	return 0;
}