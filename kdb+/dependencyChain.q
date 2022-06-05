

/ Input for the problem.
t:([] c1:`P1`P2`P3`P4`P5;st:2021.03.03T13:20:25.000 2021.03.03T13:20:28.000 2021.03.03T13:20:29.000 2021.03.03T13:20:37.000 2021.03.03T13:20:43.000;
                         et:2021.03.03T13:20:30.000 2021.03.03T13:20:33.000 2021.03.03T13:20:34.000 2021.03.03T13:20:42.000 2021.03.03T13:20:48.000);t

/Generate dependency chain for stacking alerts in c1 to the first in chain of dependency.
t1:update isi:{[x;y;z]exec c1 from t where st within (x;y),i>z}'[st;et;i] from t;
d:exec c1,isi from p:ungroup select c1,isi from t1;
d:d[`isi]!d[`c1];
t1:t1 lj `c1 xkey select c1:isi, ma from update ma:{$[y[x]~`;x;::];p:y[x];v:p;while[v<>`;[p:v;v:y[v]]];p}[;d] each key d from p;
t1:update ma:c1 from t1 where null ma;
t lj `c1 xkey select c1, ma from t1

/Disatisfaction because solution is not vectorized and is iterative [ will blowup in performance when table is sufficiently large ].





