/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

#define NO_FCGI_DEFINES

#include <string>
#include <map>
#include <stdlib.h>
#include <sstream>
#include "fcgi_stdio.h"
#include "HEngine_sn.h"

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace hengine;

int main()
{
    std::string port=":9000";
    int listenQueueBacklog = 400;
    if ( FCGX_Init() )
    {
       exit( 1 );
    }

    int listen_socket = FCGX_OpenSocket( port.c_str(), listenQueueBacklog );
    if ( listen_socket < 0 )
    {
       exit( 1 );
    }

    FCGX_Request request;
    if ( FCGX_InitRequest( &request,  listen_socket, 0 ) )
    {
       exit( 1 );
    }

    std::string header = "Content-type: text/html\r\n\r\n";
    NumTable db;
    std::map<Number,Number> posts;
    try
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        driver = get_driver_instance();
        con = driver->connect( "tcp://127.0.0.1:3306", "root", "" );
        con->setSchema( "artonym" );

        stmt = con->createStatement();
        res = stmt->executeQuery( "SELECT id, post_id, hash FROM art_image_hash" );
        while ( res->next() )
        {
            Number h = res->getUInt64( "hash" );
            db.push_back( h );
            posts[h] = res->getUInt64( "post_id" );
        }

        delete res;
        delete stmt;
        delete con;
    }
    catch ( sql::SQLException &e )
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "  << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    HEngine_sn e( 7 );
    e.build( db );

    while ( FCGX_Accept_r( &request ) == 0 )
    {
        NumTable q;
        Number hash;
        std::string query = FCGX_GetParam( "QUERY_STRING", request.envp );

        std::stringstream ss( query );
        while ( ss >> hash )
        {
            q.push_back( hash );

            if ( ss.peek() == ',' )
            {
                ss.ignore();
            }
        }

        std::string body = header;
        int c = 0;
        for ( auto &h: q)
        {
            Matches res = e.query( h );
            c += res.size();
            for ( auto &r: res )
            {
                body += std::to_string( posts[r.first] ) + ":" + std::to_string( r.first ) + ":" + std::to_string( r.second ) + "<br/>";
            }
        }

        FCGX_PutS( body.c_str(), request.out );
        FCGX_Finish_r( &request );
    }

    return 0;
}
