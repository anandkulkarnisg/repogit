/ Sources :
/ https://www.codeproject.com/KB/database/Visual_SQL_Joins/Visual_SQL_JOINS_orig.jpg
/ https://www.codeproject.com/Articles/33052/Visual-Representation-of-SQL-Joins
/ https://code.kx.com/v2/basics/joins/

/ Table Data setup.
Table_A:([] PK:1 2 3 4 5 6 7 10; Value:`FOX`COP`TAXI`LINCOLN`ARIZONA`WASHINGTON`DELL`LUCENT);
Table_B:([] PK:1 2 3 6 7 8 9 11; Value:`TROT`CAR`CAB`MONUMENT`PC`MICROSOFT`APPLE`SCOTCH);

/INNER JOIN:-
.sql.ij:{[keyCol;t1;t2;t1cols;t2cols;t1n;t2n] 
                        keyValList:{?[ej[x;y;z];();();x]}[keyCol;t1;t2]; 
                        (t1n xcol ?[t1;enlist (in;keyCol;keyValList);0b;{x!x}t1cols]),'(t2n xcol ?[t2;enlist (in;keyCol;keyValList);0b;{x!x}t2cols]) 
         }                                            
/ Invocation :  .sql.ij[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value]

/LEFT JOIN:-
.sql.lj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n] 
                        tbl1:(t1n xcol t1),'(?[t1;();0b;{(enlist x)!(enlist x)}keycol]); 
                        tbl2:(t2n xcol t2),'(?[t2;();0b;{(enlist x)!(enlist x)}keycol]); 
                        ?[tbl1 lj keycol xkey tbl2;();0b;{x!x}[raze(t1n;t2n)]]
        }
/Invocation : .sql.lj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value]

/RIGHT JOIN:-
.sql.rj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n] colOrder:raze(t1n;t2n); colOrder xcols .sql.lj[keycol;t2;t1;t2cols;t1cols;t2n;t1n] }
/Invocation : .sql.rj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value]

/ OUTER JOIN / FULL OUTER JOIN:-
.sql.oj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullCol] 
                        tbl1:.sql.lj[keycol;t1;t2;t1cols;t2cols;t1n;t2n];
                        tbl2:.sql.rj[keycol;t1;t2;t1cols;t2cols;t1n;t2n];
                        colOrder:raze(t1n;t2n); 
                        colOrder xcols tbl1 uj ?[tbl2;enlist (=;nullCol;0N);0b;()]
        }
/ Invocation : .sql.oj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value;`A_PK]

/ LEFT JOIN EXCLUDING INNER JOIN [ LEFT EXCLUDING JOIN ]:-
.sql.lxj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullCol] ?[.sql.lj[keycol;t1;t2;t1cols;t2cols;t1n;t2n];enlist (=;nullCol;0N);0b;()] }
/Invocation : .sql.lxj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value;`B_PK]

/ RIGHT JOIN EXCLUDING INNER JOIN [ RIGHT EXCLUDING JOIN ]:-
.sql.rxj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullCol] ?[.sql.rj[keycol;t1;t2;t1cols;t2cols;t1n;t2n];enlist (=;nullCol;0N);0b;()] }
/Invocation : .sql.rxj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value;`A_PK]

/ OUTER JOIN EXCLUDING INNER JOIN.
.sql.oxij:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullColList] 
            /select from .sql.oj[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullCol] where (A_PK=0N) or (B_PK=0N)            
            ?[.sql.oj[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullColList[0]];enlist (|;(=;nullColList[0];0Nj);(=;nullColList[1];0Nj));0b;()]            
          }
/ Invocation : .sql.oxij[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value;`A_PK`B_PK]
