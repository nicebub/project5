
/*
 * error:  void function used in expression
 */

int scanf( char *fmt, ... );
int printf( char *fmt, ... );

void count( int n );

int
main( void )
{
  int i, sum;

  scanf( "%d", &i);              /* get i */
  sum = count(i);                /* call count */
  printf( "%d\n", sum );         /* write result */
}

void
count( int n )
{
  int i, sum;

  i = 1;
  sum = 0;
  while ( i <= n ) {
    sum = sum + i;
    i = i + 1;
  }
}
