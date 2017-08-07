/ Core graph library implementation.

.graph.initStructures:{[]

            .global.whiteSet:`symbol$();
            .global.graySet:`symbol$();
            .global.blackSet:`symbol$();
            .global.dfsMap:([] introducer:`symbol$(); node:`symbol$());
    }


.graph.cleanupStructures:{[]
                           delete whiteSet, graySet, blackSet, dfsMap from `.global;
                         }


.graph.updateDfsMap:{[introducerItem;nodeItem]
                            .global.dfsMap:.global.dfsMap upsert ([] introducer:enlist introducerItem; node:enlist nodeItem);
                    } 


.graph.generateInitialIntroducers:{[inputDict]
                                            L1:(key inputDict) except `;
                                            L2:(value inputDict);L2:L2 except L2[0];
                                            { val:y[x]; { .graph.updateDfsMap[y;x] }[;x] each val; }[;inputDict] each L1;
                                 }


.graph.moveFromWhiteSetToGraySet:{[itemToBeMoved]
                                    .global.graySet:.global.graySet,itemToBeMoved;
                                    .global.whiteSet:.global.whiteSet except itemToBeMoved;
                                 }

.graph.moveFromGraySetToBlackSet:{[itemToBeMoved]
                                    .global.blackSet:.global.blackSet,itemToBeMoved;
                                    .global.graySet:.global.graySet except itemToBeMoved;  
                                 } 


.graph.DAGCycleCheck:{[inputDict;inputDebugMode]                        
                        
                        $[((type inputDebugMode)<>-11h) or (not (lower inputDebugMode) in `y`n);:`$"badDebugMode-use either `y`n";::];    
                        resultPair:.graph.hasCycle[inputDict];
                        $[inputDebugMode=`n;.graph.cleanupStructures[];::];
                        $[resultPair[0]=`cycleError;:(1b;`$resultPair[1]);:(0b;`$resultPair[1])];
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

                        // First move the item to gray set from white set. Since recursion uses global variables this check is needed.
                        $[(not currentItem in .global.graySet); [.graph.moveFromWhiteSetToGraySet[currentItem];];::];      

                        // Now loop across all the connected neighbours of currentItem.
                        neighbours:inputDict[currentItem];
                        size:count neighbours;
                        $[size=1;neighbours:enlist neighbours;::];
                        iter:0;                    

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

                       // Move the current item to blackSet from graySet.
                       .graph.moveFromGraySetToBlackSet[currentItem];

                       // Return all good.
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


.graph.getCleanGraph:{[inputDict]

                        // inputDict:d;
                        // This function takes a DAG graph with multiple cycles and elimitaes the cycle edges and outputs a clean graph if possible.
                        resultPair:.graph.DAGCycleCheck[inputDict;`n];    

                        // If no cycle found just return the dictionary as it is.
                        $[resultPair[0]=0b;:inputDict;::];

                        // If a cycle is found attempt a removal unless graph is clean.
                        logtbl:([cycle:`symbol$()]; actionmessage:`symbol$());

                        // Loop until we find and repair all vertices causing the cycles in the Graph.
                        while[(resultPair[0]<>0b);      
                                                        / Extract the cycle information.
                                                        cycleInfo:resultPair[1];                                                        
                                                        cycleEdges:-2#(raze (`$ ("-->" vs (string cycleInfo))));
                                                        
                                                        / Identify the source and targetVertex which are causing loop.
                                                        srcVertex:cycleEdges[0];
                                                        targetVertex:cycleEdges[1];

                                                        / Now strip the targetVertex from the sourceVertex in the dictionary.
                                                        valItems:inputDict[srcVertex];
                                                        $[(count valItems)=1;valItems:enlist valItems;::];
                                                        valItems:valItems except targetVertex;
                                                        $[(count valItems)=1;valItems:valItems[0];::];

                                                        / Update the dictionary here.
                                                        inputDict[srcVertex]:valItems;                                                        

                                                        / Log the action into a table returned later to the caller. so he knows what action has been taken.
                                                        actionMessage:`$ raze ("removed the edge from vertex = "; string srcVertex; " to vertex = "; string targetVertex); 
                                                        logtbl:logtbl upsert ([cycle:enlist cycleInfo]; actionmessage:enlist actionMessage);

                                                        / Rerun the cycle check again after the repair. It will break when no cycles are found anymore.
                                                        resultPair:.graph.DAGCycleCheck[inputDict;`n];
                            ];

                        (inputDict;logtbl)
                       }



