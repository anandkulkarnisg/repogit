

/ Find first and second max price by each sym from the below data.
t:([] sym:`a`b`a`b`a`b`c`a`c`b`b;price:1 2 5 1 2 1 1 1 3 4 3);
t:update maxPrice:(max;price) fby sym from t; / Find max price for each sym.
t1:t lj `sym xkey select sym, nextMaxPrice from update nextMaxPrice:(max;price) fby sym from {select from x where price<>maxPrice}t; /Find next maxPrice for each sym.
select distinct sym, maxPrice, nextMaxPrice from t1

/ Best and simple solution.
select first desc price by sym from t /Simple solution.

/ Identify if a given list of numbers are noramlly distributed [ with a given level of tolerence ].
t:"26, 33, 65, 28, 34, 55, 25, 44, 50, 36, 26, 37, 43, 62, 35, 38, 45, 32, 28, 34";t:"J"$trim "," vs t;
mean:{sum x%count x}t;stdev:{t:sum {(x-y)xexp 2}[;y] each x;sqrt t%count x}[t;mean];
zscore:{(x-y)%z}'[;mean;stdev] each t;
check1:((+)/[{(abs x)<=1} each zscore])%count t;check1:check1*100;
check2:((+)/[{(abs x)<=2} each zscore])%count t;check2:check2*100;
check3:((+)/[{(abs x)<=3} each zscore])%count t;check3:check3*100;
(and/)(check1>68;check2>95;check3>99.7)


t:"26, 33, 65, 28, 34, 55, 25, 44, 50, 36, 26, 37, 43, 62, 35, 38, 45, 32, 28, 34";t:"J"$trim "," vs t;
t:([] val:t);
mean:{sum x%count x}exec val from t;stdev:{t:sum {(x-y)xexp 2}[;y] each x;sqrt t%count x}[exec val from t;mean];
t:update zscore:{(x-y)%z}'[val;mean;stdev] from t;
l:{(abs x)<=y};
t:update dev1:l'[zscore;1],dev2:l'[zscore;2],dev3:l'[zscore;3] from t;
t:update dev1:100*{sum x%count x}[dev1], dev2:100*{sum x%count x}[dev2],dev3:100*{sum x%count x}[dev3] from t;
(and/)(first each value exec dev1, dev2, dev3 from 1#t)>(68f;95f;99.7f)


t:"26,33,65,28,34,55,25,44,50,36,26,37,43,62,35,38,45,32,28,34";t:"J"$trim "," vs t;
p:{"f"${100*x%y}[;count x] sum each {{x>=abs y}[;x] each 1 2 3}[{(x-y)%z}[x;avg[x];sdev[x]]]}[t];
{(and/){x within y}'[x;{(neg y;y)+/:x}[;y]each (68.5 95 99.7)]}[p;1.5]


t:1+til 200;
p:{"f"${100*x%y}[;count x] sum each {{x>=abs y}[;x] each 1 2 3}[{(x-y)%z}[x;avg[x];sdev[x]]]}[t];
{(and/){x within y}'[x;{(neg y;y)+/:x}[;y]each (68.5 95 99.7)]}[p;10.5]


.stat.isNormallyDistributed:{
                                / Use this for debug : x:"26, 33, 65, 28, 34, 55, 25, 44, 50, 36, 26, 37, 43, 62, 35, 38, 45, 32, 28, 34"; y:2;
                                t:"J"$trim "," vs x;
                                p:{"f"${100*x%y}[;count x] sum each {{x>=abs y}[;x] each 1 2 3}[{(x-y)%z}[x;avg[x];sdev[x]]]}[t];
                                {(and/){x within y}'[x;{(neg y;y)+/:x}[;y]each (68.5 95 99.7)]}[p;y]
                            }
\ts do[100000;.stat.isNormallyDistributed["26, 33, 65, 28, 34, 55, 25, 44, 50, 36, 26, 37, 43, 62, 35, 38, 45, 32, 28, 34";1.5]] /5417 2992j


t:([] c1:1 2 3 4;c2:5 6 7 8);dict:`col1`col2`col3!(`anand;12j;13.75f);
/ update each dict key as a column and corrosponding value in dictionary as column value in table.
t:{y xkey x}[;key dict]t{![x;();0b;{x!y}[enlist y;$[-11h=type z[y];enlist enlist z[y];enlist z[y]]]]}[;;dict]/key dict /key dict is passed as y. dict is passed as z.


/ find out total percentagge of numbers below 20 [ or any given number ].
t:10 11 17 21 23 27 31 38 43;{{x%y}[+/[{x<y}[x;y]];count x]}[t;20]


\ts do[10000;{{x%y}[+/[{x<y}[x;y]];count x]}[t;20]] /19 3184j
\ts do[10000;{+/[x<y]%count x}[t;24]] /12 2096j


/ Find maximum price for all symbols from the list below.
t:([] sym:`a`b`a`b`a`a`a`b`c`a`c`b`c`a;price:1 2 1 3 4 3 4 2 3 4 1 3 2 4)
\ts do[10000;select distinct sym, price:(max;price) fby sym from t]   /79 2096j
\ts do[10000;select {first -1#asc x}price by sym from t] /73 2368j

/ Find minimum price for all symbols from the list below.
t:([] sym:`a`b`a`b`a`a`a`b`c`a`c`b`c`a;price:1 2 1 3 4 3 4 2 3 4 1 3 2 4)
\ts do[10000;select distinct sym, price:(min;price) fby sym from t]   /79 2096j

.stat.isNormallyDistributed:{
                                / Use this for debug : x:"26, 33, 65, 28, 34, 55, 25, 44, 50, 36, 26, 37, 43, 62, 35, 38, 45, 32, 28, 34"; y:2;
                                t:"J"$trim "," vs x;
                                p:{"f"${100*x%y}[;count x] sum each {{x>=abs y}[;x] each 1 2 3}[{(x-y)%z}[x;avg[x];sdev[x]]]}[t];
                                {(and/){x within y}'[x;{(neg y;y)+/:x}[;y]each (68.5 95 99.7)]}[p;y]
                            }

t:"26,33,65,28,34,55,25,44,50,36,26,37,43,62,35,38,45,32,28,34";t:"J"$trim "," vs t;
\ts do[10000;{all within[;.685 .95 .997+/:-1 1*.015] avg 1 2 3>=/:abs(x-avg x)%sdev x}[t]]  /156 4768j
\ts do[10000;.stat.isNormallyDistributed["26, 33, 65, 28, 34, 55, 25, 44, 50, 36, 26, 37, 43, 62, 35, 38, 45, 32, 28, 34";1.5]] /542 2496j


inputList:1 0 1 0 1 1 2 0 1 2 1 2 0 2 1 2 0 1 2 1 2 0 1 1;
\ts do[100000;(key p)!{count y[x]}[;p] each key p:group inputList]  /339 2928j
\ts do[100000;{(key x)!(count each value x)}[group inputList]]  /222 2272j

t:([] nameList:enlist `anand`peter`thomas`roger`george;selectStatus:enlist 10101b);t
\ts do[10000;?[?[ungroup t;enlist (=;`selectStatus;1b);0b;()];();();`nameList]]    /31 2912j
\ts do[10000;update selectNameList:{(group x!y)[1b]}'[nameList;selectStatus] from t]   /30 2688j


t1:([] nameList:enlist `anand`peter`thomas`roger`george;select1Status:enlist 10101b;select2Status:enlist 01111b);t1
update selectNameList:{(group x!y)[1b]}'[nameList;(&/)(select1Status;select2Status)] from t1















