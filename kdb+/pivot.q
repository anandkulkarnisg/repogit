
/ Initialize data as below.
t:([]k:1 2 3 2 3;p:`xx`yy`zz`xx`yy;v:10 20 30 40 50);t

/ basic pivot building technique.
P:asc exec distinct p from t;pvt:exec P#(p!v) by k:k from t;pvt

/ Attempt to build the same using functional form [ aim is to generalize it ].
/ parse "exec distinct p from t"
/ parse "exec P#(p!v) by k:k from t"
P:?[t;();();(?:;`p)];pvt:?[t;();(enlist `k)!enlist `k;(#;`P;(!;`p;`v))];pvt


/ Aim to generalize this function now via lambda.
.utl.doPivot:{[t;k;p;v]
                P:asc ?[t;();();(?:;p)];
                ?[t;();(enlist k)!enlist k;(#;`P;(!;p;v))]
             }

/ Invocations!
.utl.doPivot[t;`k;`p;`v]    / works as expected!
.utl.doPivot[t;`p;`k;`v]    / does not work!
.utl.doPivot[t;`v;`p;`k]    / works as expected!

/ Failed case should look like below.
p    1    2    3
xx   10   40   0N 
yy   0N   20   50
zz   0N   0N   30

/ Trying same concept with symbol types on t1.
t1:([] k:`1`2`3`2`3;p:`xx`yy`zz`xx`yy;v:`10`20`30`40`50);t1
.utl.doPivot[t1;`p;`k;`v]    / works now!

/ So we need fix to columns names which are coming from k. If k type is numeric attempt to convert it symbol type for representation.
/ Temporary experimentation before building the final lambda.
delete t, f, k, P, k, p, v from `.
t:([]k:1 2 3 2 3;p:`xx`yy`zz`xx`yy;v:10 20 30 40 50);t
f:{ { `$ string x } each x};
k:`p; p:`k; v:`v;
P:asc ?[t;();();(?:;p)];
P:f[P];
t:![t;();0b;(enlist p)!(enlist (f;p))];
?[t;();(enlist k)!enlist k;(#;`P;(!;p;v))]

/ Final lambda is below.
.utl.doPivot:{[t;k;p;v;f]
                        P:asc ?[t;();();(?:;p)];
                        tinfo:type P;
                        $[tinfo<>11h;[P:f[P];t:![t;();0b;(enlist p)!(enlist (f;p))];];::];
                        ?[t;();(enlist k)!enlist k;(#;`P;(!;p;v))]
             }

.utl.doPivot[t;`k;`p;`v;{}]    / works as expected!
.utl.doPivot[t;`p;`k;`v;f]     / works as expected!
.utl.doPivot[t;`v;`p;`k;{}]    / works as expected!

/ doing pivoting in case where multiple values are present for criteria of pivot column (k) and column names (p).
t:([]k:1 2 3 2 3 2;p:`xx`yy`xx`xx`yy`xx;v:10 20 30 40 50 60);t
t1:select v by k,p from t;
P:asc exec distinct p from t1;
exec P#(p!v) by k:k from t1
