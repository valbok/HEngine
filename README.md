HEngine
=======

Prototype of HEngine concept described by Alex X. Liu, Ke Shen, Eric Torng in their paper "Large Scale Hamming Distance Query Processing" ICDE Conference, pages 553 - 564, 2011.

It is an attempt to solve Hamming distance range query problem in a large scale set.

As you can see in an following example, to compute hammind distance and fetch matched items from set of 752420 values takes around 0.04 sec when lanear searching takes not less 1 sec.

    HEngine/tests$ ./query 7 "data/db/table.txt" 
    Reading the dataset ........ done. 752420 hashes
    Building with 7 hamming distance bound ....... done
      
    Building time: 41.692 seconds
    query> 8149447334979397351
    Found 1 matches
    [0] 8149447334979397351

    HEngine query time: 0.04 seconds

    linear scaninng ... 
    Found 1 matches
    [0] 8149447334979397351

    Linear query time: 1.112 seconds

    query> 411930186871661727
    Found 1 matches
    [7] 5131685004167537807

    HEngine query time: 0.056 seconds

    linear scaninng ... 
    Found 1 matches
    [7] 5131685004167537807

    Linear query time: 1.136 seconds
