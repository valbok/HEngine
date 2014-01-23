/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */


#include "HEngine_sn.h"

namespace hengine
{

Table HEngine_sn::permute( const BinStr &item ) const
{
    Table result;
    // First string must be the same as requested
    result.push_back( item );
    Table rcuts = rcut( item );
    for ( unsigned i = 1; i < m_r; i++ )
    {
        auto first = rcuts[0];
        rcuts[0] = rcuts[i];
        rcuts[i] = first;

        BinStr str;
        for ( auto &s: rcuts )
        {
            str += s;
        }

        result.push_back( str );
    }

    return result;
}

void HEngine_sn::build()
{
    m_set = SignatureSet();
    for ( unsigned i = 0; i < m_r; i++ )
    {
        m_set.push_back( SignatureTable() );
    }

    for ( auto &item: m_db )
    {
        auto ps = permute( item );
        // Size of ps must be the same as m_r
        for ( unsigned i = 0; i < m_r; i++ )
        {
            m_set[i].push_back( std::make_pair( ps[i], item ) );
        }
    }
}

} // namespace
