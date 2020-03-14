
iList:10 4 12 7 3 5 2;w:1 0 4 3 2 6 5
iList[iasc w] / sorted by weights.

iList:10 4 12 7 3 5 2;w:1 0 4 3 2 6 4
iList[iasc w] / sorted by weights but if weights are same then sort by actual value [ ascending ].

t:iList!w;
{raze{asc y[x]}[;group x] each distinct asc value x}[iList!w]

iList:10 4 12 7 3 5 2;w:1 0 4 3 2 6 5
iList[iasc w] / sorted by weights.

iList:5 4 3 2 1 0;w:1 1 1 1 1 1
{raze{asc y[x]}[;group x] each distinct asc value x}[iList!w] / sorts by weight first and then sorts by ascending value with in same weight.

t:([] iList:10 4 12 7 3 5 2;w:1 0 4 3 2 6 4);t
exec iList from `w`iList xasc t / Alternative table based solution.


iList:13 1 7 2 10 11 3 6 8 4 9 5 12;w:0 4 3 1 2 12 6 5 9 8 7 11 10
iList[iasc w] / sorted by weights.

