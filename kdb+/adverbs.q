

/ Write a lambda that substitutes every character in sList[x] found in myString with tList[x]
myString:"Anand Apparao Kulkarni";sList:"doi";tList:"epj";
{ssr[x;y;z]}/[myString;sList;tList] / Polyadic over.

/ Apply a function to a set of columns Example. convert `true`false into 1b/0b column given a table and list of columns.
t:([] Name:`Anand`Peter`Thomas;Age:1 2 3;isTall:`true`false`true;isSmart:`false`true`false);t
t {![x;();0b;(enlist y)!(enlist ((';{$[x~`true;1b;0b]});y))]}/`isTall`isSmart /works perfect.

/Improved version. Takes t, columnList and lambda to apply on those columns. return table result.
{x {![x;();0b;(enlist y)!(enlist ((';z);y))]}[;;z]/y}[t;`isTall`isSmart;{$[x~`true;1b;0b]}] /works perfect using list directly via eachboth.
{x {![x;();0b;(enlist y)!enlist (z;y)]}[;;z]/y}[t;`isTall`isSmart;{{$[x~`true;1b;0b]}each x}] / Convert the columns to boolean 1b/0b.

{x {![x;();0b;(enlist y)!enlist (z;y)]}[;;z]/y}[t;enlist `Age;{{x+1}each x}] / Bump Age by 1.
{x {![x;();0b;(enlist y)!enlist ((';z);y)]}[;;z]/y}[t;enlist `Age;{x+1}] / Bump Age by 1 using each both [ simplifies lambda ].


/ Write a function given a, d and n. Generate the first n AP numbers starting from a.
.f.func:{{min(x+y;z)}[;y;x+y*z-1]\[x]};
.f.func[2;4;10]

/ Write a function given a, r and n. Generate the first n GP numbers starting from a.
.f.func:{"j"${min(x*y;z)}[;y;x*y xexp z-1]\[x]};
.f.func[2;3;10]

/ Another variant of either ap/gp with fixed iterations without using min/max function.
.f.func:{$[`ap~x;
            {(-1+z){x+y}[;y]\x}[y[0];y[1];y[2]];
            {(-1+z){x*y}[;y]\x}[y[0];y[1];y[2]]
          ]
        }

results:{z[x;y]}[;(1;2;15);.f.func] each `ap`gp

14 {x+y}[;2]\3
{(z-1){x+y}[;y]\x}[2;3;10]

1. first -1#{(z-1){x+y}[;y]\x}[2;3;10]
2. {(z-1){x+y}[;y]/x}[2;3;10]
3. {x+y*z-1}[2;3;10]

/ Iterative ap and gp without using adverbs.
.utl.ap:{z#sums x,z#y};.utl.ap[2;3;10]
.utl.ap:{(+)\[x,(z-1)#y]};.utl.ap[2;3;10]
.utl.gp:{(*)\[x,z#y]};.utl.gp[2;3;10]

.utl.ap1:{(+)\[x,(z-1)#y]};
\ts do[10000;.utl.ap1[2;3;10]] /23 1456j

.utl.ap2:{{min(x+y;z)}[;y;x+y*z-1]\[x]};
\ts do[10000;.utl.ap2[2;3;10]] /115 1456j

/ Hence .utl.ap1 is a better variant.
























