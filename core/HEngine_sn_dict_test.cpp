/**
 * @author VaL Doroshchuk
 * @license GNU GPL v2
 */

#include "HEngine_sn.h"
#include "gtest/gtest.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string>
#include <sstream>

#include <limits.h>
#include <time.h>

#include <sys/resource.h>
#include <sys/times.h>


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
            db.push_back( HEngine::number2BinStr( h ) );
        }

        dict.close();

        std::ifstream q;
        q.open( "data/db/table.txt", std::ifstream::in );
        while ( getline( q, line ) )
        {
            Number h;

            std::istringstream reader( line );
            reader >> h;
            query.push_back( HEngine::number2BinStr( h ) );
        }

        q.close();

        e = HEngine_sn( db, 1 );
    }

    virtual void TearDown()
    {
    }

    BinTable db;
    BinTable query;
    HEngine_sn e;
    time_t start_time;
};

TEST_F( SameDictTest, DictQuery )
{
    int c = 0;
    for ( auto &i:query )
    {
        Matches res = e.query( i );
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
