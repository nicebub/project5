int scanf( char *fmt, ... );
int printf( char *fmt, ... );
int fact( int n);

int main(void){

  int i, j;
  j= 0;
  printf("Enter a number: ");
  scanf("%d",&i);
  while(i < 1 ){
    printf("Too small\n");
    scanf("%d",&i);
  }
    j= fact(i);
    printf("The factorial of you number is %d\n",j);
return 0;
}

int fact( int i ){
  if(i == 1)
    return 1;
  else
    return i*fact(i-1);
}
