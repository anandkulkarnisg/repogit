
.utl.emptyResultSetTbl:([] ident:`symbol$(); nameSpace:`symbol$(); tableName:`symbol$(); columnName:`symbol$(); shortType:`char$(); foreignKey:`symbol$(); attribute:`symbol$())

.utl.getqTypes:{   t:flip {(x;.Q.t x;key'[x$\:()])}5h$where" "<>20#.Q.t;
                   idList:{x[0]} each t; shortTypeList:{x[1]} each t; longTypeList:{x[2]} each t;
                   t:([] id:idList; shortType:shortTypeList; longType:longTypeList);
                   t:`shortType xkey t;
                   t
                } 
                
.utl.getType:{ 
                $[(type x)=0h;:`mixedkList;::]; 
                t:first exec longType from .utl.getqTypes[] where id=abs type x; 
                $[(type x)<0h;:t;:(`$ raze(string t; "List"))] 
             }                

.utl.getTableMeta:{                     
                    $[(`$ first enlist string y)<>(`$".");x:`$ raze(string y,".",x);::];
                    t:`columnName`shortType`foreignKey`attribute xcol (meta x);
                    t:update tableName:`$ string x from t;
                    t:update ident: `$"." sv/: flip string(tableName;columnName) from t;                    
                    t:update nameSpace:{ $[x=`.;:`default;:x] }[y] from t;
                    t:update tableName:{ { `$ last "." vs (string x) } each x}[tableName] from t;    
                    t:select ident, nameSpace, tableName, columnName, shortType, foreignKey, attribute from t;                    
                    t
                  }

.utl.getNameSpaceMeta:{ $[(type x)=101h;x:`.;::]; 
                        $[(first string x)<>".";x:[`$ssr[string x;".";""]];::];                                               
                        tableList:{ @[tables; x; raze("nameSpaceError : `", string x; " : No Such NameSpace Found.Please verify.")] }[x];
                        $[(type tableList)=10h;'`$tableList;::];
                        $[tableList~(0#`);:.utl.emptyResultSetTbl;::];
                        raze .utl.getTableMeta[;x] each tables x 
                      }

.utl.getDictByNameSpace:{ select ident, nameSpace, tableName, columnName, longType, foreignKey, attribute from .utl.getNameSpaceMeta[x] lj .utl.getqTypes[] }

.utl.generateMeta:{ 
                    $[(type x)=101h;x:enlist `.;::];
                    $[(type x)=-11h;x:enlist x;::];
                    raze .utl.getDictByNameSpace each x 
                  }

//.utl.testExample[]
//.utl.generateMeta[`.]
//.utl.generateMeta[]
//.utl.generateMeta[`.test]
//.utl.getDictByNameSpace[`.test]
//.utl.getNameSpaceMeta[`.test]
//.utl.getNameSpaceMeta[`.test]
//.utl.generateMeta[(`.anand; `.test)]

.utl.testExample:{[] // set up test data table examples.
                     t:([] Name:`Anand`Peter`Thomas; Age:10 20 30; Salary:100 150 200);
                     t:`Name xasc t;
                     .test.tbl1:([] Name:`Anand`Peter`Thomas`Albert; Age: 1 2 3 4; Salary:10 15 20 25);
                     .test.test1.tbl:([] a:`a`b`c`d; b: 1 2 3 4; c:10.5 10.25 11.70 13.50);
                     // Execute the below test cases.
                     nameSpaceList:(`.;`.test;`.test.test1);
                    .utl.generateMeta[nameSpaceList]
                    //parse "select from .utl.generateMeta[nameSpaceList] where longType=`long, nameSpace like \"*test*\""
                    //?[.utl.generateMeta[nameSpaceList];enlist ((=;`longType;enlist `long);(like;`nameSpace;"*test*"));0b;()]
                    //?[value (`.utl.generateMeta;nameSpaceList);enlist ((=;`longType;enlist `long);(like;`nameSpace;"*test*"));0b;()]
                  }
