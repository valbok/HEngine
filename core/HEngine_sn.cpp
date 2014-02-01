/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

#include <algorithm>
#include "HEngine_sn.h"
#include <iostream>
#include <sstream>

namespace hengine
{

void HEngine_sn::build()
{
    if ( m_db.size() == 0 )
    {
        return;
    }
    std::ostringstream oss;

    m_set = SignatureSet();
    for ( unsigned i = 0; i < m_r; i++ )
    {
        m_set.push_back( SignatureTable() );

        bloom_parameters parameters;
        parameters.projected_element_count = m_db.size();
        parameters.false_positive_probability = 0.2; // 1 in 10

        // Simple randomizer (optional)
        parameters.random_seed = i;
        parameters.compute_optimal_parameters();

        m_filters.push_back( new bloom_filter( parameters ) );
    }

    for ( auto &item: m_db )
    {
        auto ps = permute( item );
        for ( unsigned i = 0; i < m_r; i++ )
        {
            m_set[i].push_back( std::make_pair( item, ps[i][0] ) );

            if ( i < m_r - 1 )
            {
                oss << ps[i][0];
                m_filters[i]->insert( oss.str().c_str() );
            }
        }
    }

    sortSignatureSet( m_set );

}

Matches HEngine_sn::query( const BinStr &item ) const
{
    return query( binStr2Number( item ) );
}

Matches HEngine_sn::query( const Number &item ) const
{
    Matches result;
    if ( m_set.size() == 0 )
    {
        return result;
    }

    std::ostringstream oss;
    auto rcuts = rcut( item );
    for ( unsigned i = 0; i < m_r; i++ )
    {
        // Generate all possible substrings that are within Hamming distance 1 of the first substring of cut
        // and then perform an exact match query on this substring in table using binary search.
        auto range = generateRange( rcuts[i] );
        for ( auto &sub: range )
        {
            oss << sub;
            if ( i < m_r - 1 && !m_filters[i]->contains( oss.str().c_str() ) )
            {
                continue;
            }

            SignatureTable pairs = searchPairs( m_set[i], sub, item, &result, m_k );
        }
    }

    return result;
}
} // namespace
