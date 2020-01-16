#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

double percental(int N[], double percent, int n){
    double k = (n-1)*percent;
    int f = floor(k);
    int c = ceil(k);
    if (f==c) return N[int(f)]*(c-k);
    double d0 = N[f]*(c-k);
    double d1 = N[c]*(k-f);
    double res = d0+d1;
    return res;
}

int main(int argc, char *argv[])
{
    double avg = 0;
    char *str = new char [1024];
    int n = 0;
    ifstream amount(argv[1]);
    while (!amount.eof()){
        amount.getline(str, 1024, '\n');
        n++;
    }
    amount.close();
    int *arr = new int[n];
    ifstream fin(argv[1]);
    for (int i=0; i<=n-1; i++){
        fin >> arr[i];
        avg += arr[i];
    }
    sort (arr, arr+n);
    double prc = percental(arr,0.9,n);
    double mdn = percental(arr,0.5,n);
    double max = arr[n-1];
    double min = arr[0];
    avg = avg/n;
    printf("%.2f",prc);
    printf("%s","\n");
    printf("%.2f",mdn);
    printf("%s","\n");
    printf("%.2f",max);
    printf("%s","\n");
    printf("%.2f",min);
    printf("%s","\n");
    printf("%.2f",avg);
    fin.close();
    return 0;
}
