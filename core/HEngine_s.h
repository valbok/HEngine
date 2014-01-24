/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

/**
 * Abstract static implementation of HEngine
 */

#ifndef HENGINE_S_H
#define HENGINE_S_H

#include "HEngine.h"
#include <math.h>
#include <iterator>

namespace hengine
{

/**
 * List of permuted substrings using segmentation factor
 * @see rcut() and permute()
 */
typedef std::vector<BinTable> Permutations;

/**
 * Original string and list of permuted by segmentation factor
 */
typedef std::pair<BinStr, BinTable> Pair;

/**
 * i-th element is an index of substring placed to front of the string
 */
typedef std::vector<Pair> SignatureTable;

typedef std::vector<Pair>::const_iterator SignatureTable_const_iterator;

/**
 * List of signature tables
 */
typedef std::vector<SignatureTable> SignatureSet;

class HEngine_s: public HEngine
{
private:
    static Pair searchPair( const SignatureTable&, const Pair&, SignatureTable_const_iterator );

protected:

    /**
     * Hamming distance bound
     */
    unsigned m_k;

    /**
     * Segmentation factor
     */
    unsigned m_r;

    /**
     * Signature set of m_db for distance bound m_k and segmentation factor m_r
     */
    SignatureSet m_set;

protected:
    HEngine_s() {}

    /**
     * @param db
     * @param k Requested hamming distance bound
     * @param r Requested segmentation factor
     */
    HEngine_s( NumTable db, unsigned k, unsigned r = 0 )
    {
        BinTable t;
        for ( auto &h: db )
        {
            t.push_back( HEngine::number2BinStr( h ) );
        }

        m_db = t;
        init( k, r );
    }

    HEngine_s( BinTable db, unsigned k, unsigned r = 0 )
    {
        m_db = db;
        init( k, r );
    }

    void init( unsigned k, unsigned r = 0  )
    {
        m_k = k;
        // m_r must not be less than k/2 + 1
        m_r = r != 0 ? r : floor( ( ( m_k / 2.f ) + 1.f ) + 0.5 );
    }

    /**
     * Constructs m_r duplicates of m_db one for each signature
     */
    void build() {}

public:
    /**
     * Splits a string into r substrings,
     * where the first r − (m mod r) substrings have length ⌊m/r⌋
     * and the last m mod r substrings have length ⌈m/r⌉
     */
    BinTable rcut( const BinStr& ) const;
    BinTable rcut( const Number& ) const;

    Permutations permute( const BinStr&, BinTable rcuts = BinTable() ) const;

    inline unsigned getHammingDistanceBound() const
    {
        return m_k;
    }

    inline unsigned getSegmentationFactor() const
    {
        return m_r;
    }

    const SignatureSet& getSignatureSet() const
    {
        return m_set;
    }

    /**
     * Generates all possible substrings that are within Hamming distance 1
     */
    static BinTable generateRange( const BinStr& );

    /**
     * Sorts tables and sets to use binary searching.
     * Sorts ONLY per first permuted substring.
     */
    static bool sortPairsCmp( const Pair& i, const Pair& j );
    static void sortSignatureTable( SignatureTable& );
    static void sortSignatureSet( SignatureSet& );

    /**
     * Searches string in signature table using binary search.
     * It handles ONLY first substring/item from permuted table.
     */
    static SignatureTable searchPairs( const SignatureTable&, const BinStr&, const BinStr item = BinStr(), Matches *q = NULL, unsigned k = 64 );
    static SignatureTable searchPairs( const SignatureTable&, const Pair&, const BinStr item = BinStr(), Matches *q = NULL, unsigned k = 64 );

};

} // namespace

#endif
