/* prints the first n fibonacci numbers */

int scanf( char *fmt, ... );
int printf( char *fmt, ... );
void fib(void);
int counter;
int a;
int b;

int main(void){
  int num;
  printf("Enter a number: ");
  scanf("%d",&num);
  printf("The first %d fibonacci numbers are:\n1\n1\n",num);
  counter= 0;
  a= 1;
  b= 1;
  while(counter< num-2){
    fib();
 }
 return 0;
}

void fib(void){
  int temp;
  counter= counter +1;
  temp= a + b;
  a= b;
  b= temp;
  printf("This is the expression: %d\n",temp);
}
