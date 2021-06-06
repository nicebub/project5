/*
 *  error:  incompatible parameters for printarray
 */

int scanf( char *fmt, ... );
int printf( char *fmt, ... );

void printarray( float b[] )
{
  int i;

  i = 0;
  while ( i < 5 ) {
    printf( "value %d = ", i+1 );
    printf( "%f\n", b[i] );
    i = i + 1;
  }
}

void bubble( float c[] )
{
  int   i, j;
  float temp;

  i = 0;
  while ( i < 4 ) {
    j = i + 1;
    while ( j < 5 ) {
      if ( c[i] > c[j] ) {
	temp = c[i];
	c[i] = c[j];
	c[j] = temp;
      }
      j = j + 1;
    }
    i = i + 1;
  }
}

int
main( void )
{
  float a[10];
  int   i;

  printf( "Please enter 5 reals for bubble sort.\n\n" );

  i = 0;
  while (i < 5) {
    printf( "enter a float for sorting: ");
    scanf( "%f", &a[i] );
    i = i + 1;
  }

  printf( "the original input:\n" );
  printarray( a[0] );
  bubble( a );
  printf( "the sorted numbers:\n" );
  printarray( a );
  return(0);
}
