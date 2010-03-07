/*----------------------------------------------------------------------------*
**  sets.cpp : class definitions for set operations using bit representations. 
**
**  Stephen R. Schmitt
**  Nettoyage et mis en c++ pure : Thibault Francois
*/

                               // MS Visual C++ file
#include "sets.h"

#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>
using namespace std;
/*----------------------------------------------------------------------------*
**  "sets()" default constructor, initializes elements of the set to zero.  
**
**  returns: nothing
*/
sets::sets() {
	clear();                                        // initialize to empty
}

/*----------------------------------------------------------------------------*
**  "sets()" copy constructor, initializes elements of the set to be
**  equal to the values of the argument set.  
**
**  returns: nothing
*/
sets::sets(const sets &rhs) { // the set to copy
	for( int i = 0; i < MAX_WORDS; i++ )            // copy into new set
		set[i] = rhs.set[i];
}

/*----------------------------------------------------------------------------*
**  "item()" checks for existence of an item in the set.  
**
**  returns: 1 if item present, 0 if not, -1 on range error
*/
int sets::item( int bit ) {                           // index of the item
	if( bit <= 0 || bit > MAX_WORDS * WORD_SIZE )   // in range?
		return -1;

	int i = bit / WORD_SIZE;
	bit -= i * WORD_SIZE;
	return set[i] & 1 << ( bit - 1 );               // binary AND
}

/*----------------------------------------------------------------------------*
**  "insert()" puts an item into the set. Range errors are ignored.  
**
**  returns: nothing
*/
void sets::insert( int bit ) {                        // index of the item
	if( bit <= 0 || bit > MAX_WORDS * WORD_SIZE )   // in range?
		return;

	int i = bit / WORD_SIZE;
	bit -= i * WORD_SIZE;

	set[i] |= 1 << ( bit - 1 );                     // binary OR
}

/*----------------------------------------------------------------------------*
**  "remove()" takes an item out of the set. Range errors are ignored.  
**
**  returns: nothing
*/
void sets::remove( int bit ) {                      // index of the item
	if( bit <= 0 || bit > MAX_WORDS * WORD_SIZE )   // in range?
		return;
	int i = bit / WORD_SIZE;
	bit -= i * WORD_SIZE;

	set[i] &= ~( 1 << ( bit - 1 ) );                // binary AND
}

/*----------------------------------------------------------------------------*
**  "clear()" removes all items from the set..  
**
**  returns: nothing
*/
void sets::clear() {
	for( int i = 0; i < MAX_WORDS; i++ )            // all words in set
		set[i] = 0;
}

/*----------------------------------------------------------------------------*
**  "define()" initializes elements of the set using an enumerated input 
**  string (numbers separated by spaces).  
**
**  NOTE: Values of set elements that are too large are ignored.
**
**  returns: nothing
*/
void sets::define( string input ) {                   // string of numbers
	int length = input.size();                   // of input buffer
	int pos = 0;                                    // current character
	clear();                                        // initialize to empty

	while( pos < length ) {                      // more input
		int bit = 0;                                // init bit to set

		while( isdigit( input[pos] ) ) {
			bit *= 10;                              // compute bit to set
			bit += input[pos] - '0';
			pos++;                                  // advance
		}

		if( bit )                                   // zero means no bit
	    insert( bit );

		pos++;                                      // advance
	}
}

/*----------------------------------------------------------------------------*
**  "binary()" prints binary representation of set to stdout.
**
**  returns:  nothing
*/
void sets::binary() {
	for( int j = 0; j < MAX_WORDS; j++ ) {         // do all words
		unsigned long mask = 1;                     // start at low bit

		for( int i = 0; i < WORD_SIZE; i++ ) {       // every bit in word
			if( i % 4 == 0 )                        // add space
				putchar( ' ' );
			set[j] & mask ? putchar( '1' ) : putchar( '0' );
	    mask <<= 1;                             // next higher bit 
		}
	}
}

