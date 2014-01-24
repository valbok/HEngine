/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

#include <algorithm>
#include "HEngine_sn.h"

namespace hengine
{

void HEngine_sn::build()
{
    m_set = SignatureSet();
    for ( unsigned i = 0; i < m_r; i++ )
    {
        m_set.push_back( SignatureTable() );
    }

    for ( auto &item: m_db )
    {
        auto ps = permute( item );
        for ( unsigned i = 0; i < m_r; i++ )
        {
            m_set[i].push_back( std::make_pair( item, ps[i] ) );
        }
    }

    sortSignatureSet( m_set );
}

Matches HEngine_sn::query( const Number &num ) const
{
    return query( number2BinStr( num ) );
}

Matches HEngine_sn::query( const BinStr &item ) const
{
    Matches result;
    if ( m_set.size() == 0 )
    {
        return result;
    }

    auto rcuts = rcut( item );
    for ( unsigned i = 0; i < m_r; i++ )
    {
        // Generate all possible substrings that are within Hamming distance 1 of the first substring of cut
        // and then perform an exact match query on this substring in table using binary search.
        auto range = generateRange( rcuts[i] );
        for ( auto &sub: range )
        {
            searchPairs( m_set[i], sub, item, &result, m_k );
        }
    }

    return result;
}
} // namespace
