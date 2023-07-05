#include <stdio.h>
#define DEBUG
const int MAX_COLL_RYD = 30;
const int MAX_COLL_SIMVOLOV = 5;

struct Zal
{
    int collRyd, collVipRyd, collMest[MAX_COLL_RYD],
        collZakMest,
        countVip = 0, countOst = 0;
    float costVip, costOst;
    char prizV;
};

typedef char tInden[MAX_COLL_SIMVOLOV];

void inzDannix(Zal &zal)
{
    int i;

    for(i = 1; i < zal.collRyd; i++)
    {
        zal.collMest[i] = zal.collMest[0];
    }

    return;
}

int naxSvobodniiRyd(Zal &zal)
{
    int i;

    if (zal.prizV == 'v')
    {
        for(i = 0; i < zal.collVipRyd; i++)
        {
            if(zal.collZakMest <= zal.collMest[i])
            {
                zal.countVip ++;
                return i;
            }
        }
    }
    else
    {
        for(i = zal.collVipRyd; i < zal.collRyd; i++)
        {
            if(zal.collZakMest <= zal.collMest[i])
            {
                zal.countOst++;
                return i;
            }
        }
    }

    return -1;
}

#ifdef DEBUG
void vizZal(Zal zal, int constM)
{
    int i, j,
        tempM;

	printf("    12345678901234567890\n");

	for(i = 0; i < zal.collRyd; i++)
    {
		printf("%2d| ", i+1);

		if(i % 2 == 1)
        {
            for(j = 0; j < zal.collMest[i]; j++)
            {
                printf(".");
            }
            for(j = zal.collMest[i]; j < constM; j++)
            {
                printf("*");
            }
        }
        else
        {
            tempM = constM - zal.collMest[i];

            for(j = 0; j < tempM; j++)
            {
                printf("*");
            }
            for(j = tempM; j < constM; j++)
            {
                printf(".");
            }
        }

        printf("\n");
    }

    return;
}
#endif

int main()
{
    Zal zal;
    tInden ind;

    int tempR, tempM, constM;

    FILE *fIn0,
         *fIn1,
         *fOut;

    fIn0 = fopen("ex0121_3.in0", "r");
    fIn1 = fopen("ex0121_3.in1", "r");
    fOut = fopen("ex0121_3.out", "w");

    fscanf(fIn0,"%d %d %d %f %f", &zal.collRyd, &zal.collMest[0], &zal.collVipRyd, &zal.costVip, &zal.costOst);

    fclose(fIn0);

    inzDannix(zal);

    constM = zal.collMest[0];

	while(fscanf(fIn1, "%s %d \n%c", &ind, &zal.collZakMest, &zal.prizV) == 3)
    {
#ifdef DEBUG
printf("%s %d %c\n", ind, zal.collZakMest, zal.prizV);
#endif

        tempR = naxSvobodniiRyd(zal);

        if(tempR != -1)
        {
            if (tempR % 2 == 1)
            {
                fprintf(fOut, "%s %d %d-%d\n", ind, tempR + 1, zal.collMest[tempR] - zal.collZakMest + 1, zal.collMest[tempR]);
#ifdef DEBUG
printf("%d, %d-%d\n", tempR +1, zal.collMest[tempR] - zal.collZakMest + 1, zal.collMest[tempR]);
#endif
				zal.collMest[tempR] -= zal.collZakMest;
            }
            else
            {
                tempM = constM - zal.collMest[tempR];
                fprintf(fOut, "%s %d %d-%d\n", ind, tempR + 1, tempM + 1, tempM + zal.collZakMest);
#ifdef DEBUG
printf("%d, %d-%d\n", tempR + 1, tempM + 1, tempM + zal.collZakMest);
#endif
				zal.collMest[tempR] -= zal.collZakMest;
            }
        }
        else
        {
            fprintf(fOut, "%s absent\n", ind);
#ifdef DEBUG
printf("%s absent\n", ind);
#endif
		}
#ifdef DEBUG
vizZal(zal, constM);
printf("\n\n");
#endif

    }

    fprintf(fOut,"%d %1.2f\n%d %1.2f", zal.countVip, zal.countVip * zal.costVip, zal.countOst, zal.countOst * zal.costOst);

    fclose(fIn1);
    fclose(fOut);

    return 0;
}

//Итог. Задача выполнена.
