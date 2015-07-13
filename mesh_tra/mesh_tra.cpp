// mesh_tra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    long double DistorX[100][100];
    long double DistorY[100][100];
    int iLines;
    int iElements;
    long double iOffsetX = atof(argv[5]);
    long double iOffsetY = atof(argv[6]);


    char szDistor[1024];
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

                    for (int ix= 0; ix < iLinesInit-1; ix++)
                    {
                        for (int iy = 0; iy < iElementsInit-1; iy ++)
                        {
                            // Y = A * X^2 + B * X + C
                            // A = [(Y2-Y1)(X1-X3) + (Y3-Y1)(X2-X1)]/[(X1-X3)(X2^2-X1^2) + (X2-X1)(X3^2-X1^2)]
                            // B = [(Y2 - Y1) - A(X2^2 - X1^2)] / (X2-X1)
                            // C = Y1 - AX1^2 - BX1

                            if (

                            
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
                        }
                    }
DONE_DIST:
                    fprintf(OutputMesh,"v %10.6f %10.6f %10.6f \n",(xx1-iOffsetX),(yy1+iOffsetY),Z);                
                }
                else
                    fprintf(OutputMesh,"%s",szString);
            }
        }
        fclose(InputMesh);
    }
	return 0;
}

