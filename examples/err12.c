/*
 * error:  function declaration and definition mismatch
 */

int scanf( char *fmt, ... );
int printf( char *fmt, ... );

int count( int n );

int
main( void )
{
  int i, sum;

  scanf( "%d", &i);              /* get i */
  sum = count(i);                /* call count */
  printf( "%d\n", sum );         /* write result */
  return(0);
}

int
count( float n )
{
  int i, sum;

  i = 1;
  sum = 0;
  while ( i <= n ) {
    sum = sum + i;
    i = i + 1;
  }
  return sum;
}
