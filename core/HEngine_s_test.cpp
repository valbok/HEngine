/**
 * @author VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine_sn.h"
#include "gtest/gtest.h"

#include <algorithm>

using namespace hengine;

TEST( HEngine_sn, HammingDistance )
{
    HEngine_sn e( BinTable(), 4 );

    EXPECT_EQ( 4, e.getHammingDistanceBound() );
}

TEST( HEngine_sn, AutSegmentationFactor )
{
    HEngine_sn e( BinTable(), 4 );

    EXPECT_EQ( 4, e.getHammingDistanceBound() );
    EXPECT_EQ( 3, e.getSegmentationFactor() );
}

TEST( HEngine_sn, CustomSegmentationFactor )
{
    HEngine_sn e( BinTable(), 4, 4 );

    EXPECT_EQ( 4, e.getHammingDistanceBound() );
    EXPECT_EQ( 4, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor5 )
{
    HEngine_sn e( BinTable(), 5 );

    EXPECT_EQ( 4, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor6 )
{
    HEngine_sn e( BinTable(), 6 );

    EXPECT_EQ( 4, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor7 )
{
    HEngine_sn e( BinTable(), 7 );

    EXPECT_EQ( 5, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor8 )
{
    HEngine_sn e( BinTable(), 8 );

    EXPECT_EQ( 5, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor9 )
{
    HEngine_sn e( BinTable(), 9 );

    EXPECT_EQ( 6, e.getSegmentationFactor() );
}

TEST( HEngine_sn, SegmentationFactor10 )
{
    HEngine_sn e( BinTable(), 10 );

    EXPECT_EQ( 6, e.getSegmentationFactor() );
}

TEST( HEngine_sn, RCut3 )
{
    HEngine_sn e( BinTable(), 4 );

    BinTable t = e.rcut( "1111111111111111111110000000000000000000001111111111111111111111" );
    EXPECT_EQ( 3, t.size() );
    EXPECT_EQ( "111111111111111111111", t[0] );
    EXPECT_EQ( "000000000000000000000", t[1] );
    EXPECT_EQ( "1111111111111111111111", t[2] );
}

TEST( HEngine_sn, RCut4 )
{
    HEngine_sn e( BinTable(), 4, 4 );

    BinTable t = e.rcut( "0000000000000000111111111111111100000000000000001111111111111111" );
    EXPECT_EQ( 4, t.size() );
    EXPECT_EQ( "0000000000000000", t[0] );
    EXPECT_EQ( "1111111111111111", t[1] );
    EXPECT_EQ( "0000000000000000", t[2] );
    EXPECT_EQ( "1111111111111111", t[3] );
}

TEST( HEngine_sn, RCut7 )
{
    HEngine_sn e( BinTable(), 7 );

    BinTable t = e.rcut( "1111111111110000000000001111111111110000000000001111111111111111" );
    EXPECT_EQ( 5, t.size() );
    EXPECT_EQ( "111111111111", t[0] );
    EXPECT_EQ( "000000000000", t[1] );
    EXPECT_EQ( "111111111111", t[2] );
    EXPECT_EQ( "000000000000", t[3] );
    EXPECT_EQ( "1111111111111111", t[4] );
}

TEST( HEngine_sn, Permute )
{
    HEngine_sn e( BinTable(), 4 );

    Permutations t = e.permute( "1111111111111111111110000000000000000000001111111111111111111111" );
    EXPECT_EQ( 3, t.size() );
    EXPECT_EQ( "111111111111111111111", t[0][0] );
    EXPECT_EQ( "000000000000000000000", t[0][1] );
    EXPECT_EQ( "1111111111111111111111", t[0][2] );

    EXPECT_EQ( "000000000000000000000", t[1][0] );
    EXPECT_EQ( "111111111111111111111", t[1][1] );
    EXPECT_EQ( "1111111111111111111111", t[1][2] );

    EXPECT_EQ( "1111111111111111111111", t[2][0] );
    EXPECT_EQ( "111111111111111111111", t[2][1] );
    EXPECT_EQ( "000000000000000000000", t[2][2] );
}

TEST( HEngine_sn, Permute4 )
{
    HEngine_sn e( BinTable(), 4, 4 );

    Permutations t = e.permute( "0000000000000000111111111111111100000000000000001111111111111111" );
    EXPECT_EQ( 4, t.size() );
    EXPECT_EQ( "0000000000000000", t[0][0] );
    EXPECT_EQ( "1111111111111111", t[0][1] );
    EXPECT_EQ( "0000000000000000", t[0][2] );
    EXPECT_EQ( "1111111111111111", t[0][3] );

    EXPECT_EQ( "1111111111111111", t[1][0] );
    EXPECT_EQ( "0000000000000000", t[1][1] );
    EXPECT_EQ( "0000000000000000", t[1][2] );
    EXPECT_EQ( "1111111111111111", t[1][3] );

    EXPECT_EQ( "0000000000000000", t[2][0] );
    EXPECT_EQ( "0000000000000000", t[2][1] );
    EXPECT_EQ( "1111111111111111", t[2][2] );
    EXPECT_EQ( "1111111111111111", t[2][3] );

    EXPECT_EQ( "1111111111111111", t[3][0] );
    EXPECT_EQ( "0000000000000000", t[3][1] );
    EXPECT_EQ( "1111111111111111", t[3][2] );
    EXPECT_EQ( "0000000000000000", t[3][3] );
}


TEST( HEngine_sn, Range4 )
{
    BinStr s = "1111";
    BinTable t = HEngine_s::generateRange( s );

    EXPECT_EQ( 5, t.size() );
    EXPECT_EQ( "1111", t[0] );
    EXPECT_EQ( "0111", t[1] );
    EXPECT_EQ( "1011", t[2] );
    EXPECT_EQ( "1101", t[3] );
    EXPECT_EQ( "1110", t[4] );
}

TEST( HEngine_sn, Range8 )
{
    BinStr s = "00000000";
    BinTable t = HEngine_s::generateRange( s );

    EXPECT_EQ( 9, t.size() );
    EXPECT_EQ( "00000000", t[0] );
    EXPECT_EQ( "10000000", t[1] );
    EXPECT_EQ( "01000000", t[2] );
    EXPECT_EQ( "00100000", t[3] );
    EXPECT_EQ( "00010000", t[4] );
    EXPECT_EQ( "00001000", t[5] );
    EXPECT_EQ( "00000100", t[6] );
    EXPECT_EQ( "00000010", t[7] );
    EXPECT_EQ( "00000001", t[8] );
}

bool lower_bound_int_pair( std::pair<int,int> i,std::pair<int,int> j)
{
    return (i.first<j.first);
}

TEST( HEngine_sn, TmpPairIntSearch )
{
    std::vector<std::pair<int,int>> v;
    v.push_back( std::make_pair( 1, 10 ) );
    v.push_back( std::make_pair( 2, 20 ) );
    v.push_back( std::make_pair( 3, 30 ) );
    v.push_back( std::make_pair( 5, 50 ) );

    std::sort( v.begin(), v.end() );

    auto val = std::make_pair( 6, 0 );
    auto i = std::lower_bound( v.begin(), v.end(), val, lower_bound_int_pair );

    int r = -1;
    if ( i != v.end() && !( val.first < (*i).first ) )
    {
        r = (*i).first;
    }

    EXPECT_EQ( -1, r );

    val = std::make_pair( 3, 0 );
    i = std::lower_bound( v.begin(), v.end(), val, lower_bound_int_pair );
    if ( i != v.end() && !( val.first < (*i).first ) )
    {
        r = (*i).first;
    }

    EXPECT_EQ( 3, r );
}

bool so( std::pair<std::string,std::string> i,std::pair<std::string,std::string> j )
{
    return (i.first<j.first);
}

TEST( HEngine_sn, TmpPairStrSearch )
{
    std::vector<std::pair<std::string,std::string>> v;
    v.push_back( std::make_pair( "1001", "1" ) );
    v.push_back( std::make_pair( "0011", "2" ) );
    v.push_back( std::make_pair( "0110", "3" ) );
    v.push_back( std::make_pair( "1000", "5" ) );

    std::sort( v.begin(), v.end(), so );

    auto val = std::make_pair( "01111111", "" );
    auto i = std::lower_bound( v.begin(), v.end(), val, so );

    std::string r = "";
    if ( i != v.end() && !( val.first < (*i).first ) )
    {
        r = (*i).first;
    }

    EXPECT_EQ( "", r );

    val = std::make_pair( "0110", "" );
    i = std::lower_bound( v.begin(), v.end(), val, so );
    if ( i != v.end() && !( val.first < (*i).first ) )
    {
        r = (*i).first;
    }

    EXPECT_EQ( "0110", r );
}


TEST( HEngine_sn, SortSignatureTable )
{
    SignatureTable t;

    BinTable v1;
    v1.push_back( "1111" );
    v1.push_back( "0000" );
    t.push_back( std::make_pair( "1", v1 ) );

    BinTable v2;
    v2.push_back( "1110" );
    t.push_back( std::make_pair( "2", v2 ) );

    BinTable v3;
    v3.push_back( "0110" );
    t.push_back( std::make_pair( "3", v3 ) );

    BinTable v4;
    v4.push_back( "0000" );
    t.push_back( std::make_pair( "4", v4 ) );

    BinTable v5;
    v5.push_back( "0111" );
    t.push_back( std::make_pair( "5", v5 ) );

    HEngine_s::sortSignatureTable( t );

    EXPECT_EQ( "0000", t[0].second[0] );
    EXPECT_EQ( "0110", t[1].second[0] );
    EXPECT_EQ( "0111", t[2].second[0] );
    EXPECT_EQ( "1110", t[3].second[0] );
    EXPECT_EQ( "1111", t[4].second[0] );
}

TEST( HEngine_sn, SortSignatureSet )
{
    SignatureTable t1;

    BinTable v1;
    v1.push_back( "10" );
    v1.push_back( "00" );
    t1.push_back( std::make_pair( "1", v1 ) );

    BinTable v2;
    v2.push_back( "00" );
    t1.push_back( std::make_pair( "2", v2 ) );

    SignatureTable t2;

    BinTable v3;
    v3.push_back( "11" );
    t2.push_back( std::make_pair( "1", v3 ) );

    BinTable v4;
    v4.push_back( "01" );
    t2.push_back( std::make_pair( "2", v4 ) );

    SignatureSet set;
    set.push_back( t1 );
    set.push_back( t2 );

    HEngine_s::sortSignatureSet( set );

    EXPECT_EQ( "00", set[0][0].second[0] );
    EXPECT_EQ( "10", set[0][1].second[0] );
    EXPECT_EQ( "01", set[1][0].second[0] );
    EXPECT_EQ( "11", set[1][1].second[0] );
}

TEST( HEngine_sn, SignatureSearch )
{
    SignatureTable t;

    BinTable v1;
    v1.push_back( "1111" );
    v1.push_back( "0000" );
    v1.push_back( "0001" );
    v1.push_back( "0011" );
    t.push_back( std::make_pair( "1", v1 ) );

    BinTable v2;
    v2.push_back( "1110" );
    t.push_back( std::make_pair( "2", v2 ) );

    BinTable v3;
    v3.push_back( "0110" );
    t.push_back( std::make_pair( "3", v3 ) );

    BinTable v4;
    v4.push_back( "0000" );
    t.push_back( std::make_pair( "4", v4 ) );

    BinTable v5;
    v5.push_back( "0111" );
    t.push_back( std::make_pair( "5", v5 ) );

    HEngine_s::sortSignatureTable( t );

    auto p = HEngine_s::searchPairs( t, "0000" );

    EXPECT_EQ( "4", p[0].first );
    EXPECT_EQ( "0000", p[0].second[0] );

    p = HEngine_s::searchPairs( t, "1001" );

    EXPECT_EQ( 0, p.size() );

    p = HEngine_s::searchPairs( t, "1111" );

    EXPECT_EQ( "1", p[0].first );
    EXPECT_EQ( "1111", p[0].second[0] );

    p = HEngine_s::searchPairs( t, "0100" );

    EXPECT_EQ( 0, p.size() );
}

TEST( HEngine_sn, SignatureSearchMultiple )
{
    SignatureTable t;

    BinTable v1;
    v1.push_back( "1111" );
    t.push_back( std::make_pair( "1", v1 ) );

    BinTable v2;
    v2.push_back( "0000" );
    t.push_back( std::make_pair( "0", v2 ) );

    BinTable v3;
    v3.push_back( "1111" );
    t.push_back( std::make_pair( "11", v3 ) );

    BinTable v4;
    v4.push_back( "0000" );
    t.push_back( std::make_pair( "00", v4 ) );

    BinTable v5;
    v5.push_back( "0111" );
    t.push_back( std::make_pair( "5", v5 ) );

    HEngine_s::sortSignatureTable( t );

    auto p = HEngine_s::searchPairs( t, "0000" );

    EXPECT_EQ( 2, p.size() );
    EXPECT_EQ( "0", p[0].first );
    EXPECT_EQ( "0000", p[0].second[0] );
    EXPECT_EQ( "00", p[1].first );
    EXPECT_EQ( "0000", p[1].second[0] );

    p = HEngine_s::searchPairs( t, "1111" );

    EXPECT_EQ( 2, p.size() );
    EXPECT_EQ( "1", p[0].first );
    EXPECT_EQ( "1111", p[0].second[0] );
    EXPECT_EQ( "11", p[1].first );
    EXPECT_EQ( "1111", p[1].second[0] );

    p = HEngine_s::searchPairs( t, "1011" );
    EXPECT_EQ( 0, p.size() );

    p = HEngine_s::searchPairs( t, "0111" );
    EXPECT_EQ( 1, p.size() );
    EXPECT_EQ( "5", p[0].first );
    EXPECT_EQ( "0111", p[0].second[0] );
}
