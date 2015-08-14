// mesh_tra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>

void calcCurve(long double &Acurv, long double &Bcurv, long double &Ccurv, long double X1, long double Y1, long double X2, long double Y2, long double X3, long double Y3)
{
    // Y1= A*X1*X1 + B*X1 +C (1)
    // Y2= A*X2*X2 + B*X2 +C (2)
    // Y3= A*X3*X3 + B*X3 +C (3)
    //                                                from (1) & (2):
    // Y2-Y1 = A* (X2*X2 - X1*X1) + B*(X2-X1)     (4)
    //                                                from (2) & (3):
    // Y3-Y2 = A* (X3*X3 - X2*X2) + B*(X3-X2)     (5)
    //                                                from (4):
    // B = [(Y2-Y1)  - A* (X2*X2 - X1*X1)] / (X2-X1) (6)
    //                                                from (5) & (6):
    // Y3-Y2 = A* (X3*X3 - X2*X2) + [(Y2-Y1)  - A* (X2*X2 - X1*X1)] / (X2-X1) *(X3-X2)
    // Y3-Y2 = A* (X3*X3 - X2*X2) + (Y2-Y1)/ (X2-X1) *(X3-X2)  - A* (X2*X2 - X1*X1) / (X2-X1) *(X3-X2)
    // (Y3-Y2)*(X2-X1) = A* (X3*X3 - X2*X2)*(X2-X1) + (Y2-Y1) *(X3-X2)  - A* (X2*X2 - X1*X1)  *(X3-X2)
    // (Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2) = A* (X3*X3 - X2*X2)*(X2-X1)   - A* (X2*X2 - X1*X1)  *(X3-X2)
    // A* [(X3*X3 - X2*X2)*(X2-X1)   - (X2*X2 - X1*X1)  *(X3-X2)] = (Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2) 
    // A = [(Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)] / [(X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2)]
    // B = ((Y2-Y1)  - A* (X2*X2 - X1*X1)) / (X2-X1)
    // C = Y1 - A*X1*X1 - B*X1
    if ((X2==X1) && (X3==X1))  //horizontal line
    {
        ;
    }
    else if (X2==X1)
    {
        ;
    }
    else if (X3==X2)
    {
        ;
    }
    else if ((((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2))) == 0)  // case : is it possible??
    {
        ;
    }
    else
    {
        Acurv = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
        Bcurv = ((Y2-Y1)  - Acurv* (X2*X2 - X1*X1)) / (X2-X1);
        Ccurv = Y1 - Acurv*X1*X1 - Bcurv*X1;
    }
}
#ifdef DO_GET_I_ANDJ
void GetIandJ(int i,int iLinesInit,int j,int iElementsInit, int &is1, int &is2, int &is3, int &jg1, int &jg2, int &jg3)
{
                    //=============================================================================
                    //                                   iElementsInit i.e  6 (normally it is 13 for 10cm 3D printer)
                    //                                <-               loop by Y ends in iElementsInit-1
                    //   X Y   X Y    X Y   X Y    X Y   X Y
                    //   0,0   0,1    0,2   0,3    0,4   0,5        <- loop j
                    //      Aa     Ab     Ab    Ab     Ac
                    //   1,0   1,1    1,2   1,3    1,4   1,5
                    //      Ba     Bb     Bb    Bb     Bc
                    //   2,0   2,1    2,2   2,3    2,4   2,5
                    //      Ba     Bb     Bb    Bb     Bc
                    //   3,0   3,1    3,2   3,3    3,4   3,5
                    //      Ba     Bb     Bb    Bb     Bc
                    //   4,0   4,1    4,2   4,3    4,4   4,5   <- loop by X ends on iLinesInit-1
                    //      Ca     Cb     Cb    Cb     Cc
                    //   5,0   5,1    5,2   5,3    5,4   5,5              <- iLinesInit i.e 6 (normally it is 13 for 10cm 3D printer)
                    // total cases:
                    // Aa, Ab, Ac, Ba, Bb, Bc, Ca, Cb, CC - 9 cases
                    // 1*  2*  3*  4*  5*  6*  7*  8*  9

    if ((i > 0) && (i <(iLinesInit-2)) && (j >0) && ( j < (iElementsInit-2))) // case Bb (5)
    {
        // top line:
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j-1,   i,j    i,j+1
        jg1 = j-1; jg2 = j;  jg3 = j+1;
        is1 = i-1; is2 = i;  is3 = i+1;
        //X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
        //Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

        //calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
        // bottom line:
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i+1,j-1,   i+1,j    i+1,j+1
        //X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
        //Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
        //calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);

    }
    else if ((i > 0) && (i <(iLinesInit-2)) && (j ==0))  // case Ba  (4)
    {
        // top line:
        // 3 points
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j,   i,j+1    i,j+2
        jg1 = j; jg2 = j+1; jg3 = j+2;
        is1 = i-1; is2 = i;  is3 = i+1;
        //X1=DistorX[i][j]; X2=DistorX[i][j+1];X3=DistorX[i][j+2];
        //Y1=DistorY[i][j]; Y2=DistorY[i][j+1];Y3=DistorY[i][j+2];
        //calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
        // bottom line:
        // 3 points
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i+1,j-1,   i+1,j    i+1,j+1
        //X1=DistorX[i+1][j]; X2=DistorX[i+1][j+1];X3=DistorX[i+1][j+2];
        //Y1=DistorY[i+1][j]; Y2=DistorY[i+1][j+1];Y3=DistorY[i+1][j+2];
        //calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);

    }
    else if ((i == 0)  && (j >0) && ( j < (iElementsInit-2))) // case Ab (2)
    {
        // top line:
        // 3 points
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j-1,   i,j    i,j+1
        jg1 = j-1; jg2 = j; jg3 = j+1;
        //                        X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
        //                        Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

        //                        calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j]; X_2= DistorY[i+1][j];X_3= DistorY[i+2][j];
                                Y_1=-DistorX[i][j]; Y_2=-DistorX[i+1][j];Y_3=-DistorX[i+2][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j+1]; X_2= DistorY[i+1][j+1];X_3= DistorY[i+2][j+1];
                                Y_1=-DistorX[i][j+1]; Y_2=-DistorX[i+1][j+1];Y_3=-DistorX[i+2][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
    }
    else if ((i > 0) && (i <(iLinesInit-2)) && ( j == (iElementsInit-2))) // case Bc (6)
    {
        // top line:
        // 3 points
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j-1,   i,j    i,j+1
        js1 = j-1; js2 = j; js3 = j+1;
        //                        X1=DistorX[i][j-1]; X2=DistorX[i][j ];X3=DistorX[i][j+1];
        //                        Y1=DistorY[i][j-1]; Y2=DistorY[i][j ];Y3=DistorY[i][j+1];

        //                        calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-2]; X2=DistorX[i+1][j-1];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-2]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
    }
    else if ((i ==(iLinesInit-2)) && (j >0) && ( j < (iElementsInit-2))) // case Cb (8)
    {
        // top line:
        // 3 points
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j-1,   i,j    i,j+1
        js1 = j-1;  js2 = j; js3 = j+1;
        //                        X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
        //                        Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

        //calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
    }
    else if ((i == 0) && (j ==0)) // case Aa (1)
    {
        // top line:
        // 3 points
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j,   i,j+1    i,j+2
        js1 = j; js2 = j+1; js3 = j+2;
        //                        X1=DistorX[i][j]; X2=DistorX[i][j+1];X3=DistorX[i][j+2];
        //                        Y1=DistorY[i][j]; Y2=DistorY[i][j+1];Y3=DistorY[i][j+2];

        //                        calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j,   i+1,j+1    i+1,j+2
                                X1=DistorX[i+1][j]; X2=DistorX[i+1][j+1];X3=DistorX[i+1][j+2];
                                Y1=DistorY[i+1][j]; Y2=DistorY[i+1][j+1];Y3=DistorY[i+1][j+2];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j]; X_2= DistorY[i+1][j];X_3= DistorY[i+2][j];
                                Y_1=-DistorX[i][j]; Y_2=-DistorX[i+1][j];Y_3=-DistorX[i+2][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j+1]; X_2= DistorY[i+1][j+1];X_3= DistorY[i+2][j+1];
                                Y_1=-DistorX[i][j+1]; Y_2=-DistorX[i+1][j+1];Y_3=-DistorX[i+2][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);

    }
    else if ((i == 0) && ( j == (iElementsInit-2))) // case Ac (2)
    {
        // top line:
        // 3 points
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j-1,   i,j    i,j+1
        js1 = j-1; js2 = j; js3 = j+1;
        //                        X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
        //                        Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

        //                        calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i  ][j]; X_2= DistorY[i+1][j];X_3= DistorY[i+2][j];
                                Y_1=-DistorX[i  ][j]; Y_2=-DistorX[i+1][j];Y_3=-DistorX[i+2][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j+1]; X_2= DistorY[i+1][j+1];X_3= DistorY[i+2][j+1];
                                Y_1=-DistorX[i][j+1]; Y_2=-DistorX[i+1][j+1];Y_3=-DistorX[i+2][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);

    }
    else if ( (i ==(iLinesInit-2)) && (j ==0)) // case Ca (7)
    {
        // top line:
        // 3 points
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j,   i,j+1    i,j+2
        js1 = j; js2 = j+1; js3 = j+2;
        //                        X1=DistorX[i][j]; X2=DistorX[i][j+1];X3=DistorX[i][j+2];
        //                        Y1=DistorY[i][j]; Y2=DistorY[i][j+1];Y3=DistorY[i][j+2];
        //
        //                        calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j]; X2=DistorX[i+1][j+1];X3=DistorX[i+1][j+2];
                                Y1=DistorY[i+1][j]; Y2=DistorY[i+1][j+1];Y3=DistorY[i+1][j+2];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
    }
    else                                  // case Cc (9)
    {
        // top line:
        //   X0,Y0   X1,Y1    X2,Y2   
        //    i,j-1,   i,j    i,j+1
        js1 = j-1; js2 = j; js3 = j+1;
        //                        X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
        //                        Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];
        //
        //                        calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
    }

}
#endif
int main(int argc, char* argv[])
{
    long double DistorX[100][100];
    long double DistorY[100][100];
    int iLines;
    int iElements;
    char szDistor[1024];



    if (argc=5 && argv[1][0] == 'x')  // convertion distertion file
    {
        printf(" converting inverted distertion file left top corner become left top corner");
        FILE *Distor = fopen(argv[2], "r");
        if (NULL != fgets(szDistor,sizeof(szDistor),Distor))
        {
            iLines = atoi(szDistor);
            for (int i = 0; i < iLines; i++)
            {
                if (NULL != fgets(szDistor,sizeof(szDistor),Distor))
                {
                    iElements = atoi(szDistor);
                    int j = 1;
                    int switchcase = 0;
                    int ielem = 0;
                    long double X, Y, Z;
                    while(j < strlen(szDistor))
                    {
                        if ((szDistor[j] != ' ') && (szDistor[j] != ','))
                        {

                            switch (switchcase)
                            {
                            case 0: switchcase = 1;break;
                            case 2: DistorX[i][ielem] = atof(&szDistor[j]);switchcase = 3;break;
                            case 4: DistorY[i][ielem++] = atof(&szDistor[j]);switchcase = 5;
                                if (ielem > iElements)
                                {
                                    printf("\n distortion file is wrong");
                                    fclose(Distor);
                                    return(36);
                                }
                                break;
                            }
                        }
                        else
                        {
                            switch (switchcase)
                            {
                            case 0: break;
                            case 1: switchcase = 2; break;
                            case 3: switchcase = 4; break;
                            case 5: switchcase = 2; break;
                            }
                        }
                        j++;
                        if (ielem == iElements)
                            break;
                    }


                }
                else
                {
                    printf("\n distortion file is wrong");
                    fclose(Distor);
                    return(35);
                }
            }
        }
        else
        {
            printf("\n distortion file is wrong");
            fclose(Distor);
            return 34;
        }

        fclose(Distor);
        FILE *DistorOut = fopen(argv[3], "w");
        FILE *NoDistorOut = fopen(argv[4], "w");
        if ((DistorOut !=NULL) && (NoDistorOut !=NULL))
        {
            fprintf(DistorOut,"%d\n",iLines);
            fprintf(NoDistorOut,"%d\n",iLines);
            long double ldX= -51.0;
            long double ldY=  51.0;
            for (int idl = 0; idl <iLines; idl++)
            {
                long double ldX= -51.0;
                fprintf(DistorOut,"%d ",iElements);
                fprintf(NoDistorOut,"%d ",iElements);
                for(int idv = 0; idv <iElements; idv++)
                {
                    fprintf(DistorOut,"%015.12f %015.12f ", DistorX[idv][iLines-idl-1], DistorY[idv][iLines-idl-1]);
                    fprintf(NoDistorOut,"%05.1f %05.1f ", ldX, ldY);
                    if (idv & 1)
                    {
                        ldX+=8.0;
                    }
                    else
                    {
                        ldX+=2.0;
                    }

                }
                if (idl & 1)
                {
                    ldY-=8.0;
                }
                else
                {
                    ldY-=2.0;
                }
                fprintf(DistorOut,"\n");
                fprintf(NoDistorOut,"\n");
            }
            fclose(DistorOut);

        }
        exit(0) ;
    }
    long double iOffsetX = atof(argv[5]);
    long double iOffsetY = atof(argv[6]);

    FILE *Distor = fopen(argv[1], "r");
    if (Distor != NULL)
    {
        if (NULL != fgets(szDistor,sizeof(szDistor),Distor))
        {
            iLines = atoi(szDistor);
            for (int i = 0; i < iLines; i++)
            {
                if (NULL != fgets(szDistor,sizeof(szDistor),Distor))
                {
                    iElements = atoi(szDistor);
                    int j = 1;
                    int switchcase = 0;
                    int ielem = 0;
                    long double X, Y, Z;
                    while(j < strlen(szDistor))
                    {
                        if (szDistor[j] != ' ')
                        {

                            switch (switchcase)
                            {
                            case 0: switchcase = 1;break;
                            case 2: DistorX[i][ielem] = atof(&szDistor[j]);switchcase = 3;break;
                            case 4: DistorY[i][ielem++] = atof(&szDistor[j]);switchcase = 5;
                                if (ielem > iElements)
                                {
                                    printf("\n distortion file is wrong");
                                    fclose(Distor);
                                    return(36);
                                }
                                break;
                            }
                        }
                        else
                        {
                            switch (switchcase)
                            {
                            case 0: break;
                            case 1: switchcase = 2; break;
                            case 3: switchcase = 4; break;
                            case 5: switchcase = 2; break;
                            }
                        }
                        j++;
                        if (ielem == iElements)
                            break;
                    }


                }
                else
                {
                    printf("\n distortion file is wrong");
                    fclose(Distor);
                    return(35);
                }
            }
        }
        else
        {
            printf("\n distortion file is wrong");
            fclose(Distor);
            return 34;
        }

        fclose(Distor);
    }
    else
    {
        printf("\n distortion file is missing");
        return 33;
    }

    long double InitX[100][100];
    long double InitY[100][100];
    int iLinesInit;
    int iElementsInit;

    char szInit[1024];
    FILE *InitFile = fopen(argv[2], "r");
    if (InitFile != NULL)
    {
        if (NULL != fgets(szInit,sizeof(szDistor),InitFile))
        {
            iLinesInit = atoi(szInit);
            for (int i = 0; i < iLinesInit; i++)
            {
                if (NULL != fgets(szInit,sizeof(szInit),InitFile))
                {
                    iElementsInit = atoi(szInit);
                    int j = 1;
                    int switchcase = 0;
                    int ielemInit = 0;
                    long double X, Y, Z;
                    while(j < strlen(szInit))
                    {
                        if (szInit[j] != ' ')
                        {

                            switch (switchcase)
                            {
                            case 0: switchcase = 1;break;
                            case 2: InitX[i][ielemInit] = atof(&szInit[j]);switchcase = 3;break;
                            case 4: InitY[i][ielemInit++] = atof(&szInit[j]);switchcase = 5;
                                if (ielemInit > iElementsInit)
                                {
                                    printf("\n distortion file is wrong");
                                    fclose(InitFile);
                                    return(56);
                                }
                                break;
                            }
                        }
                        else
                        {
                            switch (switchcase)
                            {
                            case 0: break;
                            case 1: switchcase = 2; break;
                            case 3: switchcase = 4; break;
                            case 5: switchcase = 2; break;
                            }
                        }
                        j++;
                        if (ielemInit == iElementsInit)
                            break;
                    }


                }
                else
                {
                    printf("\n InitFile is wrong");
                    fclose(InitFile);
                    return(55);
                }
            }
        }
        else
        {
            printf("\n InitFile is wrong");
            fclose(InitFile);
            return 54;
        }

        fclose(InitFile);
    }
    else
    {
        printf("\n distortion file is missing");
        return 53;
    }
    // now needs to invert Y 
    /*
    for (int ii= 0; ii < iLinesInit/2; ii++)    // loop for Y
    {
        for (int jj = 0; jj < iElementsInit; jj ++) // loop for X
        {
            long double ldtempX = InitX[ii][jj]; 
            long double ldtempY = InitY[ii][jj]; 
            InitX[ii][jj] = InitX[iLinesInit - ii-1][jj];
            InitY[ii][jj] = InitY[iLinesInit - ii-1][jj];
            InitX[iLinesInit - ii-1][jj] = ldtempX;
            InitY[iLinesInit - ii-1][jj] = ldtempY;

            ldtempX = DistorX[ii][jj]; 
            ldtempY = DistorY[ii][jj]; 
            DistorX[ii][jj] = DistorX[iLinesInit - ii-1][jj];
            DistorY[ii][jj] = DistorY[iLinesInit - ii-1][jj];
            DistorX[iLinesInit - ii-1][jj] = ldtempX;
            DistorY[iLinesInit - ii-1][jj] = ldtempY;

        }
    }*/
    FILE *InputMesh = fopen(argv[3], "r");
    if (InputMesh != NULL)
    {
        FILE *OutputMesh = fopen(argv[4], "w");
        if (OutputMesh != NULL)
        {
            char szString[256];
            while(fgets(szString, sizeof(szString),InputMesh) != NULL)
            {
                long double xx1;
                long double yy1;

                if (szString[0] =='v')
                {
                    int i = 2;
                    int switchcase = 0;
                    long double X, Y, Z;
                    while(i < strlen(szString))
                    {
                        if (szString[i] != ' ')
                        {
                            switch (switchcase)
                            {
                            case 0: X = atof(&szString[i]);switchcase = 1;break;
                            case 1: break;
                            case 2: Y = atof(&szString[i]);switchcase = 3;break;
                            case 3: break;
                            case 4: Z = atof(&szString[i]);switchcase = 5;break;
                            }
                        }
                        else
                        {
                            switch (switchcase)
                            {
                            case 0: break;
                            case 1: switchcase = 2; break;
                            case 3: switchcase = 4; break;
                            }
                        }
                        i++;
                        if (switchcase == 5)
                            break;
                    }
                    xx1=(X+iOffsetX);
                    yy1=(Y+iOffsetY);
                    long double xx_1 = yy1;
                    long double yy_1 = -xx1;

                    //=============================================================================
                    //                                   iElementsInit i.e  6 (normally it is 13 for 10cm 3D printer)
                    //                                <-               loop by Y ends in iElementsInit-1
                    //   X Y   X Y    X Y   X Y    X Y   X Y
                    //   0,0   0,1    0,2   0,3    0,4   0,5        <- loop j
                    //      Aa     Ab     Ab    Ab     Ac
                    //   1,0   1,1    1,2   1,3    1,4   1,5
                    //      Ba     Bb     Bb    Bb     Bc
                    //   2,0   2,1    2,2   2,3    2,4   2,5
                    //      Ba     Bb     Bb    Bb     Bc
                    //   3,0   3,1    3,2   3,3    3,4   3,5
                    //      Ba     Bb     Bb    Bb     Bc
                    //   4,0   4,1    4,2   4,3    4,4   4,5   <- loop by X ends on iLinesInit-1
                    //      Ca     Cb     Cb    Cb     Cc
                    //   5,0   5,1    5,2   5,3    5,4   5,5              <- iLinesInit i.e 6 (normally it is 13 for 10cm 3D printer)
                    // total cases:
                    // Aa, Ab, Ac, Ba, Bb, Bc, Ca, Cb, CC - 9 cases
                    // 1*  2*  3*  4*  5*  6*  7*  8*  9



                    for (int i= 0; i < iLinesInit-1; i++)    // loop for Y
                    {
                        for (int j = 0; j < iElementsInit-1; j ++) // loop for X
                        {
                            
                            // top and bottom lines calculated in X,Y system of coordinates
                            long double X1,X2,Y1,Y2, X3,Y3;
                            long double Atop;
                            long double Btop;
                            long double Ctop;
                            long double Abot;
                            long double Bbot;
                            long double Cbot;
                            // left and right lines calculated in X' = Y and Y' =-X system of coordinates
                            long double X_1,X_2,Y_1,Y_2, X_3,Y_3;
                            long double Aleft;
                            long double Bleft;
                            long double Cleft;
                            long double Aright;
                            long double Bright;
                            long double Cright;
#ifdef DO_GET_I_ANDJ
                            GetIandJ(i,iLinesInit,j,iElementsInit, is1, is2, is3, js1,js2,js3);
                            // top line:
                            //   X0,Y0   X1,Y1    X2,Y2   
                            //    i,j-1,   i,j    i,j+1
                            //X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
                            //Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

                            X1=DistorX[is2][js1]; X2=DistorX[is2][js2];X3=DistorX[is2][js3];
                            Y1=DistorY[is2][js1]; Y2=DistorY[is2][js2];Y3=DistorY[is2][js3];

                            calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                            // bottom line:
                            //   X0,Y0   X1,Y1    X2,Y2   
                            //    i+1,j-1,   i+1,j    i+1,j+1
                            X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                            Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                            calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                            // left line:
                            //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                            //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                            //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                            // then coordinates converted to X_1= Y1, Y_1 = -X1
                            X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                            Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                            calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                            // right line:
                            //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                            //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                            //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                            // then coordinates converted to X_1= Y1, Y_1 = -X1
                            X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                            Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                            calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
#else

                            if ((i > 0) && (i <(iLinesInit-2)) && (j >0) && ( j < (iElementsInit-2))) // case Bb (5)
                            {
                                // top line:
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j-1,   i,j    i,j+1
                                X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
                                Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                            }
                            else if ((i > 0) && (i <(iLinesInit-2)) && (j ==0))  // case Ba  (4)
                            {
                                // top line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j,   i,j+1    i,j+2
                                X1=DistorX[i][j]; X2=DistorX[i][j+1];X3=DistorX[i][j+2];
                                Y1=DistorY[i][j]; Y2=DistorY[i][j+1];Y3=DistorY[i][j+2];
                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j]; X2=DistorX[i+1][j+1];X3=DistorX[i+1][j+2];
                                Y1=DistorY[i+1][j]; Y2=DistorY[i+1][j+1];Y3=DistorY[i+1][j+2];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);

                            }
                            else if ((i == 0)  && (j >0) && ( j < (iElementsInit-2))) // case Ab (2)
                            {
                                // top line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j-1,   i,j    i,j+1
                                X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
                                Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j]; X_2= DistorY[i+1][j];X_3= DistorY[i+2][j];
                                Y_1=-DistorX[i][j]; Y_2=-DistorX[i+1][j];Y_3=-DistorX[i+2][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j+1]; X_2= DistorY[i+1][j+1];X_3= DistorY[i+2][j+1];
                                Y_1=-DistorX[i][j+1]; Y_2=-DistorX[i+1][j+1];Y_3=-DistorX[i+2][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                            }
                            else if ((i > 0) && (i <(iLinesInit-2)) && ( j == (iElementsInit-2))) // case Bc (6)
                            {
                                // top line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j-1,   i,j    i,j+1
                                X1=DistorX[i][j-1]; X2=DistorX[i][j ];X3=DistorX[i][j+1];
                                Y1=DistorY[i][j-1]; Y2=DistorY[i][j ];Y3=DistorY[i][j+1];

                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                            }
                            else if ((i ==(iLinesInit-2)) && (j >0) && ( j < (iElementsInit-2))) // case Cb (8)
                            {
                                // top line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j-1,   i,j    i,j+1
                                X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
                                Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                            }
                            else if ((i == 0) && (j ==0)) // case Aa (1)
                            {
                                // top line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j,   i,j+1    i,j+2
                                X1=DistorX[i][j]; X2=DistorX[i][j+1];X3=DistorX[i][j+2];
                                Y1=DistorY[i][j]; Y2=DistorY[i][j+1];Y3=DistorY[i][j+2];

                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j,   i+1,j+1    i+1,j+2
                                X1=DistorX[i+1][j]; X2=DistorX[i+1][j+1];X3=DistorX[i+1][j+2];
                                Y1=DistorY[i+1][j]; Y2=DistorY[i+1][j+1];Y3=DistorY[i+1][j+2];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j]; X_2= DistorY[i+1][j];X_3= DistorY[i+2][j];
                                Y_1=-DistorX[i][j]; Y_2=-DistorX[i+1][j];Y_3=-DistorX[i+2][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j+1]; X_2= DistorY[i+1][j+1];X_3= DistorY[i+2][j+1];
                                Y_1=-DistorX[i][j+1]; Y_2=-DistorX[i+1][j+1];Y_3=-DistorX[i+2][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);

                            }
                            else if ((i == 0) && ( j == (iElementsInit-2))) // case Ac (2)
                            {
                                // top line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j-1,   i,j    i,j+1
                                X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
                                Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i  ][j]; X_2= DistorY[i+1][j];X_3= DistorY[i+2][j];
                                Y_1=-DistorX[i  ][j]; Y_2=-DistorX[i+1][j];Y_3=-DistorX[i+2][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+2,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i][j+1]; X_2= DistorY[i+1][j+1];X_3= DistorY[i+2][j+1];
                                Y_1=-DistorX[i][j+1]; Y_2=-DistorX[i+1][j+1];Y_3=-DistorX[i+2][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);

                            }
                            else if ( (i ==(iLinesInit-2)) && (j ==0)) // case Ca (7)
                            {
                                // top line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j,   i,j+1    i,j+2
                                X1=DistorX[i][j]; X2=DistorX[i][j+1];X3=DistorX[i][j+2];
                                Y1=DistorY[i][j]; Y2=DistorY[i][j+1];Y3=DistorY[i][j+2];

                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                // 3 points
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j]; X2=DistorX[i+1][j+1];X3=DistorX[i+1][j+2];
                                Y1=DistorY[i+1][j]; Y2=DistorY[i+1][j+1];Y3=DistorY[i+1][j+2];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                            }
                            else                                  // case Cc (9)
                            {
                                // top line:
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i,j-1,   i,j    i,j+1
                                X1=DistorX[i][j-1]; X2=DistorX[i][j  ];X3=DistorX[i][j+1];
                                Y1=DistorY[i][j-1]; Y2=DistorY[i][j  ];Y3=DistorY[i][j+1];

                                calcCurve(Atop, Btop, Ctop, X1, Y1, X2, Y2, X3, Y3);
                                // bottom line:
                                //   X0,Y0   X1,Y1    X2,Y2   
                                //    i+1,j-1,   i+1,j    i+1,j+1
                                X1=DistorX[i+1][j-1]; X2=DistorX[i+1][j  ];X3=DistorX[i+1][j+1];
                                Y1=DistorY[i+1][j-1]; Y2=DistorY[i+1][j  ];Y3=DistorY[i+1][j+1];
                                calcCurve(Abot, Bbot, Cbot, X1, Y1, X2, Y2, X3, Y3);

                                // left line:
                                //   x0,y0  i-1,j  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j]; X_2= DistorY[i  ][j];X_3= DistorY[i+1][j];
                                Y_1=-DistorX[i-1][j]; Y_2=-DistorX[i  ][j];Y_3=-DistorX[i+1][j];

                                calcCurve(Aleft, Bleft, Cleft, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                                // right line:
                                //   x0,y0  i-1,j+1  => X_1 = y1  Y_1 = -x1
                                //   x1,y1  i  ,j+1  => X_1 = y1  Y_1 = -x1
                                //   x2,y2  i+1,j+1  => X_1 = y1  Y_1 = -x1
                                // then coordinates converted to X_1= Y1, Y_1 = -X1
                                X_1= DistorY[i-1][j+1]; X_2= DistorY[i  ][j+1];X_3= DistorY[i+1][j+1];
                                Y_1=-DistorX[i-1][j+1]; Y_2=-DistorX[i  ][j+1];Y_3=-DistorX[i+1][j+1];
                                calcCurve(Aright, Bright, Cright, X_1, Y_1, X_2, Y_2, X_3, Y_3);
                            }
#endif
                            // check that point matched area btw top-bottom curve
                            if ( Atop*xx1*xx1 + Btop*xx1 +Ctop > yy1)
                            {
                                if ( Abot*xx1*xx1 + Bbot*xx1 +Cbot < yy1)
                                {
                                    long double abot = Abot;
                                    long double bbot = Bbot;
                                    long double cbot = Cbot;
                                    long double delta = 0.1;
                                    long double target = 0;
                                    long double xx1_i = xx1;
                                    long double yy1_i = yy1;

                                    long double aright = Aright;
                                    long double bright = Bright;
                                    long double cright = Cright;
                                    long double deltaR = 0.1;
                                    long double targetR = 0;

                                    while(abs(delta) > 0.000000001)
                                    {
                                        abot = Abot+ (Atop-Abot)*target; bbot = Bbot+ (Btop-Bbot)*target; cbot = Cbot+ (Ctop-Cbot)*target;
                                        yy1_i = InitY[i+1][j] + (InitY[i][j]-InitY[i+1][j])*target;
                                        if ( abot*xx1_i*xx1_i + bbot*xx1_i +cbot < yy1)
                                        {
                                            target +=delta;
                                        }
                                        else  // over line - reduce delta
                                        {
                                            target -=delta;
                                            delta/=2;
                                            target +=delta;
                                        }
                                    }
                                    
                                    // coordinates for right and left lines:
                                    if ( Aleft*xx_1*xx_1 + Bleft*xx_1 +Cleft > yy_1)
                                    {
                                        if ( Aright*xx_1*xx_1 + Bright*xx_1 +Cright < yy_1)
                                        {
                                            xx1_i = yy1;
                                            yy1_i = -xx1;
                                            while(abs(deltaR) > 0.000000001)
                                            {
                                                aright = Aright+ (Aleft-Aright)*targetR; bright = Bright+ (Bleft-Bright)*targetR; cright = Cright+ (Cleft-Cright)*targetR;
                                                yy1_i = -InitX[i][j+1] + (-InitX[i][j]-(-InitX[i][j+1]))*targetR;
                                                if ( aright*xx1_i*xx1_i + bright*xx1_i +cright < yy_1)
                                                {
                                                    targetR +=deltaR;
                                                }
                                                else  // over line - reduce delta
                                                {
                                                    targetR -=deltaR;
                                                    deltaR/=2;
                                                    targetR +=deltaR;
                                                }
                                            }
                                            // change position accordinly found target and targetR
                                            yy1 = InitY[i+1][j] + (InitY[i][j]-InitY[i+1][j])*target;
                                            xx1 = InitX[i][j+1] + (InitX[i][j]-InitX[i][j+1])*targetR;
                                            goto DONE_DIST;
                                        }
                                    }
                                }
                            }

/*



                            if ( (i == (iLinesInit-2)) && (j == (iElementsInit-2))) // one of the last lines
                            {
                                // 2 points (j,j+1) and (i,i+1) 
                                //            => X(0,11)Y(0,11)    X(0,12)Y(0,12)  - top line in the box
                                // Y1= A*X1 + B (1)
                                // Y2= A*X2 + B (2)
                                //                                                from (1) & (2):
                                // Y2-Y1 = A* (X2 - X1)     (3)
                                // A = (X2-X1)/(Y2-Y1)
                                // B = Y1 - A*X1
                                // if (Y2-Y1) == 0  (horizontall line) then 
                                //      formula is Y= Y1
                                //  for top line:
                                // 
                                //  first poin:             Second point:
                                // X[0][11] = 50 = X1      X[0][12] = 60 = X2
                                // Y[0][11] = 60 = Y1      Y[0][12] = 60 = Y2
                                long double X1,X2,Y1,Y2;
                                X1= DistorX[i][j]; X2= DistorX[i][j+1];
                                Y1= DistorY[i][j]; Y2= DistorY[i][j+1];
                                long double Atop;
                                long double Btop;
                                if ((Y2-Y1) == 0)
                                {
                                    Atop = 0;
                                    Btop = Y1;
                                }
                                else
                                {
                                    Atop = (X2-X1)/(Y2-Y1);
                                    Btop = Y1 - Atop*X1;
                                }
                                // is it low than Top curve?
                                if ( Atop*xx1 + Btop <= yy1)
                                {
                                    //  for bottom line:
                                    //  
                                    // X[1][11] =  50 = X1      X[1][12] =  60 = X2
                                    // Y[1][11] =  50 = Y1      Y[1][12] =  50 = Y2
                                    X1= DistorX[i][j]; X2= DistorX[i][j+1];
                                    Y1= DistorY[i][j]; Y2= DistorY[i][j+1];
                                    long double Abot;
                                    long double Bbot;
                                    if ((Y2-Y1) == 0)
                                    {
                                        Abot = 0;
                                        Bbot = Y1;
                                    }
                                    else
                                    {
                                        Abot = (X2-X1)/(Y2-Y1);
                                    
                                        Bbot = Y1 - Abot*X1;

                                    }
                                    // is it high than Top curve?
                                    if ( Abot*xx1 + Bbot > yy1)
                                    {
                                        // A = (X2-X1)/(Y2-Y1)
                                        // B = Y1 - A*X1

                                        //  for left line: Y=X X=-Y
                                        //  
                                        // X[11][0] = -60 = Y1      X[12][0] = -60 = Y2
                                        // Y[11][0] = -60 =-X1      Y[12][0] = -50 =-X2
                                        Y1= DistorX[i][j]; Y2= DistorX[i][j];
                                        X1= -DistorY[i][j]; X2= -DistorY[i+1][j];
                                        long double Aleft = (X2-X1)/(Y2-Y1);
                                        long double Bleft = Y1 - Aleft*X1;
                                        // is it on the right from left curve?
                                        if ( Aleft*yy1 + Bleft > (-xx1))
                                        {
                                            //  for right line: Y=X X=-Y
                                            //  
                                            // X[11][1] = -50 = Y1      X[12][1] = -50 = Y2
                                            // Y[11][1] = -60 =-X1      Y[12][1] = -50 =-X2
                                            Y1= DistorX[i][j]; Y2= DistorX[i][j];
                                            X1= -DistorY[i][j]; X2= -DistorY[i+1][j];
                                            long double Aright = (X2-X1)/(Y2-Y1);
                                            long double Bright = Y1 - Aright*X1;
                                            // is it on the left from right cureve?
                                            if ( Aright*yy1 + Bright <= (-xx1))
                                            {
                                                // now transformation:
                                                // first calculate Y proportion from top curve
                                                // in formula // Y= Atop*X + Bt1
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[12][0] = Xt
                                                //    Y[12][0] = Yt
                                                //    Yt = Atop*Xt + Bt1
                                                //   Bt1 =  Yt - (Atop*Xt)
                                                long double Xt = DistorX[i+1][j];
                                                long double Yt = DistorY[i+1][j];
                                                long double Bt1 = Yt - (Atop*Xt);
                                                // in formula // Y= Atop*X + Bt2
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[12][1] = Xt
                                                //    Y[12][1] = Yt
                                                //    Yt = Atop*Xt + Bt2
                                                //   Bt2 =  Yt - (Atop*Xt)
                                                Xt = DistorX[i+1][j+1];
                                                Yt = DistorY[i+1][j+1];
                                                long double Bt2 =  Yt - (Atop*Xt);
                                                // then needs to find // Y= Atop*X + Bp
                                                // needs to find when this curve will cross X & Y pont:
                                                //    Y = Atop*X + Bp
                                                //   Bp =  Y - (Atop*X)
                                                long double Bp =  yy1 - (Atop*xx1);
                                                // median is crossing of the NORM greed:
                                                long double Bcross1 = ((Bt1 - Btop)/Bp + (Bt2 - Btop)/Bp)/2.0;

                                                /////////////////////////////////////////////////////////////////////////////////////
                                                // now the same for bottom curve:
                                                // in formula // Y= Abot*X + Bt1
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[11][0] = Xt
                                                //    Y[11][0] = Yt
                                                //    Yt = Abot*Xt + Bt1
                                                //   Bt1 =  Yt - (Abot*Xt)
                                                Xt = DistorX[i][j];
                                                Yt = DistorY[i][j];
                                                Bt1 = Yt - (Abot*Xt);
                                                // in formula // Y= Abot*X + Bt2
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[11][1] = Xt
                                                //    Y[11][1] = Yt
                                                //    Yt = Abot*Xt + Bt2
                                                //   Bt2 =  Yt - (Abot*Xt)
                                                Xt = DistorX[i][j+1];
                                                Yt = DistorY[i][j+1];
                                                Bt2 =  Yt - (Abot*Xt);
                                                // then needs to find // Y= Abot*X + Bp
                                                // needs to find when this curve will cross X & Y pont:
                                                //    Y = Abot*X + Bp
                                                //   Bp =  Y - (Abot*X)
                                                Bp =  yy1 - (Abot*xx1);
                                                // median is crossing of the NORM greed:
                                                long double Bcross2 = ((Bt1 - Bbot)/Bp + (Bt2 - Bbot)/Bp)/2.0;

                                                // finally the ofset from initX[11][0]
                                                //   initX[11][0] = XleftTop
                                                //   initY[11][0] = YleftTop
                                                //   initX[12][1] = Xrighttbot
                                                //   initY[12][1] = Yrightbot
                                                long double XleftTop = InitX[i][j];
                                                long double YleftTop = InitY[i][j];
                                                long double Xrightbot = InitX[i+1][j+1];
                                                long double Yrightbot = InitY[i+1][j+1];
                                                // 
                                                long double Yq1 = YleftTop + (Yrightbot-YleftTop)*Bcross1;
                                                long double Yq2 = Yrightbot + (Yrightbot-YleftTop)*Bcross2;
                                                long double Yq = (Yq1+Yq2)/2.0;
                                                yy1 = Yq;
                                            }

                                        }
                                    }
                                }
                            }
                            else if (i == (iLinesInit-2))
                            {
                                // 3 points (j,j+1,j+2) and (i,i+1,i+2)
                                // Y1= A*X1*X1 + B*X1 +C (1)
                                // Y2= A*X2*X2 + B*X2 +C (2)
                                // Y3= A*X3*X3 + B*X3 +C (3)
                                //                                                from (1) & (2):
                                // Y2-Y1 = A* (X2*X2 - X1*X1) + B*(X2-X1)     (4)
                                //                                                from (2) & (3):
                                // Y3-Y2 = A* (X3*X3 - X2*X2) + B*(X3-X2)     (5)
                                //                                                from (4):
                                // B = [(Y2-Y1)  - A* (X2*X2 - X1*X1)] / (X2-X1) (6)
                                //                                                from (5) & (6):
                                // Y3-Y2 = A* (X3*X3 - X2*X2) + [(Y2-Y1)  - A* (X2*X2 - X1*X1)] / (X2-X1) *(X3-X2)
                                // Y3-Y2 = A* (X3*X3 - X2*X2) + (Y2-Y1)/ (X2-X1) *(X3-X2)  - A* (X2*X2 - X1*X1) / (X2-X1) *(X3-X2)
                                // (Y3-Y2)*(X2-X1) = A* (X3*X3 - X2*X2)*(X2-X1) + (Y2-Y1) *(X3-X2)  - A* (X2*X2 - X1*X1)  *(X3-X2)
                                // (Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2) = A* (X3*X3 - X2*X2)*(X2-X1)   - A* (X2*X2 - X1*X1)  *(X3-X2)
                                // A* [(X3*X3 - X2*X2)*(X2-X1)   - (X2*X2 - X1*X1)  *(X3-X2)] = (Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2) 
                                // A = [(Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)] / [(X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2)]
                                // B = ((Y2-Y1)  - A* (X2*X2 - X1*X1)) / (X2-X1)
                                // C = Y1 - A*X1*X1 - B*X1
                                    
                                //  for top line:
                                //  
                                // X[0][0] = -60 = X1      X[0][1] = -50 = X2         X[0][2] = -40 = X3
                                // Y[0][0] =  60 = Y1      Y[0][1] =  60 = Y2         Y[0][2] =  60 = Y3
                                long double X1,X2,X3,Y1,Y2,Y3;
                                X1= DistorX[i][j]; X2= DistorX[i][j+1]; X3= DistorX[i][j+2];
                                Y1= DistorY[i][j]; Y2= DistorY[i][j+1]; Y3= DistorY[i][j+2];
                                long double Atop = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
                                long double Btop = ((Y2-Y1)  - Atop* (X2*X2 - X1*X1)) / (X2-X1);
                                long double Ctop = Y1 - Atop*X1*X1 - Btop*X1;
                                // is it low than Top curve?
                                if ( Atop*xx1*xx1 + Btop*xx1 +Ctop <= yy1)
                                {
                                    //  for bottom line:
                                    //  
                                    // X[1][0] = -60 = X1      X[1][1] = -50 = X2         X[1][2] = -40 = X3
                                    // Y[1][0] =  50 = Y1      Y[1][1] =  50 = Y2         Y[1][2] =  50 = Y3
                                    X1= DistorX[i][j]; X2= DistorX[i][j+1]; X3= DistorX[i][j+2];
                                    Y1= DistorY[i][j]; Y2= DistorY[i][j+1]; Y3= DistorY[i][j+2];
                                    long double Abot = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
                                    long double Bbot = ((Y2-Y1)  - Atop* (X2*X2 - X1*X1)) / (X2-X1);
                                    long double Cbot = Y1 - Atop*X1*X1 - Btop*X1;
                                    // is it high than Top curve?
                                    if ( Abot*xx1*xx1 + Bbot*xx1 +Cbot > yy1)
                                    {

                                        // A = (X2-X1)/(Y2-Y1)
                                        // B = Y1 - A*X1

                                        //  for left line: Y=X X=-Y
                                        //  
                                        // X[11][0] = -60 = Y1      X[12][0] = -60 = Y2
                                        // Y[11][0] = -60 =-X1      Y[12][0] = -50 =-X2
                                        Y1= DistorX[i][j]; Y2= DistorX[i][j];
                                        X1= -DistorY[i][j]; X2= -DistorY[i+1][j];
                                        long double Aleft = (X2-X1)/(Y2-Y1);
                                        long double Bleft = Y1 - Aleft*X1;
                                        // is it on the right from left curve?
                                        if ( Aleft*yy1 + Bleft > (-xx1))
                                        {
                                            //  for right line: Y=X X=-Y
                                            //  
                                            // X[11][1] = -50 = Y1      X[12][1] = -50 = Y2
                                            // Y[11][1] = -60 =-X1      Y[12][1] = -50 =-X2
                                            Y1= DistorX[i][j]; Y2= DistorX[i][j];
                                            X1= -DistorY[i][j]; X2= -DistorY[i+1][j];
                                            long double Aright = (X2-X1)/(Y2-Y1);
                                            long double Bright = Y1 - Aright*X1;
                                            // is it on the left from right cureve?
                                            if ( Aright*yy1 + Bright <= (-xx1))
                                            {
                                                // now transformation:
                                                // first calculate Y proportion from top curve
                                                // in formula // Y= Atop*X*X + Btop*X +Ct1
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[1][0] = Xt
                                                //    Y[1][0] = Yt
                                                //    Yt = Atop*Xt*Xt + Btop*Xt +Ct1
                                                //   Ct1 =  Yt - (Atop*Xt*Xt + Btop*Xt)
                                                long double Xt = DistorX[i+1][j];
                                                long double Yt = DistorY[i+1][j];
                                                long double Ct1 = Yt - (Atop*Xt*Xt + Btop*Xt);
                                                // in formula // Y= Atop*X*X + Btop*X +Ct2
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[1][1] = Xt
                                                //    Y[1][1] = Yt
                                                //    Yt = Atop*Xt*Xt + Btop*Xt +Ct2
                                                //   Ct2 =  Yt - (Atop*Xt*Xt + Btop*Xt)
                                                Xt = DistorX[i+1][j+1];
                                                Yt = DistorY[i+1][j+1];
                                                long double Ct2 =  Yt - (Atop*Xt*Xt + Btop*Xt);
                                                // then needs to find // Y= Atop*X*X + Btop*X +Cp
                                                // needs to find when this curve will cross X & Y pont:
                                                //    Y = Atop*X*X + Btop*X +Cp
                                                //   Cp =  Y - (Atop*X*X + Btop*X)
                                                long double Cp =  yy1 - (Atop*xx1*xx1 + Btop*xx1);
                                                // median is crossing of the NORM greed:
                                                long double Ccross1 = ((Ct1 - Ctop)/Cp + (Ct2 - Ctop)/Cp)/2.0;

                                                /////////////////////////////////////////////////////////////////////////////////////
                                                // now the same for bottom curve:
                                                // in formula // Y= Abot*X*X + Bbot*X +Ct1
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[0][0] = Xt
                                                //    Y[0][0] = Yt
                                                //    Yt = Abot*Xt*Xt + Bbot*Xt +Ct1
                                                //   Ct1 =  Yt - (Abot*Xt*Xt + Bbot*Xt)
                                                Xt = DistorX[i][j];
                                                Yt = DistorY[i][j];
                                                Ct1 = Yt - (Abot*Xt*Xt + Bbot*Xt);
                                                // in formula // Y= Abot*X*X + Bbot*X +Ct2
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[0][1] = Xt
                                                //    Y[0][1] = Yt
                                                //    Yt = Abot*Xt*Xt + Bbot*Xt +Ct2
                                                //   Ct2 =  Yt - (Abot*Xt*Xt + Bbot*Xt)
                                                Xt = DistorX[i][j+1];
                                                Yt = DistorY[i][j+1];
                                                Ct2 =  Yt - (Abot*Xt*Xt + Bbot*Xt);
                                                // then needs to find // Y= Abot*X*X + Bbot*X +Cp
                                                // needs to find when this curve will cross X & Y pont:
                                                //    Y = Abot*X*X + Bbot*X +Cp
                                                //   Cp =  Y - (Abot*X*X + Bbot*X)
                                                Cp =  yy1 - (Abot*xx1*xx1 + Bbot*xx1);
                                                // median is crossing of the NORM greed:
                                                long double Ccross2 = ((Ct1 - Cbot)/Cp + (Ct2 - Cbot)/Cp)/2.0;

                                                // finally the ofset from initX[0][0]
                                                //   initX[0][0] = XleftTop
                                                //   initY[0][0] = YleftTop
                                                //   initX[1][1] = Xrighttbot
                                                //   initY[1][1] = Yrightbot
                                                long double XleftTop = InitX[i][j];
                                                long double YleftTop = InitY[i][j];
                                                long double Xrightbot = InitX[i+1][j+1];
                                                long double Yrightbot = InitY[i+1][j+1];
                                                // 
                                                long double Yq1 = YleftTop + (Yrightbot-YleftTop)*Ccross1;
                                                long double Yq2 = Yrightbot + (Yrightbot-YleftTop)*Ccross2;
                                                long double Yq = (Yq1+Yq2)/2.0;
                                                yy1 = Yq;
                                            }

                                        }
                                    }
                                }
                            }
                            else if (j == (iElementsInit-2))
                            {
                                // 2 points (j,j+1) and (i,i+1)
                                // Y1= A*X1 + B (1)
                                // Y2= A*X2 + B (2)
                                //                                                from (1) & (2):
                                // Y2-Y1 = A* (X2 - X1)     (3)
                                // A = (X2-X1)/(Y2-Y1)
                                // B = Y1 - A*X1
                                //  for top line:
                                //  
                                // X[0][11] = 50 = X1      X[0][12] = 60 = X2
                                // Y[0][11] = 60 = Y1      Y[0][12] = 60 = Y2
                                long double X1,X2,Y1,Y2;
                                X1= DistorX[i][j]; X2= DistorX[i][j+1];
                                Y1= DistorY[i][j]; Y2= DistorY[i][j+1];
                                long double Atop = (X2-X1)/(Y2-Y1);
                                long double Btop = Y1 - Atop*X1;
                                // is it low than Top curve?
                                if ( Atop*xx1 + Btop <= yy1)
                                {
                                    //  for bottom line:
                                    //  
                                    // X[1][11] =  50 = X1      X[1][12] =  60 = X2
                                    // Y[1][11] =  50 = Y1      Y[1][12] =  50 = Y2
                                    X1= DistorX[i][j]; X2= DistorX[i][j+1];
                                    Y1= DistorY[i][j]; Y2= DistorY[i][j+1];
                                    long double Abot = (X2-X1)/(Y2-Y1);
                                    long double Bbot = Y1 - Abot*X1;
                                    // is it high than Top curve?
                                    if ( Abot*xx1 + Bbot > yy1)
                                    {
                                        long double Y3;
                                        long double X3;
                                        //  for left line: Y=X X=-Y
                                        //  
                                        // X[0][0] = -60 = Y1      X[1][0] = -60 = Y2         X[2][0] = -60 = Y3
                                        // Y[0][0] =  60 =-X1      Y[1][0] =  50 =-X2         Y[2][0] =  40 =-X3
                                        Y1= DistorX[i][j]; Y2= DistorX[i][j]; Y3= DistorX[i][j];
                                        X1= -DistorY[i][j]; X2= -DistorY[i+1][j]; X3= -DistorY[i+2][j];
                                        long double Aleft = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
                                        long double Bleft = ((Y2-Y1)  - Atop* (X2*X2 - X1*X1)) / (X2-X1);
                                        long double Cleft = Y1 - Atop*X1*X1 - Btop*X1;
                                        // is it on the right from left curve?
                                        if ( Aleft*yy1*yy1 + Bleft*yy1 +Cleft > (-xx1))
                                        {
                                            //  for right line: Y=X X=-Y
                                            //  
                                            // X[0][1] = -50 = Y1      X[1][1] = -50 = Y2         X[2][1] = -50 = Y3
                                            // Y[0][1] =  60 =-X1      Y[1][1] =  50 =-X2         Y[2][1] =  40 =-X3
                                            Y1= DistorX[i][j]; Y2= DistorX[i][j]; Y3= DistorX[i][j];
                                            X1= -DistorY[i][j]; X2= -DistorY[i+1][j]; X3= -DistorY[i+2][j];
                                            long double Aright = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
                                            long double Bright = ((Y2-Y1)  - Atop* (X2*X2 - X1*X1)) / (X2-X1);
                                            long double Cright = Y1 - Atop*X1*X1 - Btop*X1;
                                            // is it on the left from right cureve?
                                            if ( Aright*yy1*yy1 + Bright*yy1 +Cright <= (-xx1))
                                            {
                                                // now transformation:
                                                // first calculate Y proportion from top curve
                                                // in formula // Y= Atop*X + Bt
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[1][11] = Xt
                                                //    Y[1][11] = Yt
                                                //    Yt = Atop*Xt + Btop
                                                //   Bt1 =  Yt - (Atop*Xt)
                                                long double Xt = DistorX[i+1][j];
                                                long double Yt = DistorY[i+1][j];
                                                long double Bt1 = Yt - (Atop*Xt);
                                                // in formula // Y= Atop*X + Bt2
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[1][12] = Xt
                                                //    Y[1][12] = Yt
                                                //    Yt = Atop*Xt + Bt2
                                                //   Bt2 =  Yt - (Atop*Xt)
                                                Xt = DistorX[i+1][j+1];
                                                Yt = DistorY[i+1][j+1];
                                                long double Bt2 =  Yt - (Atop*Xt);
                                                // then needs to find // Y= Atop*X + Bp
                                                // needs to find when this curve will cross X & Y pont:
                                                //    Y = Atop*X + Bp
                                                //   Bp =  Y - (Atop*X)
                                                long double Bp =  yy1 - (Atop*xx1);
                                                // median is crossing of the NORM greed:
                                                long double Bcross1 = ((Bt1 - Btop)/Bp + (Bt2 - Btop)/Bp)/2.0;

                                                /////////////////////////////////////////////////////////////////////////////////////
                                                // now the same for bottom curve:
                                                // in formula // Y= Abot*X + Bt1
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[0][0] = Xt
                                                //    Y[0][0] = Yt
                                                //    Yt = Abot*Xt + Bbot*Xt +Bt1
                                                //   Bt1 =  Yt - (Abot*Xt)
                                                Xt = DistorX[i][j];
                                                Yt = DistorY[i][j];
                                                Bt1 = Yt - (Abot*Xt);
                                                // in formula // Y= Abot*X*X + Bt2
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[0][1] = Xt
                                                //    Y[0][1] = Yt
                                                //    Yt = Abot*Xt*Xt + Bt2
                                                //   Bt2 =  Yt - (Abot*Xt)
                                                Xt = DistorX[i][j+1];
                                                Yt = DistorY[i][j+1];
                                                Bt2 =  Yt - (Abot*Xt);
                                                // then needs to find // Y= Abot*X*X + Bp
                                                // needs to find when this curve will cross X & Y pont:
                                                //    Y = Abot*X +Bp
                                                //   Bp =  Y - (Abot*X)
                                                Bp =  yy1 - (Abot*xx1);
                                                // median is crossing of the NORM greed:
                                                long double Bcross2 = ((Bt1 - Bbot)/Bp + (Bt2 - Bbot)/Bp)/2.0;

                                                // finally the ofset from initX[0][0]
                                                //   initX[0][0] = XleftTop
                                                //   initY[0][0] = YleftTop
                                                //   initX[1][1] = Xrighttbot
                                                //   initY[1][1] = Yrightbot
                                                long double XleftTop = InitX[i][j];
                                                long double YleftTop = InitY[i][j];
                                                long double Xrightbot = InitX[i+1][j+1];
                                                long double Yrightbot = InitY[i+1][j+1];
                                                // 
                                                long double Yq1 = YleftTop + (Yrightbot-YleftTop)*Bcross1;
                                                long double Yq2 = Yrightbot + (Yrightbot-YleftTop)*Bcross2;
                                                long double Yq = (Yq1+Yq2)/2.0;
                                                yy1 = Yq;
                                            }

                                        }
                                    }
                                }
                            }
                            else   // main case 
                            {
                                // 3 points (j,j+1,j+2) and (i,i+1,i+2)
                                // Y1= A*X1*X1 + B*X1 +C (1)
                                // Y2= A*X2*X2 + B*X2 +C (2)
                                // Y3= A*X3*X3 + B*X3 +C (3)
                                //                                                from (1) & (2):
                                // Y2-Y1 = A* (X2*X2 - X1*X1) + B*(X2-X1)     (4)
                                //                                                from (2) & (3):
                                // Y3-Y2 = A* (X3*X3 - X2*X2) + B*(X3-X2)     (5)
                                //                                                from (4):
                                // B = [(Y2-Y1)  - A* (X2*X2 - X1*X1)] / (X2-X1) (6)
                                //                                                from (5) & (6):
                                // Y3-Y2 = A* (X3*X3 - X2*X2) + [(Y2-Y1)  - A* (X2*X2 - X1*X1)] / (X2-X1) *(X3-X2)
                                // Y3-Y2 = A* (X3*X3 - X2*X2) + (Y2-Y1)/ (X2-X1) *(X3-X2)  - A* (X2*X2 - X1*X1) / (X2-X1) *(X3-X2)
                                // (Y3-Y2)*(X2-X1) = A* (X3*X3 - X2*X2)*(X2-X1) + (Y2-Y1) *(X3-X2)  - A* (X2*X2 - X1*X1)  *(X3-X2)
                                // (Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2) = A* (X3*X3 - X2*X2)*(X2-X1)   - A* (X2*X2 - X1*X1)  *(X3-X2)
                                // A* [(X3*X3 - X2*X2)*(X2-X1)   - (X2*X2 - X1*X1)  *(X3-X2)] = (Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2) 
                                // A = [(Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)] / [(X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2)]
                                // B = ((Y2-Y1)  - A* (X2*X2 - X1*X1)) / (X2-X1)
                                // C = Y1 - A*X1*X1 - B*X1
                                    
                                //  for top line:
                                //  
                                // X[0][0] = -60 = X1      X[0][1] = -50 = X2         X[0][2] = -40 = X3
                                // Y[0][0] =  60 = Y1      Y[0][1] =  60 = Y2         Y[0][2] =  60 = Y3
                                long double X1,X2,X3,Y1,Y2,Y3;
                                X1= DistorX[i][j]; X2= DistorX[i][j+1]; X3= DistorX[i][j+2];
                                Y1= DistorY[i][j]; Y2= DistorY[i][j+1]; Y3= DistorY[i][j+2];
                                long double Atop = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
                                long double Btop = ((Y2-Y1)  - Atop* (X2*X2 - X1*X1)) / (X2-X1);
                                long double Ctop = Y1 - Atop*X1*X1 - Btop*X1;
                                // is it low than Top curve?
                                if ( Atop*xx1*xx1 + Btop*xx1 +Ctop <= yy1)
                                {
                                    //  for bottom line:
                                    //  
                                    // X[1][0] = -60 = X1      X[1][1] = -50 = X2         X[1][2] = -40 = X3
                                    // Y[1][0] =  50 = Y1      Y[1][1] =  50 = Y2         Y[1][2] =  50 = Y3
                                    X1= DistorX[i][j]; X2= DistorX[i][j+1]; X3= DistorX[i][j+2];
                                    Y1= DistorY[i][j]; Y2= DistorY[i][j+1]; Y3= DistorY[i][j+2];
                                    long double Abot = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
                                    long double Bbot = ((Y2-Y1)  - Atop* (X2*X2 - X1*X1)) / (X2-X1);
                                    long double Cbot = Y1 - Atop*X1*X1 - Btop*X1;
                                    // is it high than Top curve?
                                    if ( Abot*xx1*xx1 + Bbot*xx1 +Cbot > yy1)
                                    {
                                        //  for left line: Y=X X=-Y
                                        //  
                                        // X[0][0] = -60 = Y1      X[1][0] = -60 = Y2         X[2][0] = -60 = Y3
                                        // Y[0][0] =  60 =-X1      Y[1][0] =  50 =-X2         Y[2][0] =  40 =-X3
                                        Y1= DistorX[i][j]; Y2= DistorX[i][j]; Y3= DistorX[i][j];
                                        X1= -DistorY[i][j]; X2= -DistorY[i+1][j]; X3= -DistorY[i+2][j];
                                        long double Aleft = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
                                        long double Bleft = ((Y2-Y1)  - Atop* (X2*X2 - X1*X1)) / (X2-X1);
                                        long double Cleft = Y1 - Atop*X1*X1 - Btop*X1;
                                        // is it on the right from left curve?
                                        if ( Aleft*yy1*yy1 + Bleft*yy1 +Cleft > (-xx1))
                                        {
                                            //  for right line: Y=X X=-Y
                                            //  
                                            // X[0][1] = -50 = Y1      X[1][1] = -50 = Y2         X[2][1] = -50 = Y3
                                            // Y[0][1] =  60 =-X1      Y[1][1] =  50 =-X2         Y[2][1] =  40 =-X3
                                            Y1= DistorX[i][j]; Y2= DistorX[i][j]; Y3= DistorX[i][j];
                                            X1= -DistorY[i][j]; X2= -DistorY[i+1][j]; X3= -DistorY[i+2][j];
                                            long double Aright = ((Y3-Y2)*(X2-X1)- (Y2-Y1) *(X3-X2)) / ((X3*X3 - X2*X2)*(X2-X1) - (X2*X2 - X1*X1)  *(X3-X2));
                                            long double Bright = ((Y2-Y1)  - Atop* (X2*X2 - X1*X1)) / (X2-X1);
                                            long double Cright = Y1 - Atop*X1*X1 - Btop*X1;
                                            // is it on the left from right cureve?
                                            if ( Aright*yy1*yy1 + Bright*yy1 +Cright <= (-xx1))
                                            {
                                                // now transformation:
                                                // first calculate Y proportion from top curve
                                                // in formula // Y= Atop*X*X + Btop*X +Ct1
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[1][0] = Xt
                                                //    Y[1][0] = Yt
                                                //    Yt = Atop*Xt*Xt + Btop*Xt +Ct1
                                                //   Ct1 =  Yt - (Atop*Xt*Xt + Btop*Xt)
                                                long double Xt = DistorX[i+1][j];
                                                long double Yt = DistorY[i+1][j];
                                                long double Ct1 = Yt - (Atop*Xt*Xt + Btop*Xt);
                                                // in formula // Y= Atop*X*X + Btop*X +Ct2
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[1][1] = Xt
                                                //    Y[1][1] = Yt
                                                //    Yt = Atop*Xt*Xt + Btop*Xt +Ct2
                                                //   Ct2 =  Yt - (Atop*Xt*Xt + Btop*Xt)
                                                Xt = DistorX[i+1][j+1];
                                                Yt = DistorY[i+1][j+1];
                                                long double Ct2 =  Yt - (Atop*Xt*Xt + Btop*Xt);
                                                // then needs to find // Y= Atop*X*X + Btop*X +Cp
                                                // needs to find when this curve will cross X & Y pont:
                                                //    Y = Atop*X*X + Btop*X +Cp
                                                //   Cp =  Y - (Atop*X*X + Btop*X)
                                                long double Cp =  yy1 - (Atop*xx1*xx1 + Btop*xx1);
                                                // median is crossing of the NORM greed:
                                                long double Ccross1 = ((Ct1 - Ctop)/Cp + (Ct2 - Ctop)/Cp)/2.0;

                                                /////////////////////////////////////////////////////////////////////////////////////
                                                // now the same for bottom curve:
                                                // in formula // Y= Abot*X*X + Bbot*X +Ct1
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[0][0] = Xt
                                                //    Y[0][0] = Yt
                                                //    Yt = Abot*Xt*Xt + Bbot*Xt +Ct1
                                                //   Ct1 =  Yt - (Abot*Xt*Xt + Bbot*Xt)
                                                Xt = DistorX[i][j];
                                                Yt = DistorY[i][j];
                                                Ct1 = Yt - (Abot*Xt*Xt + Bbot*Xt);
                                                // in formula // Y= Abot*X*X + Bbot*X +Ct2
                                                // needs to find when this curve will cross bottom curve pont:
                                                //    X[0][1] = Xt
                                                //    Y[0][1] = Yt
                                                //    Yt = Abot*Xt*Xt + Bbot*Xt +Ct2
                                                //   Ct2 =  Yt - (Abot*Xt*Xt + Bbot*Xt)
                                                Xt = DistorX[i][j+1];
                                                Yt = DistorY[i][j+1];
                                                Ct2 =  Yt - (Abot*Xt*Xt + Bbot*Xt);
                                                // then needs to find // Y= Abot*X*X + Bbot*X +Cp
                                                // needs to find when this curve will cross X & Y pont:
                                                //    Y = Abot*X*X + Bbot*X +Cp
                                                //   Cp =  Y - (Abot*X*X + Bbot*X)
                                                Cp =  yy1 - (Abot*xx1*xx1 + Bbot*xx1);
                                                // median is crossing of the NORM greed:
                                                long double Ccross2 = ((Ct1 - Cbot)/Cp + (Ct2 - Cbot)/Cp)/2.0;

                                                // finally the ofset from initX[0][0]
                                                //   initX[0][0] = XleftTop
                                                //   initY[0][0] = YleftTop
                                                //   initX[1][1] = Xrighttbot
                                                //   initY[1][1] = Yrightbot
                                                long double XleftTop = InitX[i][j];
                                                long double YleftTop = InitY[i][j];
                                                long double Xrightbot = InitX[i+1][j+1];
                                                long double Yrightbot = InitY[i+1][j+1];
                                                // 
                                                long double Yq1 = YleftTop + (Yrightbot-YleftTop)*Ccross1;
                                                long double Yq2 = Yrightbot + (Yrightbot-YleftTop)*Ccross2;
                                                long double Yq = (Yq1+Yq2)/2.0;
                                                yy1 = Yq;
                                            }

                                        }
                                    }
                                }
                            }
  */                          
                            /*
                            if ((InitX[ix][iy] <= (X+iOffsetX)) && (InitY[ix][iy] <= (Y+iOffsetY)) && (InitX[ix+1][iy+1] > (X+iOffsetX)) && (InitY[ix+1][iy+1] > (Y+iOffsetY)))
                            {
                                // ditorsion found
                                long double XX = InitX[ix+1][iy+1] - InitX[ix][iy];
                                long double YY = InitY[ix+1][iy+1] - InitY[ix][iy];

                                long double xXXd1 = DistorX[ix+1][iy] - DistorX[ix][iy];
                                long double xYYd1 = DistorY[ix+1][iy] - DistorY[ix][iy];

                                long double xXXd2 = DistorX[ix+1][iy+1] - DistorX[ix][iy+1];
                                long double xYYd2 = DistorY[ix+1][iy+1] - DistorY[ix][iy+1];

                                long double yXXd3 = DistorX[ix][iy+1] - DistorX[ix][iy];
                                long double yYYd3 = DistorY[ix][iy+1] - DistorY[ix][iy];

                                long double yXXd4 = DistorX[ix+1][iy+1] - DistorX[ix+1][iy];
                                long double yYYd4 = DistorY[ix+1][iy+1] - DistorY[ix+1][iy];

                                long double x11 = DistorX[ix][iy] + (X+iOffsetX-DistorX[ix][iy])/XX * xXXd1;
                                long double y11 = DistorY[ix][iy] + (Y+iOffsetY-DistorY[ix][iy])/YY * xYYd1;

                                long double x21 = DistorX[ix][iy+1] + (X+iOffsetX-DistorX[ix][iy+1])/XX * xXXd2;
                                long double y21 = DistorY[ix][iy+1] + (Y+iOffsetY-DistorY[ix][iy+1])/YY * xYYd2;
                                long double x1 = x11+ (X+iOffsetX-DistorX[ix][iy])/XX * yXXd3;
                                long double y1 = (y11+y21)/2;

                                long double x12 = DistorX[ix][iy] + (X+iOffsetX-DistorX[ix][iy])/XX * yXXd3;
                                long double y12 = DistorY[ix][iy] + (Y+iOffsetY-DistorY[ix][iy])/YY * yYYd3;

                                long double x22 = DistorX[ix+1][iy] + (X+iOffsetX-DistorX[ix+1][iy])/XX * yXXd4;
                                long double y22 = DistorX[ix+1][iy] + (Y+iOffsetY-DistorX[ix+1][iy])/YY * yYYd4;

                                long double x2 = (x12+x22)/2;
                                long double y2 = y12+(Y+iOffsetY-DistorY[ix][iy])/YY * xYYd2;

                                xx1 = (x1+x2)/2;
                                yy1 = (y1+y2)/2;
                                goto DONE_DIST;
                            }
                            */
                        }
                    }
DONE_DIST:
                    fprintf(OutputMesh,"v %10.6f %10.6f %10.6f \n",(xx1-iOffsetX),(yy1-iOffsetY),Z);                
                }
                else
                    fprintf(OutputMesh,"%s",szString);
            }
        }
        fclose(InputMesh);
    }
	return 0;
}

