/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

/**
 * Base abstract class to handle various versions of HEngine algorithm
 * proposed by Alex X. Liu, Ke Shen, Eric Torng
 * in their paper "Large Scale Hamming Distance Query Processing".
 * ICDE Conference, pages 553 - 564, 2011.
 */

#ifndef HENGINE_H
#define HENGINE_H

#include <vector>
#include <string>

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
typedef std::vector<BinStr> Table;

class HEngine
{

protected:
    /**
     * Original database of strings
     */
    Table m_db;

public:
    virtual ~HEngine() {}

    /**
     * Base functions to proceed querying the database
     */
    virtual Table query( BinStr ) const = 0;
    virtual Table query( Number ) const = 0;

    /**
     * Convertors
     */
    static Number bin2dec( std::string );
    static std::string dec2bin( Number );
};

} // namespace

#endif
