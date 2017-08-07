.graph.hasCycle[d]
                       
/ Input is a dictionary of a DAG where each edge each key represents the vertex and values represent the direction to which edges flow from this vertex.

    d.1:`2`3;
    d.2:`3;
    d.3:0#`;
    d.4:`5;
    d.5:`6;
    d.6:`4;

    / delete d from `.

    d.1:`2;
    d.2:`3;    
    d.3:0#`;

   / delete d from `.

   d.1:`2;
   d.2:`3;
   d.3:`1;

/ .graph.hasCycle[d]

   d.1:`2;
   d.2:`11;

/ .graph.hasCycle[d]

    d.1:`2;
    d.2:`1;

/ .graph.hasCycle[d]
/ The above is a inputDict for the DFS search of a cycle in the DFS.

    d.a:`b;
    d.b:`c;
    d.c:`d`e`f;
    d.d:0#`;
    d.e:0#`;
    d.f:`g`h;
    d.g:0#`;
    d.h:`a;

    / delete d from `.
    d.a:`b;
    d.b:`c;
    d.c:`d;
    d.d:`e;
    d.e:`f`g;   
    d.f:`a;
    d.g:0#`;
/ .graph.hasCycle[d]

/ Another test sample.

    d.a:`b;
    d.b:`c;
    d.c:`d`e`f;
    d.d:0#`;
    d.e:0#`;
    d.f:`g`h;
    d.g:0#`;
    d.h:`a;
    / delete d from `.
    / .graph.hasCycle[d]


/ delete d from `.

    d.a:`b;
    d.b:`c;
    d.c:`d`e;
    d.d:`f`g`h;
    d.e:0#`;
    d.f:0#`;
    d.g:`h;
    d.h:`i;
    d.i:0#`;    
    .graph.hasCycle[d]
  
/  delete d from `.

    d.a:`b;
    d.b:`c;
    d.c:`d`e`f;
    d.d:0#`;
    d.e:0#`;
    d.f:`g;
    d.g:`h;
    d.h:`i;
    d.i:`e;
    /.graph.hasCycle[d]

/ delete d from `.

    d.a:`b;
    d.b:`c;
    d.c:`d;
    d.d:`e;
    d.e:`b;
    .graph.hasCycle[d]
    

/ delete d from `.
    
  d.a:`b;
  d.b:`c;
  d.c:`d`e`f;
  d.d:0#`;
  d.e:`g;
  d.f:0#`;
  d.g:`h;
  d.h:`g`e
  
/ cycle in cycle [ sub cycle ]
/ .graph.hasCycle[d]
 

/ A case with three cycles.

/ delete d from `.

    d.a:`b;
    d.b:`c;
    d.c:`d`e`f;
    d.d:0#`;
    d.e:`g;
    d.f:0#`;
    d.g:`i`h;
    d.h:`j;
    d.i:`e`c;
    d.j:`g;

.graph.hasCycle[d] // Test cases pass.
/ First case detects : (`cycleError;"e-->g-->i-->e")
/ Remove i to e connection.
   d.i:`c;  
/ Now detects the other cycle : (`cycleError;"c-->e-->g-->i-->c")
/ Now remove the i to c connection.
   d.i:0#`;

/ Now exposes the final cycle : (`cycleError;"g-->h-->j-->g")
/ Remove the connection j to g.
  d.j:0#`;  
/ Finally no cylces present! (`noCycle;"")
/ All test cases passed.

.graph.DAGCycleCheck[d;`n]

/ The example given in the video by Tushar Roy.
/ delete d from `.

    d.1:`2`3;
    d.2:`3;
    d.3:0#`;
    d.4:`1`5;
    d.5:`6;
    d.6:`4;
    /d.6:0#`;

.graph.DAGCycleCheck[d;`n]    


p:.graph.getCleanGraph[d]

p[0]
p[1]









