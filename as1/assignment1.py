#! /usr/bin/env python2.7
import sys
import os
from operator import mul

# hardcode the 1,000-digit number required for exercise 2
n  = """
73167176531330624919225119674426574742355349194934
96983520312774506326239578318016984801869478851843
85861560789112949495459501737958331952853208805511
12540698747158523863050715693290963295227443043557
66896648950445244523161731856403098711121722383113
62229893423380308135336276614282806444486645238749
30358907296290491560440772390713810515859307960866
70172427121883998797908792274921901699720888093776
65727333001053367881220235421809751254540594752243
52584907711670556013604839586446706324415722155397
53697817977846174064955149290862569321978468622482
83972241375657056057490261407972968652414535100474
82166370484403199890008895243450658541227588666881
16427171479924442928230863465674813919123162824586
17866458359124566529476545682848912883142607690042
24219022671055626321111109370544217506941658960408
07198403850962455444362981230987879927244284909188
84580156166097919133875499200524063689912560717606
05886116467109405077541002256983155200055935729725
71636269561882670428252483600823257530420752963450
"""

def prob1(term, course):
    """
    Write a python script that creates the following directories for a given term
    and course:
        assignments
        examples
        exams
        lecture_notes
        submissions
    Also create a symbolic link to
    /usr/local/classes/eecs/<term>/<class>/public_html called 'website', and a
    link to /usr/local/classes/eecs/<term>/<class>/handin called 'handin'.

    It is your responsibility to ensure that you don't attempt to create a
    directory that already exists. Make use of the os, sys, and getopt modules,
    with both short and long form options for term and course.
    """
    prefix = term + "/" + course + "/"

    dirs = ["assignments", "examples", "exams", "lecture_notes", "submissions"]
    paths = [prefix + d for d in dirs]

    symlink_source = "/usr/local/classes/eecs/" + prefix + "public_html"
    symlink_name = prefix + "website"

    link_source = "/usr/local/classes/eecs/" + prefix + "handin"
    link_name = prefix + "handin"

    paths.append(symlink_source)
    paths.append(link_source)

    for p in paths:
        if not os.path.exists(p):
            # create all dirs recursively, becuause of link and symlink in paths
            os.mkdirs(p)
    if not os.path.exists(prefix + symlink_name):
        os.symlink(symlink_source, symlink_name)
    if not os.path.exists(prefix + link_name):
        os.link(link_source, link_name)

def prob2():
    # Find the greatest product of five consecutive digits in the 1000-digit number.
    return max(reduce(mul, n[i:i + 5], 1) for i in range(len(n) - 4))

def prob3():
    """
    Using names.txt, a 46K text file containing over five-thousand first names,
    begin by sorting it into alphabetical order. Then working out the alphabetical
    value for each name, multiply this value by its alphabetical position in the
    list to obtain a name score. For example, when the list is sorted into
    alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the
    938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
    What is the total of all the name scores in the file? See the posted examples
    for how to work with a file. For this, A = 1, B = 2, etc. 
    """

def prob4():
    """
    The nth term of the sequence of triangle numbers is given by, tn = ½ n (n+1);
    so the first ten triangle numbers are:
    1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
    By converting each letter in a word to a number corresponding to its
    alphabetical position and adding these values we form a word value. For
    example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value
    is a triangle number then we shall call the word a triangle word. Using
    words.txt, a 16K text file containing nearly two-thousand common English
    words, how many are triangle words? 
    """
    
def main():
    pass

if __name__ == "__main__":
    main()
