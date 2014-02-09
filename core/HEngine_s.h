/**
 * @author VaL Doroshchuk
 * @copyright Alex X. Liu, Ke Shen, Eric Torng, VaL Doroshchuk
 * @license GNU GPL v2
 */

/**
 * Abstract implementation of HEngine using static/predefined hamming dinstance bound
 */

#ifndef HENGINE_S_H
#define HENGINE_S_H

#include "HEngine.h"
#include "../lib/bloom/bloom_filter.hpp"

#include <iterator>

namespace hengine
{

/**
 * List of permuted substrings using segmentation factor
 * @see rcut() and permute()
 */
typedef std::vector<NumTable> Permutations;

/**
 * Original string and first substring from a list of permuted by segmentation factor
 */
typedef std::pair<Number, Number> Pair;

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
     * Signature set of signature table for distance bound m_k and segmentation factor m_r
     */
    SignatureSet m_set;

    /**
     * List of Bloom filters one per signature table
     */
    std::vector<bloom_filter*> m_filters;

protected:
    /**
     * @param db
     * @param k Requested hamming distance bound
     * @param r Requested segmentation factor
     */
    HEngine_s( unsigned k, unsigned r = 0 )
    {
        m_k = k;
        auto sf = calcSegmentationFactor( m_k );
        m_r = ( r != 0  && ( r >= sf || r <= 64 ) ) ? r : sf;
    }

public:
    virtual ~HEngine_s()
    {
        for( unsigned i = 0; i < m_filters.size(); i++ )
        {
            delete m_filters[i];
        }
    }

    static unsigned calcSegmentationFactor( unsigned k )
    {
        return ( k / 2 ) + 1;
    }

    /**
     * Constructs m_r duplicates for each signature
     */
    virtual void build( const NumTable& ) {}

    /**
     * Splits a string into r substrings,
     * where the first r − (m mod r) substrings have length ⌊m/r⌋
     * and the last m mod r substrings have length ⌈m/r⌉
     */
    NumTable rcut( const BinStr& ) const;
    NumTable rcut( const Number& ) const;

    Permutations permute( const BinStr& ) const;
    Permutations permute( const Number&, NumTable rcuts = NumTable() ) const;

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
    NumTable generateRange( const BinStr&, const unsigned i = 0 ) const;
    NumTable generateRange( const Number&, const unsigned i = 0 ) const;

    /**
     * Returns count of bits for sub binary string
     * @see rcut()
     */
    unsigned getRCutBitLength( const unsigned i = 0 ) const;

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
    static SignatureTable searchPairs( const SignatureTable&, const Number&, const Number item = 0, Matches *q = NULL, unsigned k = 64 );

};

} // namespace

#endif
