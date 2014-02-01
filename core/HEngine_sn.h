/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */


/**
 * Non recursive implementation of HEngine using predefined hamming distance bound
 */

#ifndef HENGINE_SN_H
#define HENGINE_SN_H

#include "HEngine_s.h"

namespace hengine
{

class HEngine_sn: public HEngine_s
{

public:
    HEngine_sn( unsigned k, unsigned r = 0 ): HEngine_s( k, r ) {}
    Matches query( const BinStr& ) const;
    Matches query( const Number& ) const;

    void build( const NumTable& );
    void build( const BinTable& );
};

} // namespace

#endif
