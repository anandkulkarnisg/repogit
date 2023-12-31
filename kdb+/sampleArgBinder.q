



/ Set a input table as below.
t:([] c1:1 2 3;c2:2 3 4;c3:3 4 5;x:4 5 6;y:5 6 7);t


/ A Basic simple adder lambda 
t:update c3:{[a;b;c]c:a+b}[;;]'[c1;c2][c3] from t;

/ A simple functional update to add two columns bound into programmable third column.
t:![t;();0b;(enlist `c3)!(enlist ((';{[a;b;c]c:a+b});`c1;`c2;`c3))]

/ Wrap this in a functional update lambda.
t:![t;();0b;(enlist `c3)!(enlist ((';{[a;b;c]c:a+b});`c1;`c2;`c3))];

/ Wrapped inside a lambda in generic fashion.
t:{[w;x;y;z] ![w;();0b;(enlist z)!(enlist ((';{[a;b;c] c:a+b});x;y;z))]}[t;`c1;`c2;`c3]; /works
t:{[w;x;y;z] ![w;();0b;(enlist z)!(enlist ((';{[a;b;c] c:a+b});x;y;z))]}[t;`c1;`c2;`x]; /works