/*----------------------------------------------------------------------------*
**  "cardinality()" counts items in the set.
**
**  returns:  total items
*/
int sets::cardinality() {
	int count = 0;                                  // init counter

	for( int j = 0; j < MAX_WORDS; j++ ) {          // do all words
		unsigned long mask = 1;                     // start at low bit
        
		for( int i = 0; i < WORD_SIZE; i++ ) {       // every bit in word
			count += set[j] & mask ? 1 : 0;
	    mask <<= 1;                             // next higher bit
		}
	}
	return count;
}

/*----------------------------------------------------------------------------*
**  "print()" displays set to stdout as a list of integers.
**
**  returns:  nothing
*/
void sets::print() {
	cout << "{ " ;

	for( int j = 0; j < MAX_WORDS; j++ ) {           // do all words
		unsigned long mask = 1;                     // start at low bit
    for( int i = 1; i <= WORD_SIZE; i++ ) {
			if( set[j] & mask )                     // check bit
				cout << ( WORD_SIZE * j + i ) << " ";
			mask <<= 1;                             // next higher bit
		}
	}
	cout << "}" << endl;
}

string sets::to_s() {
	ostringstream out;
	out << "{ " ;

	for( int j = 0; j < MAX_WORDS; j++ ) {           // do all words
		unsigned long mask = 1;                     // start at low bit
        
		for( int i = 1; i <= WORD_SIZE; i++ ) {
			if( set[j] & mask )                     // check bit
				out << ( WORD_SIZE * j + i ) << " ";
			mask <<= 1;                             // next higher bit
		}
	}
    
	out << "}";
	return out.str();
}

/*----------------------------------------------------------------------------*
**  "operator = " assigns the right hand side to this set.
**
**  returns: nothing
*/
const sets &sets::operator = ( const sets &rhs ) {
	if( &rhs != this ) {             // avoid self assignment
		for( int i = 0; i < MAX_WORDS; i++ )        // copy into this set
			set[i] = rhs.set[i];
	}

	return *this;                                   // enable x = y = z;
}

/*----------------------------------------------------------------------------*
**  "operator ~ " performs set complement operation (not).
**
**  returns: pointer to set
*/
sets sets::operator ~ () const {
	sets rv;
	
	for( int i = 0; i < MAX_WORDS; i++ )
		rv.set[i] = ~set[i];                        // bitwise complement

	return rv;
}
		      
/*----------------------------------------------------------------------------*
**  "operator + " performs set union operation (or).
**
**  returns: pointer to set
*/
sets sets::operator + ( const sets &rhs ) {
	sets rv;
	
	for( int i = 0; i < MAX_WORDS; i++ )
		rv.set[i] = set[i] | rhs.set[i];            // bitwise OR

	return rv;
}

/*----------------------------------------------------------------------------*
**  "operator * " performs set intersection operation (and).
**
**  returns: pointer to set
*/
sets sets::operator * ( const sets &rhs ) {
	sets rv;
    
	for( int i = 0; i < MAX_WORDS; i++ )
		rv.set[i] = set[i] & rhs.set[i];            // bitwise AND
                       
	return rv;
}

/*----------------------------------------------------------------------------*
**  "operator - " performs set difference operation.
**
**  returns: pointer to set
*/
sets sets::operator - ( const sets &rhs ) {
	sets rv;
    
	for( int i = 0; i < MAX_WORDS; i++ )
		rv.set[i] = set[i] & ( ~rhs.set[i] );       // bitwise a AND ~b
                       
	return rv;
}

/*----------------------------------------------------------------------------*
**  "operator ^ " performs set symmetric difference operation (xor).
**
**  returns: pointer to set
*/
sets sets::operator ^ ( const sets &rhs ) {
	sets rv;
    
	for( int i = 0; i < MAX_WORDS; i++ )
		rv.set[i] = set[i] ^ rhs.set[i];            // bitwise XOR
                       
	return rv;
}

