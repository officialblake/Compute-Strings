# Compute-Strings

A C++ program that will compute the number of strings w of length n over {a,b,c,d}
with the following property: In any substring of length 6 of w, all three letters a, b, c and d
occur at least once. For example, strings like abbccdaabcasatisfy the property, but a string like
badaabcbcdcabaddoes not satisfy the property since the substring aabcbc does not have a d.

## Running the program

GMP is required to run this program. 

On unix based systems, this program can be run via: 

``` g++ main.cpp dfa.cpp -lgmpxx -lgmp -o proj1.out ```

followed by 

``` proj1.txt ```

This program can also be run via the makefile. The makefile is curretly optimized for ARM based systems, so the path to the GPM package will need to be updated on x86 systems. 