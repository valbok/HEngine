/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine.h"
#include <bitset>

namespace hengine
{

Number HEngine::bin2dec( std::string num )
{
    std::bitset<64ul> x( num );

    return x.to_ullong();
}

std::string HEngine::dec2bin( Number num )
{
    return std::bitset<64>( num ).to_string();
}

Number HEngine::getHammingDistance( BinStr hash1, BinStr hash2 )
{
    return getHammingDistance( bin2dec( hash1 ), bin2dec( hash2 ) );
}

Number HEngine::getHammingDistance( Number hash1, Number hash2 )
{
    Number x = hash1 ^ hash2;
    const Number m1  = 0x5555555555555555ULL;
    const Number m2  = 0x3333333333333333ULL;
    const Number h01 = 0x0101010101010101ULL;
    const Number m4  = 0x0f0f0f0f0f0f0f0fULL;

    x -= ( x >> 1 ) & m1;

    x = ( x & m2 ) + ( ( x >> 2 ) & m2 );

    x = ( x + ( x >> 4 ) ) & m4;

    return ( x * h01 ) >> 56;
}

} // namespace
