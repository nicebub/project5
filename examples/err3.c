/*
 * error:  illegal operands for addition
 */

int scanf( char *fmt, ... );
int printf( char *fmt, ... );

int
main( void )
{
  int i, j;

  scanf( "%d", &i );                /* get i */
  j = 9 + "string";
  printf( "Result is %d\n", j );    /* print j */
  return(0);
}
