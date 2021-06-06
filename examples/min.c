/* tests function calls */

int printf( char *fmt, ... );
int min(int a, int b);
int scanf(char *fmt, ... );

int x;
int y;

int main(void){
  int z;  
  printf("Enter a number: ");
  scanf("%d",&x);
  printf("Enter a number: ");
  scanf("%d",&y);
  z= min(x,y);
  printf("The min of %d",x);
  printf(" and %d",y);
  printf(" is %d\n",z);
	return 0;
}

int min(int a, int b){
  printf("First argument to min is %d\n",a);
  printf("Second arguement to min is %d\n",b);
  if(a < b)
    return a;
  else
    return b;
}
