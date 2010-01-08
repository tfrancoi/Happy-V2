/*----------------------------------------------------------------------------*
**  sets.h : class declaration for set operations using bit representations. 
**
**  Stephen R. Schmitt
*/

#ifndef SETS_H
#define SETS_H

#define MAX_WORDS  2
#define WORD_SIZE  ( 8 * sizeof( unsigned long ) )

class sets
{
public:
    sets();
    sets( const sets & );
    void binary();
    int  cardinality();
    void clear();
    void define( char * );
    void insert( int );
    int  item( int );
    void print();
    void remove( int );

    const sets &operator = ( const sets & );
    sets operator ~ () const;
    sets operator + ( const sets & );
    sets operator * ( const sets & );
    sets operator - ( const sets & );
    sets operator ^ ( const sets & );

private:
    unsigned long set[MAX_WORDS];                   // the set
};

#endif
