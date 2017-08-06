

/ Core graph library implementation.

.graph.initStructures:{[]

            .global.whiteSet:`symbol$();
            .global.graySet:`symbol$();
            .global.blackSet:`symbol$();
            .global.dfsMap:([] introducer:`symbol$(); node:`symbol$());
    }

.graph.updateDfsMap:{[introducerItem;nodeItem]
                            .global.dfsMap:.global.dfsMap upsert ([] introducer:enlist introducerItem; node:enlist nodeItem);
                    } 


.graph.generateInitialIntroducers:{[inputDict]
                                            L1:(key inputDict) except `;
                                            L2:(value inputDict);L2:L2 except L2[0];
                                            { val:y[x]; { .graph.updateDfsMap[y;x] }[;x] each val; }[;inputDict] each L1;
                                 }               

/ The main driver function that checks for the cycle.
    .graph.hasCycle:{[inputDict]                

                        // Initialize the tracking structures.
                        .graph.initStructures[];

                        // Generate initial introducers.
                        .graph.generateInitialIntroducers[inputDict];

                        // Add all the vertices to white set.
                        .global.whiteSet:(key inputDict) except `$"";
                         size:count .global.whiteSet;

                        // Loop till the white set is not empty.
                        while[(count .global.whiteSet)>0; 
                                          [     whiteItem:.global.whiteSet[0];
                                                $[1b=.graph.dfs[whiteItem;inputDict];:(`cycleError; .graph.traceCycle[]);::];
                                          ];  
                             ];               
                        (`noCycle; "")
                    }

/ The DFS search algorithm.
    .graph.dfs:{[currentItem;inputDict]
                            
                        $[currentItem=`;:0b;::];
                        0N!raze raze( "Exploring the item = "; string currentItem);
                        0N!raze raze( "White Set is = "; string .global.whiteSet);
                        0N!raze raze( "Gray Set is = "; string .global.graySet);
                        0N!raze raze( "Black Set is = "; string .global.blackSet);

                        // First move the item to gray set from white set. Since recursion uses global variables this check is needed.
                        $[(not currentItem in .global.graySet); [       .global.graySet:.global.graySet,currentItem;
                                                                        .global.whiteSet:.global.whiteSet except currentItem;
                                                                ];
                                                                ::
                         ];      

                        0N!raze raze( "After the move of item = "; string currentItem);
                        0N!raze raze( "White Set is = "; string .global.whiteSet);
                        0N!raze raze( "Gray Set is = "; string .global.graySet);
                        0N!raze raze( "Black Set is = "; string .global.blackSet);
                                 
                                               
                        // Now loop across all the connected neighbours of currentItem.
                        neighbours:inputDict[currentItem];
                        size:count neighbours;
                        $[size=1;neighbours:enlist neighbours;::];
                        iter:0;                    

                        0N!raze raze( "The total size of dependents on = "; string currentItem; " is = "; string size);    
                        0N!raze raze( "The type of list is = "; string (type neighbours); "h");    

                        // No more neighbours left this breaks the cycle.
                         $[((size=1) and (type neighbours)=0h);iter:size;::];

                        while[iter<size; 
                                         currentNeighbour:neighbours[iter]; 
                                         .graph.updateDfsMap[currentItem;currentNeighbour];
                                         skip:0b;
                                         $[(currentNeighbour in .global.blackSet)=1b; skip:1b; ::];                                           
                                            $[skip=0b; 
                                         
                                                  // If found in graySet then there is cycle.
                                                    [
                                                        $[(currentNeighbour in .global.graySet)=1b;:1b;::];
                                                        // do a recursive search. 
                                                        $[1b=.graph.dfs[currentNeighbour;inputDict];:1b;::];
                                                    ];::
                                             ];                                          
                                    iter:iter+1;                                  
                             ];

                                0N!raze raze( "moving item from gray to black set = "; string currentItem);
                                 // Move the current item to blackSet from graySet.
                                .global.blackSet:.global.blackSet,currentItem;
                                .global.graySet:.global.graySet except currentItem;
                                0N!raze raze( "White Set is = "; string .global.whiteSet);
                                0N!raze raze( "Gray Set is = "; string .global.graySet);
                                0N!raze raze( "Black Set is = "; string .global.blackSet);
                       0b           
                   }

.graph.traceCycle:{[]
                        tracerList:`symbol$();
                        seperator:"-->";
                        iter:0;
                        result:"";
                        nodeItem:first exec last node from .global.dfsMap;
                        tracerList:tracerList,nodeItem;
                        introducerItem:first exec last introducer from .global.dfsMap where node=nodeItem;
                        tracerList:tracerList,introducerItem;
                        
                        while[(introducerItem<>nodeItem);    introducerItem:first exec last introducer from .global.dfsMap where node = introducerItem;
                                                             $[(introducerItem<>`); [$[(not introducerItem in tracerList); 
                                                                                                    tracerList:tracerList,introducerItem; 
                                                                                                    [tracerList:.graph.getsubCycle[tracerList;introducerItem];introducerItem:nodeItem;]]
                                                                                    ];
                                                                                    [tracerList:tracerList,nodeItem; introducerItem:nodeItem;]];
                                                             0N!tracerList
                             ];

                        tracerList:reverse tracerList;        
                        while[(iter<(count tracerList));  result:raze (result;string tracerList[iter]); result:raze (result;seperator); iter:iter+1;];
                        result:result[til ( (count result)-(count seperator))];
                        result
                        
                    }

.graph.getsubCycle:{[tracerList;introducerItem]
                        
                        listIdx:tracerList?introducerItem;
                        tracerList:(0-((count tracerList)-(listIdx)))#tracerList;
                        tracerList:tracerList,introducerItem                        
                   }

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
 






