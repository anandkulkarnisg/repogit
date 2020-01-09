
/ Basic concept using adverbs.
{(z-1){x+y}[;y]\x}[1;3;10]   / AP
{(z-1){x*y}[;y]\x}[2;4;10]   / GP
1%{(z-1){x+y}[;y]\x}[1;3;10] / HP

/ putting it altogether.
generator:{$[x[0] in `ap`hp;op:(+);op:(*)];t:{{(z[0]-1){z/[x;y]}[;y;z[1]]\x}[x;y;(z[0];z[1])]}[x[1];y;(z;op)];$[x[0]=`hp;t:1%t;::];t};
resultList:{generator[(x;1);3;10]} peach `ap`gp`hp;







