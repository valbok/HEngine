/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

#include <algorithm>
#include "HEngine_sn.h"

#include <map>
#include <iostream>

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
        auto rcuts = rcut( item );
        auto ps = permute( item, rcuts );
        for ( unsigned i = 0; i < m_r; i++ )
        {
            auto t = ps[i];
            m_set[i].push_back( std::make_pair( item, t ) );
        }
    }

    sortSignatureSet( m_set );
}

QueryResult HEngine_sn::query( const Number& num ) const
{
    return query( dec2bin( num ) );
}

QueryResult HEngine_sn::query( const BinStr& item ) const
{
    std::map<BinStr, BinStr> m;
    auto rcuts = rcut( item );
    const Permutations ps = permute( item, rcuts );
    for ( unsigned i = 0; i < ps.size(); i++ )
    {
        const SignatureTable &table = m_set[i];
        //const Table &p = ps[i];
        const BinStr &cut = rcuts[i];

        // Generate all possible substrings that are within Hamming distance 1 of the first substring of cut
        // and then perform an exact match query on this substring in table using binary search.
        auto range = generateRange( cut );

        for ( auto &sub: range )
        {
            auto p = searchPair( table, sub );
            if ( p.first != "" )
            {
                m[p.first] = sub;
            }
        }
    }

    QueryResult result;
    for ( auto &f: m )
    {
        unsigned d = getHammingDistance( f.first, item );
        if ( d <= m_k )
        {
            result.push_back( std::make_pair( f.first, d ) );
        }
    }

    return result;
}

} // namespace
