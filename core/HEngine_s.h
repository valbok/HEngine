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

namespace hengine
{

/**
 * List of permuted substrings using segmentation factor
 * @see rcut() and permute()
 */
typedef std::vector<Table> Permutations;

/**
 * Original string and list of permuted by segmentation factor
 */
typedef std::pair<BinStr, Table> Pair;

/**
 * i-th element is an index of substring placed to front of the string
 */
typedef std::vector<Pair> SignatureTable;

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
    HEngine_s( Table db, unsigned k, unsigned r = 0 )
    {
        m_db = db;
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
    Table rcut( const BinStr& ) const;
    Table rcut( const Number& ) const;

    Permutations permute( const BinStr&, Table rcuts = Table() ) const;

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
    static Table generateRange( const BinStr& );

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
    static Pair searchPair( const SignatureTable&, const BinStr& );
    static Pair searchPair( const SignatureTable&, const Pair& );

};

} // namespace

#endif
