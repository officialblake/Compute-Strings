# Compute-Strings

A C++ program to compute the number of strings w of length n over {a,b,c,d}
with the following property: In any substring of length 6 of w, all three letters a, b, c and d
occur at least once. For example, strings like abbccdaabcasatisfy the property, but a string like
badaabcbcdcabaddoes not satisfy the property since the substring aabcbc does not have a d.