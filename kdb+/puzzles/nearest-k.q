/ Find k closest elements to a given value.Works for all edge cases!
/ Case 1
iList:12 16 22 30 35 39 42 45 48 50 53 55 56;X:35;K:4;
{$[(count x)<=y;x;y#x]}[iList[iasc abs iList-X] except X;K]

/ Case 2
iList:12 16 22 30 36 39 42 45 48 50 53 55 56;X:35;K:4;
{$[(count x)<=y;x;y#x]}[iList[iasc abs iList-X] except X;K]

/ Case 3
iList:5 7 8 9;X:7;K:5;
{$[(count x)<=y;x;y#x]}[iList[iasc abs iList-X] except X;K]


/ binary search.
iList:12 16 22 30 35 39 42 45 48 50 53 55 56;x:35;k:4;

/ Step 1 : reduce the list to K items each side on binarySearch Index of X item.
iList:iList[{(til x[1]+1) except (til x[0])}{(max(x[0];0);min(x[1];y-1))}[;count iList] {(neg x;x)}[k]+iList bin x] / Way 1
iList:{x[0]}[0 1 + {(max(x[0];0);min(x[1];y-1))}[;count iList] {(neg x;x)}[k]+iList bin x] _ iList / Way 2 sounds better.
/ Step2 : Identify the elements now like below.
{$[(count x)<=y;x;y#x]}[iList[iasc abs iList-X] except x;k]


/ Worst case.
iList:1 2 3 4 5 6 100;x:10;k:4;
iList:{x[0]}[0 1 + {(max(x[0];0);min(x[1];y-1))}[;count iList] {(neg x;x)}[k]+iList bin x] _ iList / Way 2 sounds better.
{$[(count x)<=y;x;y#x]}[iList[iasc abs iList-X] except x;k]

/ Rodion solution.
iList:12 16 22 30 35 39 42 45 48 50 53 55 56;x:35;k:4;
{y {x[;1]where y>rank x[;0]}[;z]{f:where not 0=x;(x,'til count x) f}abs x-y}[x;iList;k]
{x[;1]where y>rank x[;0]}[;k]{f:where not 0=x;(x,'til count x) f}abs iList-x

\ts do[10000;iList[k#iasc {f:where not 0=x;(x,'til count x) f}abs iList-x]] /9 3888j
\ts do[10000;{y {x[;1]where y>rank x[;0]}[;z]{f:where not 0=x;(x,'til count x) f}abs x-y}[x;iList;k]] /21 5344
