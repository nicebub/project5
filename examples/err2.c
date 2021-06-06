/*
 * error: multiple declaration of ident:  i
 */

int scanf( char *fmt, ... );
int printf( char *fmt, ... );

int
main( void )
{
  int i, j;
  int i;

  scanf( "%d", &i );                /* get i */
  j = 9 + i * 8;                    /* evaluate j */
  printf( "Result is %d\n", j );    /* print j */
  return(0);
}
