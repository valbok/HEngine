/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine_s.h"
#include <algorithm>

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

Permutations HEngine_s::permute( const BinStr &item, Table rcuts ) const
{
    Permutations result;
    if ( rcuts.size() == 0 )
    {
        rcuts = rcut( item );
    }

    for ( unsigned i = 0; i < m_r; i++ )
    {
        auto first = rcuts[0];
        rcuts[0] = rcuts[i];
        rcuts[i] = first;

        Table t;
        for ( auto &s: rcuts )
        {
            t.push_back( s );
        }

        result.push_back( t );
    }

    return result;
}

Table HEngine_s::generateRange( const BinStr &item )
{
    Table result;
    result.push_back( item );
    for ( unsigned i = 0; i < item.length(); i++ )
    {
        BinStr dig = item[i] == '0' ? "1" : "0";
        result.push_back( item.substr( 0, i ) + dig + item.substr( i + 1 ) );
    }

    return result;
}

bool HEngine_s::sortPairsCmp( const Pair& i, const Pair& j )
{
    return ( i.second[0] < j.second[0] );
}

void HEngine_s::sortSignatureTable( SignatureTable &table )
{
    sort( table.begin(), table.end(), sortPairsCmp );
}

void HEngine_s::sortSignatureSet( SignatureSet &set )
{
    for ( unsigned i = 0; i < set.size(); i++ )
    {
        sortSignatureTable( set[i] );
    }
}

Pair HEngine_s::searchPair( const SignatureTable& table, const BinStr& val )
{
    Table v;
    v.push_back( val );

    return searchPair( table, std::make_pair( "", v ) );
}

Pair HEngine_s::searchPair( const SignatureTable& table, const Pair& val )
{
    auto i = std::lower_bound( table.begin(), table.end(), val, sortPairsCmp );

    Pair result;
    if ( i != table.end() && !( val.second[0] < (*i).second[0] ) )
    {
        result = *i;
    }

    return result;
}
} // namespace
