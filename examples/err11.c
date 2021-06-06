/*
 * error:  void function and return w/ expression
 */

int scanf( char *fmt, ... );
int printf( char *fmt, ... );

void count( int n );

int
main( void )
{
  int i, sum;

  scanf( "%d", &i);              /* get i */
  count(i);                /* call count */
  printf( "%d\n", sum );         /* write result */
  return(0);
}

void
count( int n )
{
  int i, sum;

  i = 1;
  sum = 0;
  while ( "hello" ) {
    sum = sum + i;
    i = i + 1;
  }
  return sum;
}
