#include <stdio.h>
#include <omp.h>
static long num_steps = 1000000000;
double step;
double time;
#define GAP 1


void main()
{

 int i,p,pid;
 double x, pi, sum = 0.0;
 double localsum[4*GAP];

 time = omp_get_wtime();

 step = 1.0/(double) num_steps;

#pragma omp parallel num_threads(4) shared(p,localsum,step,num_steps) private(pid,i,x)
{
 pid = omp_get_thread_num();
 p = omp_get_num_threads();
 //printf(" num threads (%d) ",p);
 
 int myfirst = (num_steps/p) * pid;
 int mylast = (num_steps/p) * (pid+1)-1;
 localsum[pid*GAP] = 0.0;
 

 for (i=myfirst; i<mylast; i++)
 {
   x = (i+0.5)*step;
   localsum[pid*GAP] += 4.0/(1.0+x*x);
 }
}

 for (i=0; i<p; i++)
   sum += localsum[i*GAP];

 pi = step * sum;

 time = omp_get_wtime() - time;

 printf(" Value of pi =%lf   time = %lf s \n ",pi,time);

}
