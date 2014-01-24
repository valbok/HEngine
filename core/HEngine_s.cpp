/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine_s.h"
#include <algorithm>
#include <iostream>
namespace hengine
{

BinTable HEngine_s::rcut( const Number &num ) const
{
    return rcut( HEngine::number2BinStr( num ) );
}

BinTable HEngine_s::rcut( const BinStr &item ) const
{
    BinTable result;
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

Permutations HEngine_s::permute( const BinStr &item, BinTable rcuts ) const
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

        BinTable t;
        for ( auto &s: rcuts )
        {
            t.push_back( s );
        }

        result.push_back( t );
    }

    return result;
}

BinTable HEngine_s::generateRange( const BinStr &item )
{
    BinTable result;
    result.push_back( item );
    for ( unsigned i = 0; i < item.length(); i++ )
    {
        BinStr dig = item[i] == '0' ? "1" : "0";
        result.push_back( item.substr( 0, i ) + dig + item.substr( i + 1 ) );
    }

    return result;
}

bool HEngine_s::sortPairsCmp( const Pair &i, const Pair &j )
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

SignatureTable HEngine_s::searchPairs( const SignatureTable &table, const BinStr &val, const BinStr item, Matches *q, const unsigned k )
{
    BinTable v;
    v.push_back( val );

    return searchPairs( table, std::make_pair( "", v ), item, q, k );
}

SignatureTable HEngine_s::searchPairs( const SignatureTable &table, const Pair &val, const BinStr item, Matches *q, const unsigned k )
{
    SignatureTable result;
    auto li = std::lower_bound( table.begin(), table.end(), val, sortPairsCmp );
    auto ui = std::upper_bound( li, table.end(), val, sortPairsCmp );

    if ( li == table.end() || ui > table.end() )
    {
        return result;
    }

    unsigned d;
    for ( auto i = li; i != ui; ++i )
    {
        d = ( k >= 64 ) ? k : getHammingDistance( item, (*i).first );
        if ( d <= k )
        {
            result.push_back( *i );
            if ( q != NULL )
            {
                (*q)[(*i).first] = d;
            }
        }
    }

    return result;
}
} // namespace
