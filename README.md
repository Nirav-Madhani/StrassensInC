
# Implementation of Strassen's Matrix Multiplication Algorithm In C
Implementation of Strassens Algorithm in C using pointers

## Hilights

1. One of the problem in c is creating matrix of dynamic size.
2. Therefore I need to use double pointer.
3. Initializing double pointer is messy, so we can rather initialize an array and convert into double pointer
```
int** arr2pointer(int s,int a[][s]){
    int** c = newMatrix(s);
    for(int i=0;i<s;i++)
    for(int j=0;j<s;j++)
        c[i][j] = a[i][j];
    return c;
}
```

4. To create matrix of size `s x s`
```
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
```
5. In `main` method I'm  testing the functionality by hardcoding 2 matrices, which can be easily be modified to accept input from user

## Sample I/O

```
A matirx is:
1 2 3 
4 5 6 
7 8 9 
B matrix is:
2 4 6 
8 1 2 
3 4 5 
Result of AxB matrix is:
27 18 25 
66 45 64 
105 72 103 
```
