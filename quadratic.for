        REAL A,B,C
        INTEGER N
        WRITE(6,10)
10      FORMAT('COUNT     ','    A       ','      B        ','       C'
     ,'            X1 REAL','        X1 IMG','         X2 REAL'
     ,'        X2 IMG')        
        DO 60 N = 1, 20,1
        OPEN(11, FILE='quadratic.in', FORM='formatted')
        READ(11,'(3f10.0)') A, B, C
        CALL QUADRATICCALC(A,B,C,N)
60      CONTINUE
        CLOSE(11)
        WRITE(6,25) (N-1)
25      FORMAT('END OF PROGRAM: ', I3 ,' CARDS READ')
        PAUSE
        STOP
        END
        SUBROUTINE QUADRATICCALC(A,B,C,N)
        REAL X1R,X2R,X1I,X2I,DISCRIMINATIVE
        DISCRIMINATIVE = B ** 2 - 4.0 * A * C
        IF(DISCRIMINATIVE) 20,15,15
15          DISCRIMINATIVE = sqrt(DISCRIMINATIVE)
            X1R = (-B + DISCRIMINATIVE) / (2.0 * A)
            X2R = (-B - DISCRIMINATIVE) / (2.0 * A)
            X1I = 0.0
            X2I = 0.0
        IF(DISCRIMINATIVE) 30,30,30
20          DISCRIMINATIVE = (-DISCRIMINATIVE)
            DISCRIMINATIVE =SQRT(DISCRIMINATIVE)
            X1R = -B / (2.0 * A)
            X2R = X1R
            X1I = DISCRIMINATIVE / (2.0 * A)
            X2I = -(DISCRIMINATIVE / (2.0 * A))
30      CALL PRINT(A,B,C,X1R,X2R,X1I,X2I,N)
        RETURN
        END
        SUBROUTINE PRINT(A,B,C,X1R,X2R,X1I,X2I,N)
        WRITE(6,100) N,A,B,C
100     FORMAT(I5,1PE15.4,1PE15.4,1PE15.4$)
        IF(X1R) 23,24,23
23      WRITE(6,21) X1R
21      FORMAT(1PE15.4$)
        IF(X1I) 33,34,33
24      WRITE(6,22)
22      FORMAT('               '$)
        IF(X1I) 33,34,33
33      WRITE(6,21) X1I
        IF (X2R) 43,44,43
34      WRITE(6,22)
        IF (X2R) 43,44,43
43      WRITE(6,21) X2R
        IF (X2I) 53,54,53
44      WRITE(6,22)
        IF (X2I) 53,54,53
53      WRITE(6,51) X2I
51      FORMAT(1PE15.4)
        GOTO 13
54      WRITE(6,52)
52      FORMAT('               ')
13      RETURN
        END
