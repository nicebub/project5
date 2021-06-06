/*
 * error:  incompatible operands of asignment
 */

int scanf( char *fmt, ... );
int printf( char *fmt, ... );

int
main( void )
{
  int i, j;

  scanf( "%d", &i );                /* get i */
  j = "hello";
  printf( "Result is %d\n", j );    /* print j */
  return(0);
}
