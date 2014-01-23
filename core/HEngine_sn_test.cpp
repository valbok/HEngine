/**
 * @author VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine_sn.h"
#include "gtest/gtest.h"

using namespace hengine;

TEST( HEngine_sn, DefaultConstructor )
{
    HEngine_sn e( Table(), 0 );
}

TEST( HEngine_sn, HammingDistance )
{
    HEngine_sn e( Table(), 4 );

    EXPECT_EQ( 4, e.getHammingDistance() );
}

TEST( HEngine_sn, AutSegmentationFactor )
{
    HEngine_sn e( Table(), 4 );

    EXPECT_EQ( 4, e.getHammingDistance() );
    EXPECT_EQ( 3, e.getSegmentationFactor() );
}

TEST( HEngine_sn, CustomSegmentationFactor )
{
    HEngine_sn e( Table(), 4, 4 );

    EXPECT_EQ( 4, e.getHammingDistance() );
    EXPECT_EQ( 4, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor5 )
{
    HEngine_sn e( Table(), 5 );

    EXPECT_EQ( 4, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor6 )
{
    HEngine_sn e( Table(), 6 );

    EXPECT_EQ( 4, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor7 )
{
    HEngine_sn e( Table(), 7 );

    EXPECT_EQ( 5, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor8 )
{
    HEngine_sn e( Table(), 8 );

    EXPECT_EQ( 5, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor9 )
{
    HEngine_sn e( Table(), 9 );

    EXPECT_EQ( 6, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor10 )
{
    HEngine_sn e( Table(), 10 );

    EXPECT_EQ( 6, e.getSegmentationFactor() );
}

TEST( HEngine_sn, RCut3 )
{
    HEngine_sn e( Table(), 4 );

    Table t = e.rcut( "1111111111111111111110000000000000000000001111111111111111111111" );
    EXPECT_EQ( 3, t.size() );
    EXPECT_EQ( "111111111111111111111", t[0] );
    EXPECT_EQ( "000000000000000000000", t[1] );
    EXPECT_EQ( "1111111111111111111111", t[2] );
}

TEST( HEngine_sn, RCut4 )
{
    HEngine_sn e( Table(), 4, 4 );

    Table t = e.rcut( "0000000000000000111111111111111100000000000000001111111111111111" );
    EXPECT_EQ( 4, t.size() );
    EXPECT_EQ( "0000000000000000", t[0] );
    EXPECT_EQ( "1111111111111111", t[1] );
    EXPECT_EQ( "0000000000000000", t[2] );
    EXPECT_EQ( "1111111111111111", t[3] );
}

TEST( HEngine_sn, RCut7 )
{
    HEngine_sn e( Table(), 7 );

    Table t = e.rcut( "1111111111110000000000001111111111110000000000001111111111111111" );
    EXPECT_EQ( 5, t.size() );
    EXPECT_EQ( "111111111111", t[0] );
    EXPECT_EQ( "000000000000", t[1] );
    EXPECT_EQ( "111111111111", t[2] );
    EXPECT_EQ( "000000000000", t[3] );
    EXPECT_EQ( "1111111111111111", t[4] );
}

TEST( HEngine_sn, Permute )
{
    HEngine_sn e( Table(), 4 );

    Table t = e.permute( "1111111111111111111110000000000000000000001111111111111111111111" );
    EXPECT_EQ( 3, t.size() );
    EXPECT_EQ( "1111111111111111111110000000000000000000001111111111111111111111", t[0] );
    EXPECT_EQ( "0000000000000000000001111111111111111111111111111111111111111111", t[1] );
    EXPECT_EQ( "1111111111111111111111111111111111111111111000000000000000000000", t[2] );
}

TEST( HEngine_sn, Permute4 )
{
    HEngine_sn e( Table(), 4, 4 );

    Table t = e.permute( "0000000000000000111111111111111100000000000000001111111111111111" );
    EXPECT_EQ( 4, t.size() );
    EXPECT_EQ( "0000000000000000111111111111111100000000000000001111111111111111", t[0] );
    EXPECT_EQ( "1111111111111111000000000000000000000000000000001111111111111111", t[1] );
    EXPECT_EQ( "0000000000000000000000000000000011111111111111111111111111111111", t[2] );
    EXPECT_EQ( "1111111111111111000000000000000011111111111111110000000000000000", t[3] );
}

TEST( HEngine_sn, Build )
{
    Table t;
    t.push_back( "1111111111111111111110000000000000000000001111111111111111111111" );
    t.push_back( "0000000000000000000001111111111111111111110000000000000000000000" );
    t.push_back( "1111111111100000000001111111111100000000001111111111000000000000" );
    t.push_back( "1010101010101010101010101010101010101010101010101010101010101010" );

    HEngine_sn e( t, 4 );

    const SignatureSet set = e.getSignatureSet();
    EXPECT_EQ( 3, set.size() );
    EXPECT_EQ( 4, set[0].size() );
    EXPECT_EQ( 4, set[1].size() );
    EXPECT_EQ( 4, set[2].size() );

    EXPECT_EQ( "1111111111111111111110000000000000000000001111111111111111111111", set[0][0].first );
    EXPECT_EQ( "0000000000000000000001111111111111111111110000000000000000000000", set[0][1].first );
    EXPECT_EQ( "1111111111100000000001111111111100000000001111111111000000000000", set[0][2].first );
    EXPECT_EQ( "1010101010101010101010101010101010101010101010101010101010101010", set[0][3].first );

    EXPECT_EQ( "0000000000000000000001111111111111111111111111111111111111111111", set[1][0].first );
    EXPECT_EQ( "1111111111111111111110000000000000000000000000000000000000000000", set[1][1].first );

    EXPECT_EQ( "1111111111111111111111111111111111111111111000000000000000000000", set[2][0].first );
    EXPECT_EQ( "0000000000000000000000000000000000000000000111111111111111111111", set[2][1].first );
}
