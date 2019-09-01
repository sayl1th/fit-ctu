#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <memory>
using namespace std;

class InvalidIndexException
{
};

#endif /* __PROGTEST__ */

class CPatchStr
{
  public:
                CPatchStr ( void );
                CPatchStr ( const char * str );
    // copy constructor
    // destructor 
    // operator =
    CPatchStr   SubStr    ( size_t            from,
                            size_t            len ) const;
    CPatchStr & Append    ( const CPatchStr & src );

    CPatchStr & Insert    ( size_t            pos,
                            const CPatchStr & src );
    CPatchStr & Delete    ( size_t            from,
                            size_t            len );
    char      * ToStr     ( void ) const;
  private:
    // todo
};

#ifndef __PROGTEST__
bool stringMatch ( char       * str,
                   const char * expected )
{
  bool res = strcmp ( str, expected ) == 0;
  delete [] str;
  return res;
}

int main ( void )
{
  char tmpStr[100];

  CPatchStr a ( "test" );
  assert ( stringMatch ( a . ToStr (), "test" ) );
  strncpy ( tmpStr, " da", sizeof ( tmpStr ) );
  a . Append ( tmpStr );
  assert ( stringMatch ( a . ToStr (), "test da" ) );
  strncpy ( tmpStr, "ta", sizeof ( tmpStr ) );
  a . Append ( tmpStr );
  assert ( stringMatch ( a . ToStr (), "test data" ) );
  strncpy ( tmpStr, "foo text", sizeof ( tmpStr ) );
  CPatchStr b ( tmpStr );
  assert ( stringMatch ( b . ToStr (), "foo text" ) );
  CPatchStr c ( a );
  assert ( stringMatch ( c . ToStr (), "test data" ) );
  CPatchStr d ( a . SubStr ( 3, 5 ) );
  assert ( stringMatch ( d . ToStr (), "t dat" ) );
  d . Append ( b );
  assert ( stringMatch ( d . ToStr (), "t datfoo text" ) );
  d . Append ( b . SubStr ( 3, 4 ) );
  assert ( stringMatch ( d . ToStr (), "t datfoo text tex" ) );
  c . Append ( d );
  assert ( stringMatch ( c . ToStr (), "test datat datfoo text tex" ) );
  c . Append ( c );
  assert ( stringMatch ( c . ToStr (), "test datat datfoo text textest datat datfoo text tex" ) );
  d . Insert ( 2, c . SubStr ( 6, 9 ) );
  assert ( stringMatch ( d . ToStr (), "t atat datfdatfoo text tex" ) );
  b = "abcdefgh";
  assert ( stringMatch ( b . ToStr (), "abcdefgh" ) );
  assert ( stringMatch ( b . ToStr (), "abcdefgh" ) );
  assert ( stringMatch ( d . ToStr (), "t atat datfdatfoo text tex" ) );
  assert ( stringMatch ( d . SubStr ( 4, 8 ) . ToStr (), "at datfd" ) );
  assert ( stringMatch ( b . SubStr ( 2, 6 ) . ToStr (), "cdefgh" ) );
  try
  {
    b . SubStr ( 2, 7 ) . ToStr ();
    assert ( "Exception not thrown" == NULL );
  }
  catch ( InvalidIndexException & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown" == NULL );
  }
  a . Delete ( 3, 5 );
  assert ( stringMatch ( a . ToStr (), "tesa" ) );
  return 0;
}
#endif /* __PROGTEST__ */
