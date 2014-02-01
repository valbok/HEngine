/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

/**
 * Base abstract class to handle various versions of HEngine algorithm
 */

#ifndef HENGINE_H
#define HENGINE_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace hengine
{

/**
 * 64 bit number of a hash to calculate hamming distance
 */
typedef unsigned long long Number;

/**
 * Contains string binary representation of a number, e.g "11110000"
 */
typedef std::string BinStr;

/**
 * Database of strings in dec
 */
typedef std::vector<Number> NumTable;

/**
 * Database of strings in binary
 */
typedef std::vector<BinStr> BinTable;

/**
 * Result of querying.
 * List of found strings and its hamming distance to requested one.
 */
typedef std::map<Number, unsigned> Matches;

class HEngine
{

public:
    HEngine() {}
    virtual ~HEngine() {}

    /**
     * Base functions to proceed querying the database
     */
    virtual Matches query( const BinStr& ) const = 0;
    virtual Matches query( const Number& ) const = 0;

    /**
     * Convertors from number to bin string and vica versa
     */
    static Number binStr2Number( std::string );
    static std::string number2BinStr( Number );

    /**
     * Calculates actual hamming distance between numbers or bin strings
     */
    static Number getHammingDistance( Number, Number );
    static Number getHammingDistance( BinStr, BinStr );
};

} // namespace

#endif
