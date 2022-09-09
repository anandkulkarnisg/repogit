n:1000000
k:til n

q)/ search our plain list at start/mid/end
\ts do[1000; k?2]
1
\ts do[1000; k?`int$n%2]
437
\ts do[1000; k?n-2]
950

/ time searching our ordered list
l:`s#k
\ts do[1000;l?2]
1
\ts do[1000;l?`int$n%2]
4
\ts do[1000;l?n-2]
2

.Q.gc[]

\\

"u"$.z.p
"i"$.z.p
"j"$.z.p

