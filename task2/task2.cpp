#include <math.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

bool hit(float A[], float B[], float C[], float D[], float P[]){ // принадлежность вершине
    bool detection = false;
    if (((A[0]-P[0]==0)&&(A[1]-P[1]==0))||((B[0]-P[0]==0)&&(B[1]-P[1]==0))||((C[0]-P[0]==0)&&(C[1]-P[1]==0))||((D[0]-P[0]==0)&&(D[1]-P[1]==0))){
        detection = true;
    }
    return detection;
}

bool inclusion(float A[], float B[], float P[]){ // проверка принадлежности точки одной из сторон
    bool incl = false;
    float a, b;
    a = ((P[0]-A[0])/(B[0]-A[0]));
    b = ((P[1]-A[1])/(B[1]-A[1]));
    a = floor(a*100)/100;
    b = floor(b*100)/100;
    if (a==b){
        incl = true;
    }
    return incl;
}

float distance(float A[], float B[]){ // построение вектора от точки A до точки B
    float dis = sqrt(pow((B[0]-A[0]),2)+pow((B[1]-A[1]),2));
    return dis;
}

float Heron(float a, float b, float c){ // формула Герона
    float p;
    p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

int main(int argc, char *argv[])
{
    setlocale(0, "");

    char *str = new char [1024];
    float *A = new float[2];
    float *B = new float[2];
    float *C = new float[2];
    float *D = new float[2];
    float *P = new float[2];
    float *d = new float[5];
    float *o = new float[4];
    int n;
    bool factor;
    float s1, s2;

    ifstream f1in(argv[1]);
    f1in >> A[0];
    f1in >> A[1];
    f1in >> B[0];
    f1in >> B[1];
    f1in >> C[0];
    f1in >> C[1];
    f1in >> D[0];
    f1in >> D[1];

    ifstream amount(argv[2]);
    while (!amount.eof()){
        amount.getline(str, 1024, '\n');
        n++;
    }
    amount.close();
    ifstream f2in(argv[2]);
    for (int i = 0; i<n; i++){
        factor = false;
        f2in >> P[0];
        f2in >> P[1];
        factor = hit(A,B,C,D,P);
        if (factor == true){
            printf("%s", "0\n");
            continue;
        }
        while(true){
            factor = inclusion(A,B,P);
            if (factor == true) break;
            factor = inclusion(B,C,P);
            if (factor == true) break;
            factor = inclusion(C,D,P);
            if (factor == true) break;
            factor = inclusion(D,A,P);
            break;
        }
        if (factor == true){
            printf("%s", "1\n");
            continue;
        }
        d[0]=distance(A,B);
        d[1]=distance(B,C);
        d[2]=distance(C,D);
        d[3]=distance(D,A);
        d[4]=distance(A,C);
        o[0]=distance(A,P);
        o[1]=distance(B,P);
        o[2]=distance(C,P);
        o[3]=distance(D,P);
        s1 = round(Heron(d[0],d[1],d[4])+Heron(d[2],d[3],d[4]));
        s2 = round(Heron(o[0],d[0],o[1])+Heron(o[1],d[1],o[2])+Heron(o[2],d[2],o[3])+Heron(o[3],d[3],o[0]));
        if (s1==s2){
            printf("%s", "2\n");
        }
        else printf("%s", "3\n");
    }

    f1in.close();
    f2in.close();
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] D;
    delete[] P;
    delete[] d;
    delete[] o;

    return 0;
}
