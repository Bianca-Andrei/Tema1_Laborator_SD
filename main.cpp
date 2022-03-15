#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sys/time.h>
#include <algorithm>
using namespace std;
ifstream f("date.in");

bool verificare_sortare(vector<long> &v, long n)
{
    long i;
    for(i=0;i<n-1;i++)
        if (v[i]>v[i+1]) return 0;
    return 1;
}

// aici incep subprogramele pentru mergesort

void mergesort(vector <long> &v, long left, long right, long long m)
{
    long i = left, j = m+1;
    vector <long> aux;
    while(i <= m && j <= right)
    {
        if(v[i]<=v[j])
            aux.push_back(v[i++]);
        else aux.push_back(v[j++]);

    }
    while(i<=m)
        aux.push_back(v[i++]);
    while(j<=right)
        aux.push_back(v[j++]);
    long k = aux.size();
    for(i=0;i<k;i++)
        v.at(left+i) = aux.at(i);
    aux.clear();


}

void combine(vector <long> &v, long left, long right)
{
    long m;
    if (left<right)
    {
        m = (left+right)/2;
        combine(v, left, m);
        combine(v, m+1, right);
        mergesort(v, left, right, m);
    }
}

//subprogram ce afla valoarea maxima dintr-un vector

long maximum(vector <long> &v, long n)
{   long maxim=0;
    for (long i=0;i<n;i++)
        if(v[i]>maxim) maxim=v[i];
    return maxim;
}

//aici incep subprogramele pentru radixsort

void num(vector <long> &v, long n, long putere, int baza)
{
    long fr[10];
    vector <long> aux;
    int i, maxim = maximum(v, n), j;
    for(i=0;i<=9;i++)
        fr[i]=0;
    for(i=0;i<n;i++)
        fr[(v[i]/putere)%baza]++;
    for(i=1;i<=9;i++)
        fr[i] += fr[i-1];
    for (i=0;i<n;i++)
        aux.push_back(0);
    for (i=n-1;i>=0;i--)
    {   long c = (v[i]/putere)%baza;
        aux[fr[c]-1] = v[i];
    fr[c]--;
    }
    for(i=0;i<n;i++)
        v[i]=aux[i];
    aux.clear();

}

void radixsort(vector <long> &v, long n, int baza)
{
   long maxim, putere = 1;
   maxim = maximum(v, n);
   while(maxim/putere)
   {
        num(v, n, putere, baza);
        putere *= baza;
   }

}

void num_2(vector <long> &v, long n, long putere, int baza)
{
    long fr[baza];
    vector <long> aux;
    int i, maxim = maximum(v, n), j;
    long copie = putere;
    int nr=0;
    while(copie>>1)
    {
        nr++;
        copie = copie>>1;
    }
    for(i=0;i<=baza-1;i++)
        fr[i]=0;
    for(i=0;i<n;i++)
        fr[(v[i]>>nr)%baza]++;
    for(i=1;i<baza;i++)
        fr[i] += fr[i-1];
    for (i=0;i<n;i++)
        aux.push_back(0);
    for (i=n-1;i>=0;i--)
    {   long c = (v[i]>>nr)%baza;
        aux[fr[c]-1] = v[i];
    fr[c]--;
    }
    for(i=0;i<n;i++)
        v[i]=aux[i];
    aux.clear();

}

void radixsort_2(vector <long> &v, long n, int baza)
{
   long maxim, putere = 1;
   maxim = maximum(v, n);
   int exp=0;
   int copie = baza;
   while(copie>>1)
   {
       exp++;
       copie = copie>>1;
   }
   while(maxim/putere)
   {
        num_2(v, n, putere, baza);
        putere = putere <<exp;
   }

}

//aici incepe subprogramul pentru shellsort

void shellsort(vector <long> &v, long n)
{
    long i, start, j, aux, k;
    start = n>>1;
    for(i=start;i>0;i=i>>1)
        for(j=i;j<n;j++)
    {
        aux = v[j];
        for(k=j;k>=i;k-=i)
        {
            if(v[k-i]<=aux) break;
            v[k] = v[k-i];
        }
        v[k] = aux;
    }

}

//aici incepe subprogramul pentru countingsort

void counting(vector <long> &v, long n)
{
    vector <long> fr;
    long i;
    long maxim=0;
    for (i=0;i<n;i++)
        if(v.at(i)>maxim) maxim=v.at(i);
    for (i=0;i<=maxim;i++)
        fr.push_back(0);
    for(i=0;i<n;i++)
        fr[v[i]]++;
    v.clear();
    int m = fr.size();
    for(i=0;i<m;i++)
       for(int j=0;j<fr.at(i);j++)
            v.push_back(i);

}

//aici incepe subprogramul pentru bubblesort

void bubblesort(vector<long> &v, long n)
{
    long i, j, k, aux;
    bool ok;
    ok = 1;
    k = 1;
    while(ok==1)
    {
        ok=0;
        for (i=0;i<n-k;i++)
            if(v[i]>v[i+1])
        {
            aux = v[i];
            v[i] = v[i+1];
            v[i+1] = aux;
            ok = 1;
        }
        k++;
    }
}

int main()
{
    vector <long> a;
    vector <long> b;
    long i, j, nr_teste, n, maxim, x;
    f>>nr_teste;
    for(j=0;j<nr_teste;j++)
    {
        f>>n>>maxim;
        cout<<"TESTUL "<<j+1<<endl;
        cout<<n<<" "<<maxim<<endl;
        for (i=0;i<n;i++)
        {
            f>>x;
            a.push_back(x);
        }

        timeval start, stop;
        long secunde, microsecunde;
        b = a;
        gettimeofday(&start, 0);
        combine(b, 0, n-1);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"MERGE SORT: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();

        b = a;
        gettimeofday(&start, 0);
        radixsort(b, n, 10);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"RADIX SORT in baza 10: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();

        b = a;
        gettimeofday(&start, 0);
        radixsort_2(b, n, 2);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"RADIX SORT in baza 2: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();

        b = a;
        gettimeofday(&start, 0);
        radixsort_2(b, n, 8);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"RADIX SORT in baza 8: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();

        b = a;
        gettimeofday(&start, 0);
        radixsort_2(b, n, 16);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"RADIX SORT in baza 16: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();

        b = a;
        gettimeofday(&start, 0);
        shellsort(b, n);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"SHELL SORT: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();
        b = a;
        gettimeofday(&start, 0);
        bubblesort(b, n);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"BUBBLE SORT: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();

        b = a;
        gettimeofday(&start, 0);
        counting(b, n);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"COUNTING SORT: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();

        b = a;
        gettimeofday(&start, 0);
        sort(b.begin(), b.begin()+n);
        gettimeofday(&stop, 0);
        secunde = stop.tv_sec - start.tv_sec;
        microsecunde = stop.tv_usec - start.tv_usec;
        cout<<"SORT: "<<secunde+microsecunde*1e-6<<" secunde, ";
        if (verificare_sortare(b, n)) cout<<"sortat corect";
        else cout<<"nesortat";
        cout<<endl;
        b.clear();

        a.clear();
    }
}
