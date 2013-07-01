#! /usr/bin/env python2.7
import sys
import getopt
import os
from operator import mul

# hardcode the 1,000-digit number required for exercise 2
n  =[7, 3, 1, 6, 7, 1, 7, 6, 5, 3, 1, 3, 3, 0,
6, 2, 4, 9, 1, 9, 2, 2, 5, 1, 1, 9, 6, 7, 4,
4, 2, 6, 5, 7, 4, 7, 4, 2, 3, 5, 5, 3, 4, 9,
1, 9, 4, 9, 3, 4, 9, 6, 9, 8, 3, 5, 2, 0, 3,
1, 2, 7, 7, 4, 5, 0, 6, 3, 2, 6, 2, 3, 9, 5,
7, 8, 3, 1, 8, 0, 1, 6, 9, 8, 4, 8, 0, 1, 8,
6, 9, 4, 7, 8, 8, 5, 1, 8, 4, 3, 8, 5, 8, 6,
1, 5, 6, 0, 7, 8, 9, 1, 1, 2, 9, 4, 9, 4, 9,
5, 4, 5, 9, 5, 0, 1, 7, 3, 7, 9, 5, 8, 3, 3,
1, 9, 5, 2, 8, 5, 3, 2, 0, 8, 8, 0, 5, 5, 1,
1, 1, 2, 5, 4, 0, 6, 9, 8, 7, 4, 7, 1, 5, 8,
5, 2, 3, 8, 6, 3, 0, 5, 0, 7, 1, 5, 6, 9, 3,
2, 9, 0, 9, 6, 3, 2, 9, 5, 2, 2, 7, 4, 4, 3,
0, 4, 3, 5, 5, 7, 6, 6, 8, 9, 6, 6, 4, 8, 9,
5, 0, 4, 4, 5, 2, 4, 4, 5, 2, 3, 1, 6, 1, 7,
3, 1, 8, 5, 6, 4, 0, 3, 0, 9, 8, 7, 1, 1, 1,
2, 1, 7, 2, 2, 3, 8, 3, 1, 1, 3, 6, 2, 2, 2,
9, 8, 9, 3, 4, 2, 3, 3, 8, 0, 3, 0, 8, 1, 3,
5, 3, 3, 6, 2, 7, 6, 6, 1, 4, 2, 8, 2, 8, 0,
6, 4, 4, 4, 4, 8, 6, 6, 4, 5, 2, 3, 8, 7, 4,
9, 3, 0, 3, 5, 8, 9, 0, 7, 2, 9, 6, 2, 9, 0,
4, 9, 1, 5, 6, 0, 4, 4, 0, 7, 7, 2, 3, 9, 0,
7, 1, 3, 8, 1, 0, 5, 1, 5, 8, 5, 9, 3, 0, 7,
9, 6, 0, 8, 6, 6, 7, 0, 1, 7, 2, 4, 2, 7, 1,
2, 1, 8, 8, 3, 9, 9, 8, 7, 9, 7, 9, 0, 8, 7,
9, 2, 2, 7, 4, 9, 2, 1, 9, 0, 1, 6, 9, 9, 7,
2, 0, 8, 8, 8, 0, 9, 3, 7, 7, 6, 6, 5, 7, 2,
7, 3, 3, 3, 0, 0, 1, 0, 5, 3, 3, 6, 7, 8, 8,
1, 2, 2, 0, 2, 3, 5, 4, 2, 1, 8, 0, 9, 7, 5,
1, 2, 5, 4, 5, 4, 0, 5, 9, 4, 7, 5, 2, 2, 4,
3, 5, 2, 5, 8, 4, 9, 0, 7, 7, 1, 1, 6, 7, 0,
5, 5, 6, 0, 1, 3, 6, 0, 4, 8, 3, 9, 5, 8, 6,
4, 4, 6, 7, 0, 6, 3, 2, 4, 4, 1, 5, 7, 2, 2,
1, 5, 5, 3, 9, 7, 5, 3, 6, 9, 7, 8, 1, 7, 9,
7, 7, 8, 4, 6, 1, 7, 4, 0, 6, 4, 9, 5, 5, 1,
4, 9, 2, 9, 0, 8, 6, 2, 5, 6, 9, 3, 2, 1, 9,
7, 8, 4, 6, 8, 6, 2, 2, 4, 8, 2, 8, 3, 9, 7,
2, 2, 4, 1, 3, 7, 5, 6, 5, 7, 0, 5, 6, 0, 5,
7, 4, 9, 0, 2, 6, 1, 4, 0, 7, 9, 7, 2, 9, 6,
8, 6, 5, 2, 4, 1, 4, 5, 3, 5, 1, 0, 0, 4, 7,
4, 8, 2, 1, 6, 6, 3, 7, 0, 4, 8, 4, 4, 0, 3,
1, 9, 9, 8, 9, 0, 0, 0, 8, 8, 9, 5, 2, 4, 3,
4, 5, 0, 6, 5, 8, 5, 4, 1, 2, 2, 7, 5, 8, 8,
6, 6, 6, 8, 8, 1, 1, 6, 4, 2, 7, 1, 7, 1, 4,
7, 9, 9, 2, 4, 4, 4, 2, 9, 2, 8, 2, 3, 0, 8,
6, 3, 4, 6, 5, 6, 7, 4, 8, 1, 3, 9, 1, 9, 1,
2, 3, 1, 6, 2, 8, 2, 4, 5, 8, 6, 1, 7, 8, 6,
6, 4, 5, 8, 3, 5, 9, 1, 2, 4, 5, 6, 6, 5, 2,
9, 4, 7, 6, 5, 4, 5, 6, 8, 2, 8, 4, 8, 9, 1,
2, 8, 8, 3, 1, 4, 2, 6, 0, 7, 6, 9, 0, 0, 4,
2, 2, 4, 2, 1, 9, 0, 2, 2, 6, 7, 1, 0, 5, 5,
6, 2, 6, 3, 2, 1, 1, 1, 1, 1, 0, 9, 3, 7, 0,
5, 4, 4, 2, 1, 7, 5, 0, 6, 9, 4, 1, 6, 5, 8,
9, 6, 0, 4, 0, 8, 0, 7, 1, 9, 8, 4, 0, 3, 8,
5, 0, 9, 6, 2, 4, 5, 5, 4, 4, 4, 3, 6, 2, 9,
8, 1, 2, 3, 0, 9, 8, 7, 8, 7, 9, 9, 2, 7, 2,
4, 4, 2, 8, 4, 9, 0, 9, 1, 8, 8, 8, 4, 5, 8,
0, 1, 5, 6, 1, 6, 6, 0, 9, 7, 9, 1, 9, 1, 3,
3, 8, 7, 5, 4, 9, 9, 2, 0, 0, 5, 2, 4, 0, 6,
3, 6, 8, 9, 9, 1, 2, 5, 6, 0, 7, 1, 7, 6, 0,
6, 0, 5, 8, 8, 6, 1, 1, 6, 4, 6, 7, 1, 0, 9,
4, 0, 5, 0, 7, 7, 5, 4, 1, 0, 0, 2, 2, 5, 6,
9, 8, 3, 1, 5, 5, 2, 0, 0, 0, 5, 5, 9, 3, 5,
7, 2, 9, 7, 2, 5, 7, 1, 6, 3, 6, 2, 6, 9, 5,
6, 1, 8, 8, 2, 6, 7, 0, 4, 2, 8, 2, 5, 2, 4,
8, 3, 6, 0, 0, 8, 2, 3, 2, 5, 7, 5, 3, 0, 4,
2, 0, 7, 5, 2, 9, 6, 3, 4, 5, 0]
 
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
    return reduce(mul, (max(reduce(mul, (n[i:i + 5], 1)) for i in range(len(n) - 4))))

