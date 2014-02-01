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

const Number rcut_m1[] = {
        0b1111111111111111111111111111111111111111111111111111111111111111
    };
const int rcut_sh1[] = {
        0
    };

const Number rcut_m2[] = {
        0b1111111111111111111111111111111100000000000000000000000000000000,
        0b0000000000000000000000000000000011111111111111111111111111111111
    };
const int rcut_sh2[] = {
        32
    };

const Number rcut_m3[] = {
        0b1111111111111111111110000000000000000000000000000000000000000000,
        0b0000000000000000000001111111111111111111110000000000000000000000,
        0b0000000000000000000000000000000000000000001111111111111111111111
    };
const int rcut_sh3[] = {
        43,
        22,
        0
    };

const Number rcut_m4[] = {
        0b1111111111111111000000000000000000000000000000000000000000000000,
        0b0000000000000000111111111111111100000000000000000000000000000000,
        0b0000000000000000000000000000000011111111111111110000000000000000,
        0b0000000000000000000000000000000000000000000000001111111111111111
    };
const int rcut_sh4[] = {
        48,
        32,
        16,
        0
    };

const Number rcut_m5[] = {
        0b1111111111110000000000000000000000000000000000000000000000000000,
        0b0000000000001111111111111000000000000000000000000000000000000000,
        0b0000000000000000000000000111111111111100000000000000000000000000,
        0b0000000000000000000000000000000000000011111111111110000000000000,
        0b0000000000000000000000000000000000000000000000000001111111111111
    };
const int rcut_sh5[] = {
        52,
        39,
        26,
        13,
        0
    };

const Number rcut_m6[] = {
        0b1111111111000000000000000000000000000000000000000000000000000000,
        0b0000000000111111111100000000000000000000000000000000000000000000,
        0b0000000000000000000011111111111000000000000000000000000000000000,
        0b0000000000000000000000000000000111111111110000000000000000000000,
        0b0000000000000000000000000000000000000000001111111111100000000000,
        0b0000000000000000000000000000000000000000000000000000011111111111
    };
const int rcut_sh6[] = {
        54,
        44,
        33,
        22,
        11,
        0
    };

const Number rcut_m7[] = {
        0b1111111110000000000000000000000000000000000000000000000000000000,
        0b0000000001111111110000000000000000000000000000000000000000000000,
        0b0000000000000000001111111110000000000000000000000000000000000000,
        0b0000000000000000000000000001111111110000000000000000000000000000,
        0b0000000000000000000000000000000000001111111110000000000000000000,
        0b0000000000000000000000000000000000000000000001111111110000000000,
        0b0000000000000000000000000000000000000000000000000000001111111111
    };
const int rcut_sh7[] = {
        55,
        46,
        37,
        28,
        19,
        10,
        0
    };

const Number rcut_m8[] = {
        0b1111111100000000000000000000000000000000000000000000000000000000,
        0b0000000011111111000000000000000000000000000000000000000000000000,
        0b0000000000000000111111110000000000000000000000000000000000000000,
        0b0000000000000000000000001111111100000000000000000000000000000000,
        0b0000000000000000000000000000000011111111000000000000000000000000,
        0b0000000000000000000000000000000000000000111111110000000000000000,
        0b0000000000000000000000000000000000000000000000001111111100000000,
        0b0000000000000000000000000000000000000000000000000000000011111111
    };
const int rcut_sh8[] = {
        56,
        48,
        40,
        32,
        24,
        16,
        8,
        0
    };

const Number* rcut_m[] = { rcut_m1, rcut_m2, rcut_m3, rcut_m4, rcut_m5, rcut_m6, rcut_m7, rcut_m8 };
const int* rcut_sh[] = { rcut_sh1, rcut_sh2, rcut_sh3, rcut_sh4, rcut_sh5, rcut_sh6, rcut_sh7, rcut_sh8 };

NumTable HEngine_s::rcut( const BinStr &item ) const
{
    return rcut( HEngine::binStr2Number( item ) );
}

NumTable HEngine_s::rcut( const Number &num ) const
{
    NumTable result;
    for ( unsigned i = 0; i < m_r; i++ )
    {
        Number sub = ( rcut_m[m_r - 1][i] & num ) >> rcut_sh[m_r - 1][i];
        result.push_back( sub  );
    }

    return result;
}

Permutations HEngine_s::permute( const BinStr &item ) const
{
    return permute( HEngine::binStr2Number( item ) );
}

Permutations HEngine_s::permute( const Number &item, NumTable rcuts ) const
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

        NumTable t;
        for ( auto &s: rcuts )
        {
            t.push_back( s );
        }

        result.push_back( t );
    }

    return result;
}

unsigned HEngine_s::getRCutBitLength( const unsigned i ) const
{
    unsigned r = 0;
    for ( unsigned j = 0; j < i; j++ )
    {
        r += getRCutBitLength( j );
    }

    return 64 - rcut_sh[m_r - 1][i] - r;
}

NumTable HEngine_s::generateRange( const BinStr &item, const unsigned i ) const
{
    return generateRange( HEngine::binStr2Number( item ), i );
}

NumTable HEngine_s::generateRange( const Number &item, const unsigned i ) const
{
    NumTable result;
    result.push_back( item );
    unsigned len = getRCutBitLength( i );
    for ( unsigned j = 0; j < len; j++ )
    {
        unsigned s = 1 << j;
        Number x = item ^ s;
        result.push_back( x );
    }

    return result;
}

bool HEngine_s::sortPairsCmp( const Pair &i, const Pair &j )
{
    return ( i.second < j.second );
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

SignatureTable HEngine_s::searchPairs( const SignatureTable &table, const Number &val, const Number item, Matches *q, const unsigned k )
{
    SignatureTable result;
    Pair p = std::make_pair( 0, val );

    auto li = std::lower_bound( table.begin(), table.end(), p, sortPairsCmp );
    auto ui = std::upper_bound( li, table.end(), p, sortPairsCmp );

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
