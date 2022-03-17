#include <stdio.h>
#include <math.h>

typedef int bool;
#define true  1
#define false 0


float fx (float x)
{
  return (1.0 / x);
}


float romb (float lower, float upper, float tol)
{
    int nx [16];
    float t [136];
    
    bool done = false;
    bool error = false;
    int pieces = 1;
    nx[1] = 1;
    float delta_x = (upper - lower) / pieces;
    float c = (fx(lower) + fx(upper)) * 0.5;
    t[1] = delta_x * c;
    int n = 1;
    int nn = 2;
    float sum = c;
    
    float fotom,x;
    int l,i,j,k,nt,ntra; 
    do 
    {
        n = n+1;
        fotom = 4;
        nx[n] = nn;
        pieces = pieces * 2;
        l = pieces - 1;
        delta_x = (upper - lower) / pieces;
        
        int ll = (l+1)/2;
        for(int ii = 1; ii <= ll; ii++)
        {
	      i = ii * 2 - 1;
	      x = lower + i * delta_x;
	      sum = sum + fx(x);
        }
        
        t[nn] = delta_x * sum;
        
        ntra = nx[n-1];
        k = n-1;
        
        for(int m = 1; m <= k; m++)
        {
	        j = nn+m;
	        nt = nx[n - 1] + m - 1;
	        t[j] = (fotom * t[j - 1] - t[nt]) / (fotom-1.0);
	        fotom = fotom * 4;
        }
          
        if (n > 4)
        {
	        if (t[nn + 1] != 0.0) {
	            if ((fabs(t[ntra+1]-t[nn+1])<=fabs(t[nn+1]*tol))
	            || (fabs(t[nn-1]-t[j])<=fabs(t[j]*tol)))
	            {
	                done = true;
	            } else 
	            if (n>15) {
	   	           done = true;
	               error = true;
	            }
	        }
        }	
        nn = j+1;    
    } while (!done);
    
    return (t[j]);
}


int main()
{
    const float tol = 1.0E-4;
    float lower = 1.0;
    float upper = 9.0;
    float sum = romb(lower,upper,tol);

    return 0;
}
