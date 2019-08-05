.dataDict.emptyResultSetTbl:([] ident:`symbol$(); nameSpace:`symbol$(); tableName:`symbol$(); columnName:`symbol$(); shortType:`char$(); foreignKey:`symbol$(); attribute:`symbol$())

.dataDict.getqTypes:{   t:flip {(x;.Q.t x;key'[x$\:()])}5h$where" "<>20#.Q.t;
                   idList:{x[0]} each t; shortTypeList:{x[1]} each t; longTypeList:{x[2]} each t;
                   t:([] id:idList; shortType:shortTypeList; longType:longTypeList);
                   t:`shortType xkey t;
                   t
                } 

.dataDict.getType:{ 
                $[(type x)=0h;:`mixedkList;::]; 
                t:first exec longType from .dataDict.getqTypes[] where id=abs type x; 
                $[(type x)<0h;:t;:(`$ raze(string t; "List"))] 
             }            
.dataDict.buildErrMsg:{ `$ raze raze ("invalid arg types : got : -> "; { raze ("`"; x) } each string x; " : expected : ->"; { raze ("`"; x) } each string y) }

.dataDict.validateSigniture:{ 
                         /x:`vwap;
                         /y:(1 2 3f; 4 5 6i);
                         t:value exec funcSigniture, cnt:count i from .config.funcSignitures[] where funcName=x;                        
                         $[t[1]<>1;`funcSignitureNotFoundError;::];
                         e:{value x} string first t[0];g:.dataDict.getType each y;
                         $[any g<>e;:.dataDict.buildErrMsg[g;e];:1b];
                       }
/.dataDict.validateSigniture[`vwap;(1 2 3f; 4 5 6f)]

.config.funcSignitures:{[] ([funcName:enlist `vwap]; funcSigniture:enlist `$"`floatList`floatList") } /.config.funcSignitures[]

/ Use this as example to test the above.
/vwap:{ g:.dataDict.getType each (x;y); e:`floatList`floatList; $[all g<>e;:.dataDict.buildErrMsg[g;e];::]; (x$y)%sum x }
/vwap:{ g:.dataDict.getType each (x;y); e:{ value x} string first exec funcSigniture from .config.funcSignitures[] where funcName=`vwap; $[all g<>e;:.dataDict.buildErrMsg[g;e];::]; (x$y)%sum x }
vwap:{ $[(type r:.dataDict.validateSigniture[`vwap;(x;y)])<>-1h;:r;::]; (x$y)%sum x }   
.dataDict.validateSigniture[`vwap;(1 2 3j; 4 5 6i)]
/vwap[1 2 3j; 4 5 6j]
vwap[1 2 3f; 4 5 6f]
/vwap[1 2 3i;"a"]
/vwap[1 2 3f;4 5 6f]~(1 2 3f wavg 4 5 6f) / Test of the validity of implementation!!
/vwap[`anand;.z.p]
/ vwap["f"$1+til 10;"f"$20+til 10]~(("f"$1+til 10) wavg "f"$20+til 10) / Test of the validity of implementation!!
.config.funcSignitures[]

.dataDict.getTableMeta:{                     
                    $[(`$ first enlist string y)<>(`$".");x:`$ raze(string y,".",x);::];
                    t:`columnName`shortType`foreignKey`attribute xcol (meta x);
                    t:update tableName:`$ string x from t;
                    t:update ident: `$"." sv/: flip string(tableName;columnName) from t;                    
                    t:update nameSpace:{ $[x=`.;:`default;:x] }[y] from t;
                    t:update tableName:{ { `$ last "." vs (string x) } each x}[tableName] from t;    
                    t:select ident, nameSpace, tableName, columnName, shortType, foreignKey, attribute from t;                    
                    t
                  }

.dataDict.getNameSpaceMeta:{ $[(type x)=101h;x:`.;::]; 
                        $[(first string x)<>".";x:[`$ssr[string x;".";""]];::];                                               
                        tableList:{ @[tables; x; raze("nameSpaceError : `", string x; " : No Such NameSpace Found.Please verify.")] }[x];
                        $[(type tableList)=10h;'`$tableList;::];
                        $[tableList~(0#`);:.dataDict.emptyResultSetTbl;::];
                        raze .dataDict.getTableMeta[;x] each tables x 
                      }

.dataDict.getDictByNameSpace:{ select ident, nameSpace, tableName, columnName, longType, foreignKey, attribute from .dataDict.getNameSpaceMeta[x] lj .dataDict.getqTypes[] }

.dataDict.generateMeta:{ 
                    $[(type x)=101h;x:enlist `.;::];
                    $[(type x)=-11h;x:enlist x;::];
                    raze .dataDict.getDictByNameSpace each x 
                  }

.dataDict.testExample:{[] // set up test data table examples.
                     t:([] Name:`Anand`Peter`Thomas; Age:10 20 30; Salary:100 150 200);
                     t:`Name xasc t;
                     .test.tbl1:([] Name:`Anand`Peter`Thomas`Albert; Age: 1 2 3 4; Salary:10 15 20 25);
                     .test.test1.tbl:([] a:`a`b`c`d; b: 1 2 3 4; c:10.5 10.25 11.70 13.50);
                     // Execute the below test cases.
                     nameSpaceList:(`.;`.test;`.test.test1);
                    .dataDict.generateMeta[nameSpaceList]
                    //parse "select from .dataDict.generateMeta[nameSpaceList] where longType=`long, nameSpace like \"*test*\""
                    //?[.dataDict.generateMeta[nameSpaceList];enlist ((=;`longType;enlist `long);(like;`nameSpace;"*test*"));0b;()]
                    //?[value (`.dataDict.generateMeta;nameSpaceList);enlist ((=;`longType;enlist `long);(like;`nameSpace;"*test*"));0b;()]
                  }

/ Create a delta control config param namespace so that we can query its meta.
.dataDict.generateConfigParamMeta:{ cp:`$ ":" vs string x; tblContent:.uc.getActiveParamValue[cp[0];cp[1]]; resultPair:(`$ssr[raze (".deltaconfigparam.";string x);":";"_"];tblContent); resultPair[0] set resultPair[1];};
.dataDict.getConfigParamMeta:{ .dataDict.generateConfigParamMeta each distinct .ex.prh".uc.getParamsForGroup[`SURVEILLANCE_CONFIG]"; .dataDict.generateMeta[`.deltaconfigparam] };
.dataDict.getConfigParamMeta[]


/ Invocation examples.
//.dataDict.testExample[]
//.dataDict.generateMeta[`.]
//.dataDict.generateMeta[]
//.dataDict.generateMeta[`.test]
//.dataDict.getDictByNameSpace[`.test]
//.dataDict.getNameSpaceMeta[`.test]
//.dataDict.getNameSpaceMeta[`.test]
//.dataDict.generateMeta[(`.anand; `.test)]