def prob3():
    """
    Using names.txt, a 46K text file containing over five-thousand first names,
    begin by sorting it into alphabetical order. Then working out the alphabetical
    value for each name, multiply this value by its alphabetical position in the
    list to obtain a name score. For example, when the list is sorted into
    alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the
    938th name in the list. So, COLIN would obtain a score of 938 x 53 = 49714.
    What is the total of all the name scores in the file? See the posted examples
    for how to work with a file. For this, A = 1, B = 2, etc. 
    """
def score(word):
    # assuming uppercase, since all the names are
    score = 0
    for c in word:
        score += ord(c) - 64
    return score

def prob4():
    """
    The nth term of the sequence of triangle numbers is given by, tn = .5 * n (n+1);
    so the first ten triangle numbers are:
    1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
    By converting each letter in a word to a number corresponding to its
    alphabetical position and adding these values we form a word value. For
    example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value
    is a triangle number then we shall call the word a triangle word. Using
    words.txt, a 16K text file containing nearly two-thousand common English
    words, how many are triangle words? 
    """
    triangles = [sum(range(1, n+1)) for n in range(50)]    
    names = open('names.txt', 'r')
    hits = []
    for n in names.read().split(','):
        if score(n.strip('"')) in triangles:
            hits.append(n)
    names.close()
    return len(hits)

def main():
    # mostly copied out of the docs at http://docs.python.org/2/library/getopt.html
    try:
        opts, args = getopt.getopt(sys.argv[1:], "1234")
    except getopt.GetoptError as err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        sys.exit(2)
    for o, a in opts:
        if o == "-1":
            prob1(a[0], a[1])
        elif o == "-2":
            print prob2()
        elif o == "-3":
            print prob3()
        elif o == "-4":
            print prob4()
        else:
            print "try again with a problem number"
            sys.exit()
if __name__ == "__main__":
    main()
