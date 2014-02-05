HEngine
=======

Prototype of HEngine concept described by Alex X. Liu, Ke Shen, Eric Torng in their paper "Large Scale Hamming Distance Query Processing" ICDE Conference, pages 553 - 564, 2011.

It is an attempt to solve a Hamming distance range query problem in a large scale set.

Is supposed to handle only 64 bit binary strings.

    tests$ ./matches 7 data/db/table.txt data/query/face2.txt
    Reading the dataset ........ done. 752420 db hashes and 343 query hashes.
    Building with 7 hamming distance bound ....... done.

    Building time: 13.772 seconds

    Searching HEngine matches .......
    found 100 total matches. Query time: 0.1 seconds

    Searching linear matches .......
    found 100 total matches. Linear query time: 7.104 seconds
    

As you can see it is much more faster than linear scanning.
