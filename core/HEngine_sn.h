/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */


/**
 * Non recursive static implementation of HEngine
 */

#ifndef HENGINE_SN_H
#define HENGINE_SN_H

#include "HEngine_s.h"

namespace hengine
{

class HEngine_sn: public HEngine_s
{

protected:
    void build();

public:
    HEngine_sn() {}
    HEngine_sn( BinTable db, unsigned k, unsigned r = 0 ): HEngine_s( db, k, r ) { build();}
    HEngine_sn( NumTable db, unsigned k, unsigned r = 0 ): HEngine_s( db, k, r ) { build();}
    Matches query( const BinStr& ) const;
    Matches query( const Number& ) const;
};

} // namespace

#endif
