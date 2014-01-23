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

} // namespace
