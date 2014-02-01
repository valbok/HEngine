/**
 * @author VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine_sn.h"
#include "gtest/gtest.h"

#include <iostream>
#include <fstream>

using namespace hengine;

class SameDictTest: public testing::Test
{
protected:

    virtual void SetUp()
    {
        std::string line;
        std::ifstream dict;
        dict.open( "data/db/table.txt", std::ifstream::in );
        while ( getline( dict, line ) )
        {
            Number h;

            std::istringstream reader( line );
            reader >> h;
            db.push_back( h );
        }

        dict.close();

        std::ifstream q;
        q.open( "data/db/table.txt", std::ifstream::in );
        while ( getline( q, line ) )
        {
            Number h;

            std::istringstream reader( line );
            reader >> h;
            query.push_back( h );
        }

        q.close();
        e = new HEngine_sn( 1 );
        e->build( db );
    }

    virtual void TearDown()
    {
    }

    NumTable db;
    NumTable query;
    HEngine_sn* e;
};

TEST_F( SameDictTest, DictQuery )
{
    int c = 0;
    for ( auto &i:query )
    {
        Matches res = e->query( i );
        for ( auto &ir:res )
        {
            if ( i == ir.first )
            {
                c++;
            }
        }

    }

    EXPECT_EQ( db.size(), c );
}


class LennaFaceDictTest: public testing::Test
{
protected:

    virtual void SetUp()
    {
        std::string line;
        std::ifstream dict;
        dict.open( "data/db/lenna_full.txt", std::ifstream::in );
        while ( getline( dict, line ) )
        {
            Number h;

            std::istringstream reader( line );
            reader >> h;
            db.push_back( h );
        }

        dict.close();

        std::ifstream q;
        q.open( "data/query/matched_lenna_face.txt", std::ifstream::in );
        while ( getline( q, line ) )
        {
            Number h;

            std::istringstream reader( line );
            reader >> h;
            query.push_back( h );
        }

        q.close();

        e = new HEngine_sn( 7 );
        e->build( db );
    }

    virtual void TearDown()
    {
    }

    NumTable db;
    NumTable query;
    HEngine_sn *e;
    time_t start_time;
};

TEST_F( LennaFaceDictTest, DictQuery )
{
    int c = 0;
    for ( auto &i:query )
    {
        Matches res = e->query( i );
        if ( res.size() > 0 )
            c++;
    }

    EXPECT_EQ( query.size(), c );
}

