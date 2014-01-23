/**
 * @author VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine.h"
#include "gtest/gtest.h"

using namespace hengine;

TEST( HEngine, Bin2dec )
{
    Number n = HEngine::bin2dec( "1111" );
    EXPECT_EQ( 15, n );

    n = HEngine::bin2dec( "10001000" );
    EXPECT_EQ( 136, n );

    n = HEngine::bin2dec( "1111111111111111111111111111111111111111111111111111111111111111" );
    EXPECT_EQ( 18446744073709551615ull, n );

    n = HEngine::bin2dec( "1111111111111111111111111111111111111111111111111111111100000000" );
    EXPECT_EQ( 18446744073709551360ull, n );

    n = HEngine::bin2dec( "1111000011111111" );
    EXPECT_EQ( 61695ull, n );
}

TEST( HEngine, Dec2bin )
{
    std::string n = HEngine::dec2bin( 15 );
    EXPECT_EQ( "0000000000000000000000000000000000000000000000000000000000001111", n );

    n = HEngine::dec2bin( 18446744073709551615ull );
    EXPECT_EQ( "1111111111111111111111111111111111111111111111111111111111111111", n );
}

TEST( HEngine, HamminDistance )
{
    auto d = HEngine::getHammingDistance( HEngine::bin2dec( "1111" ), HEngine::bin2dec( "0000" ) );
    EXPECT_EQ( 4, d );

    d = HEngine::getHammingDistance( "1111", "1111" );
    EXPECT_EQ( 0, d );

    d = HEngine::getHammingDistance( "1111", "1110" );
    EXPECT_EQ( 1, d );

    d = HEngine::getHammingDistance( "1111", "0110" );
    EXPECT_EQ( 2, d );

    d = HEngine::getHammingDistance( "1111", "0100" );
    EXPECT_EQ( 3, d );

    d = HEngine::getHammingDistance( "1111111111111111111111111111111111111111111111111111111111111111", "1111111111111111111111111111111111111111111111111111111111111111" );
    EXPECT_EQ( 0, d );

    d = HEngine::getHammingDistance( "1111111111111111111111111111111111111111111111111111111111111111", "1111111111111111111111111111111111111111111111111111111111111110" );
    EXPECT_EQ( 1, d );

    d = HEngine::getHammingDistance( "0000000000000000000000000000000000000000000000000000000000000000", "1111111111111111111111111111111111111111111111111111111111111111" );
    EXPECT_EQ( 64, d );

    d = HEngine::getHammingDistance( 1, 3 );
    EXPECT_EQ( 1, d );

}
