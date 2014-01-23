/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine_s.h"

namespace hengine
{

Table HEngine_s::rcut( const Number &num ) const
{
    return rcut( HEngine::dec2bin( num ) );
}

Table HEngine_s::rcut( const BinStr &item ) const
{
    Table result;
    unsigned q = 64 / m_r;

    for ( unsigned i = 0; i < m_r; i++ )
    {
        int m = q;
        if ( i == m_r - 1 )
        {
            q = item.length() - i * m;
        }

        result.push_back( item.substr( i * m, q ) );
    }

    return result;
}

} // namespace
