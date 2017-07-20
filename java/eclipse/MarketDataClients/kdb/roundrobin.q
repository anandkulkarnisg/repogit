/ Below is the round robin strategy implementation!.

.z.execute:{    $[x in .cfg.gateway.allowedcmdlist;:(value x);::];		
                $[x like ".gatewayfuncs.registerworker*";:(value x);::];
				$[.utl.anypatternmatch[x;.cfg.gateway.patternmatchcmds]=1b;:(value x);::];
				snapshot:.gatewayfuncs.gatewaystatus[];
				$[.cfg.gateway.workermode=`strict;snapshot:select from snapshot where host in .cfg.worker.list;::];
				workers:count snapshot;
                $[workers=0;:`noworkererror;::];
                .cfg.roundrobintoken:(.cfg.roundrobintoken+1) mod workers;
                rpchost:string [exec host from snapshot][.cfg.roundrobintoken];
				result:.rpc.remotequery[rpchost;x;`rpcerror];
				$[.cfg.roundrobintuple=1b;:(rpchost;result);:result];
           }

