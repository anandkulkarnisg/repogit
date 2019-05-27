/ Synopsis : This example below assumes that the master process is running at 5000 and slaves are running from 5001 to 5004.
/ Understanding of basic async , countdownLatch and interprocessing communication is needed.


/ Use this function to quit at ay point to restart afresh on master process.
.utl.quit:{ system"\\"; }
/ .utl.quit[]

/ priciple technique to divide list eqaul sizes.
0 5 10 15 _ 1+til 20;
(0 1 2 3 * 5) _ 1+til 20;

/ Create a 100 million list of integer items to process.
sampleList:1+til 100000000;
numWorkers:4;

/ Slice the list in equal portions for the workers to process.
sampleList:((til numWorkers) * ("j"$(count sampleList)%numWorkers)) _ sampleList;

/ Pass each list to the workers in async with a call back function to ensure they report the results back when ready.
/ We use a global list to collect the results back.
.global.resultList:`long$();
.global.countDownLatch:numWorkers;

/ Implement here what the post processing function would do when all results are returned.
postProcessFunc:{ .global.finalSum:sum x; }

/ Client call back implementation below.
clientCallBackFunc:{ .global.resultList:.global.resultList, x; .global.countDownLatch-:1; $[.global.countDownLatch=0;postProcessFunc[.global.resultList];::];  }

/ The list of slave process rpc handles.
slaveRpcConnectionList:{ value raze ("`::"; string x) } each 5000 + 1+til numWorkers;

/ The below is the slave side call passed on the fly.
slaveProcessCall:{ result:sum x; (neg .z.w)(`clientCallBackFunc;result) };

/ Build a simple map of rpc connection handle and chunk of data to be passed.
processingDict:({ { :hopen x } each x } each slaveRpcConnectionList)!sampleList;

/ Run the processing async on each slave process via below.
{ { k:((key y)[x]); v:y[k]; (neg k)(z;v); }[;x;y] each til count x }[processingDict;slaveProcessCall]

/ Close the handles to the slave process at end. 
{ hclose x } each key processingDict;

/ Verify the result.
.global.finalSum=sum raze sampleList / should return 1b to confirm all is ok.

/ Shutdown all the processes with master at the end.
{ p:@[x;y;`success]; $[p=`success;:p;:`error] }[;"\\\\"] each { value raze ("`::"; string x) } each reverse 5000 + til 5;

