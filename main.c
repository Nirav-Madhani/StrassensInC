/******************************************************************************

A B  E F
C D  G H

*******************************************************************************/
#include <stdio.h>


void printMatrix(int s,int **a){
    for(int i=0;i<s;i++){
        for(int j=0;j<s;j++){
            printf("%d ",a[i][j]);
        }printf("\n");
    }
}

int ** newMatrix(int s){
    int **c;
    c = malloc(sizeof(int*) * s);
     
    for(int i = 0; i < s; i++) {
        c[i] = malloc(sizeof(int*) * s);
    }
    for(int i=0;i<s;i++)
    for(int j=0;j<s;j++)
        c[i][j]=0;
    return c;
}
//If we pass double array to double pointer, we'll get segmentation fault.
//But initializing double pointer every time is tedious
//So i m initializing 2d array but then converting it to double pointer
int** arr2pointer(int s,int a[][s]){
    int** c = newMatrix(s);
    for(int i=0;i<s;i++)
    for(int j=0;j<s;j++)
        c[i][j] = a[i][j];
    return c;
}
//Modified to give least pow(2) >= n size matrix
int** arr2pointer2(int s,int a[][s]){
    int n =  pow(2, ceil(log(s)/log(2)));    
    int** c = newMatrix(n);
    for(int i=0;i<s;i++)
    for(int j=0;j<s;j++)
        c[i][j] = a[i][j];
    return c;
}
//Matrix Addition
int ** add(int s,int **a,int** b){
    int** c = newMatrix(s);
    for(int i=0;i<s;i++){
        for(int j=0;j<s;j++){
            c[i][j] =  a[i][j]+b[i][j];
        }
    }
    return c;
}
//Matrix Subtraction
int ** sub(int s,int** a,int** b){
    int** c = newMatrix(s);
    for(int i=0;i<s;i++){
        for(int j=0;j<s;j++){
            c[i][j] =  a[i][j]-b[i][j];
        }
    }
    return c;
}
//Strassen matrix multiplication.
int **multiply(int s,int **A,int **B)
{   
    
int** C = newMatrix(s);
    
if(s==2){
    int m1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]); //(a + d)(e+h)
	int m2 = (A[1][0] + A[1][1]) * B[0][0];             //(c+d)e
	int m3 = A[0][0] * (B[0][1] - B[1][1]);             // a(f-h)                     
	int m4 = A[1][1] * (B[1][0] - B[0][0]);             // d*(g-e)
	int m5 = (A[0][0] + A[0][1]) * B[1][1];             // (a+b)*h
	int m6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]); //(c-a)*(e+f)
	int m7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]); //(b-d)*(g+h)
	C[0][0] = m1 + m4 - m5 + m7;
	C[0][1] = m3 + m5;
	C[1][0] = m2 + m4;
	C[1][1] = m1 - m2 + m3 + m6;
	return C;
}
//Divide Matrix
int n2 = s/2;
int **a = newMatrix(n2);
int **b = newMatrix(n2);
int **c = newMatrix(n2);
int **d = newMatrix(n2);
int **e = newMatrix(n2);
int **f = newMatrix(n2);
int **g = newMatrix(n2);
int **h = newMatrix(n2);
//Assigning Matrix A to H
for(int i=0;i<n2;i++){
    for(int j=0;j<n2;j++){
        a[i][j] = A[i][j];
        e[i][j] = B[i][j];
    }
}
for(int i=0;i<n2;i++){
    for(int j=n2;j<2*n2;j++){
         b[i][j-n2] = A[i][j];
        f[i][j-n2] = B[i][j];
    }
}
for(int i=n2;i<2*n2;i++){
    for(int j=0;j<n2;j++){
        c[i-n2][j] = A[i][j];
        g[i-n2][j] = B[i][j];
    }
}
for(int i=n2;i<2*n2;i++){
    for(int j=n2;j<2*n2;j++){
        d[i-n2][j-n2] = A[i][j];
        h[i-n2][j-n2] = B[i][j];
    }
}
 //(a + d)(e+h)
//(c+d)e
// a(f-h)                     
// d*(g-e)
// (a+b)*h
 //(c-a)*(e+f)
 //(b-d)*(g+h)
int **m1 = multiply(n2,add(n2,a,d),add(n2,e,h));
int **m2 = multiply(n2,add(n2,c,d),e);
int **m3 = multiply(n2,a,sub(n2,f,h));
int **m4 = multiply(n2,d,sub(n2,g,e));
int **m5 = multiply(n2,add(n2,a,b),h);
int **m6 = multiply(n2,sub(n2,c,a),add(n2,e,f));
int **m7 = multiply(n2,sub(n2,b,d),add(n2,g,h));

//	C[0][0] = m1 + m4 - m5 + m7;
//	C[0][1] = m3 + m5;
//	C[1][0] = m2 + m4;
//	C[1][1] = m1 - m2 + m3 + m6;

int **c0 = sub(n2,add(n2,add(n2,m1 , m4) , m7),m5);
int **C1 = add(n2,m3,m5);
int **c2 = add(n2,m2,m4);
int **c3 = sub(n2,add(n2,add(n2,m1,m3),m6),m2);
//Assign c
for(int i=0;i<n2;i++){
    for(int j=0;j<n2;j++){
         C[i][j]=c0[i][j];
    }
}
for(int i=0;i<n2;i++){
    for(int j=n2;j<2*n2;j++){
        C[i][j] = C1[i][j-n2] ;
       
    }
}
for(int i=n2;i<2*n2;i++){
    for(int j=0;j<n2;j++){
        C[i][j] = c2[i-n2][j] ;

    }
}
for(int i=n2;i<2*n2;i++){
    for(int j=n2;j<2*n2;j++){
       C[i][j] =  c3[i-n2][j-n2];
    }
}
return C;
}

int main(){
    
  
    int n=3;
    int a[][3] = {1,2,3,4,5,6,7,8,9};
    int b[][3] = {2,4,6,8,1,2,3,4,5};

    
    int n1 = pow(2, ceil(log(n)/log(2))); 
    int** A = arr2pointer2(n,a)    ;
    int** B = arr2pointer2(n,b)    ;
    int** c= multiply(n1,A,B);
    printf("A matirx is:\n");
    printMatrix(n,A);
    printf("B matrix is:\n");
    printMatrix(n,B);
    printf("Result of AxB matrix is:\n");
    printMatrix(n,c);
    return 0;
}

