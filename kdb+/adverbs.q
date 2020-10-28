

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












