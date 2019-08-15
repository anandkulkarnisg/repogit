
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
/parse "update k:{ { `$ string x } each x}[k] from t"
f:{ { `$ string x } each x};
![t;();0b;(enlist `k)!(enlist (f;`k))]


/ New definition.
.utl.doPivot:{[t;k;p;v;f]
                        P:asc ?[t;();();(?:;p)];
                        tinfo:type ?[t;();();p];
                        $[tinfo<>11h;[t:![t;();0b;(enlist p)!(enlist (f;p))];];::];
                        ?[t;();(enlist k)!enlist k;(#;`P;(!;p;v))]
             }


.utl.doPivot:{[t;k;p;v;func]
                        P:asc ?[t;();();(?:;p)];
                        t:![t;();0b;(enlist p)!(enlist (func;p))];
                        t    
                        /?[t;();(enlist k)!enlist k;(#;`P;(!;p;v))]
             }



.utl.doPivot[t;`k;`p;`v;{}]    / works as expected!
.utl.doPivot[t;`p;`k;`v;f]    / does not work!
.utl.doPivot[t;`v;`p;`k;{}]    / works as expected!














