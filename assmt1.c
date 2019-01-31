/* Code for COMP10002 Assignment 1, March 2017.
   Jeremy Tee Yee Lun, teej1@student.unimelb.edu.au
   Algorithm are fun!
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIV "==========" /* stage header */
/* stage numbers */
#define STAGE_NUM_ONE 1 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5

#define READ_OK 1 /* reading point succeeded */
#define READ_FAILED 0 /* reading point failed */

#define MAX_NUM_POINTS 99 /* maximum number of points */
#define MAX_NUM_DIMENSIONS 10 /* maximum number of dimensions */

typedef double point_t[MAX_NUM_DIMENSIONS];

/* function prototypes */
void stage_one(point_t one_point, int *num_points, int num_dimensions);
void stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums);
void stage_three(double *coordinate_sums, int num_points);
void stage_four(point_t points[], int num_points, int num_dimensions);
void stage_five(point_t points[], int num_points, int num_dimensions);

void print_stage_heading(int stage);
int read_one_point(point_t one_point, int num_dimensions);
/* add your own function prototypes here */



/* main program binds it all together */
int
main(int argc, char *argv[]) {

	/* storage for the input data */
	int num_dimensions;
	point_t points[MAX_NUM_POINTS];
	
	/* storage for statistics */
	int num_points = 0; /* number of points read in */
	double coordinate_sums[MAX_NUM_POINTS]; /* coordinate sums of the points */
	
	/* read the first line - number of dimensions */
	scanf("%d", &num_dimensions);
	
	/* stage 1 */
	stage_one(points[0], &num_points, num_dimensions);
	
	/* stage 2 */
	stage_two(points, &num_points, num_dimensions, 
		coordinate_sums);

	/* stage 3 */
	stage_three(coordinate_sums, num_points);
	
	/* stage 4 */
	stage_four(points, num_points, num_dimensions);

	/* stage 5 */
	stage_five(points, num_points, num_dimensions);
	
	/* and done! */
	
	return 0;
}

/* print out a stage heading, with a prior blank line once the stage number
   goes plus one 
*/
void 
print_stage_heading(int stage) {
	/* main job is to print the stage number passed as an argument */
	if (stage > STAGE_NUM_ONE) {
		/* separate the stages */
		printf("\n");
	}
	printf("Stage %d\n%s\n", stage, DIV);
}

/* read the coordinates of one point, store them in one_point
*/
int 
read_one_point(point_t one_point, int num_dimensions) {
	int i = 0;
	
	/* keep reading until num_dimensions numbers have been obtained */
	while (i < num_dimensions) {
		if (scanf("%lf", one_point+i) != 1) {
			return READ_FAILED;
		}
		i++;
	}
	
	return READ_OK;
}

/* stage 1 - read in and print one point
*/
void 
stage_one(point_t one_point, int *num_points, int num_dimensions) {
	/* print stage heading for stage 1 */
	print_stage_heading(STAGE_NUM_ONE);
	
	/* add your code here for stage 1 */
	int i;
	read_one_point(one_point, num_dimensions);
	
	/* print first point */
	printf("Point %02d: <", ++(*num_points));
	for (i =0; i< num_dimensions; i++)
	{
		/* print elements based on the format given */
		printf("%.2f", one_point[i]);
		if (i == num_dimensions-1)
		{
			printf(">\n");
		}
		else
		{
			printf(", ");
		}
	}
}

/* stage 2 - read in the rest of the points and visualise them
*/

void 
stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums) {
	/* print stage heading for stage 2 */
	print_stage_heading(STAGE_NUM_TWO);
	
	point_t one_point;
	/* add your code here for stage 2 */
	int i;
	
	/* read in all the remaining points and increment num_points */
	while (read_one_point(one_point, num_dimensions)) 
	{
		for(i = 0; i < num_dimensions; i++)
		{
			points[*num_points][i] = one_point[i];
		}
		(*num_points)++;
	}
	
	int count1, count2;
	for (count1 = 0; count1 < *num_points; count1++)
	{	
		/* set initial value for coordinate_sum = 0 */
		*(coordinate_sums+count1) = 0.0;
		for(i = 0; i < num_dimensions; i++)
		{
			/* increment *coordinate_sums for every element in a point */
			*(coordinate_sums+count1) += points[count1][i];
		}
		
		/* print the statement */
		printf("Point %02d, sum of coordinates (/100): %5.2f ", count1 + 1,
			*(coordinate_sums + count1)/100);
		printf("|");
		
		/* print + and - */
		for (count2 = 1; count2 < (*(coordinate_sums+count1)/100) + 1; count2++)
		{
			if(count2 % 10 != 0)
			{
				printf("-");
			}
			else
			{
				printf("+");
			}
		}
		
		printf("\n");
		
	}
}

/* stage 3 - print statistics
*/
void 
stage_three(double *coordinate_sums, int num_points) {
	/* print stage heading for stage 3 */
	print_stage_heading(STAGE_NUM_THREE);
	
	/* add your code here for stage 3 */
	int i = 0, largest_point = 0;
	double max = 0;
	printf("Total: %d points\n",num_points);
	
	/* get max values by comparing */
	for (i = 0; i < num_points; i++)
	{	
		/* if a max value is obtained
		   - replace max and largest_point */
		if(*(coordinate_sums + i) > max)
		{
			max = *(coordinate_sums+i);
			largest_point = i;
		}
	}
	
	printf("Point of largest sum of coordinates: %02d\n",largest_point+1);
	printf("Largest sum of coordinates: %.2f\n", max);

}

/* stage 4 - find and print the skyline points
*/
void 
stage_four(point_t points[], int num_points, int num_dimensions) {
	/* print stage heading for stage 4 */
	print_stage_heading(STAGE_NUM_FOUR);
	
	/* add your code here for stage 4 */
	printf("Skyline points:\n");
	
	int i,j,k,a;
	
	/* Check if its a skyline point */
	for (i = 0; i < num_points; i++)
	{	
		/* Check for lines below of the chosen i line */
		int isSkyline = 1;
		for (j = i + 1; j < num_points; j++)
		{
			int count = 0;
			for (k = 0; k < num_dimensions; k++)
			{
				/* for every element dominated by j count++ */
				if (points[i][k] <= points[j][k])
				{
					count++;
				}
			}
			
			/* set 0 as not a skyline point and break from loop */
			if (count == num_dimensions)
			{
				isSkyline = 0;
				break;
			}
		}
		
		/* Can be skipped if its already not a skyline point
		Check for lines above of the chosen i line */
		if (isSkyline != 0)
		{
			for (j = i - 1; j >= 0; j--)
			{
				int count = 0;
				for (k = 0; k < num_dimensions; k++)
				{	
					/* for every element dominated by j count++ */
					if (points[i][k] <= points[j][k])
					{	
						count++;
					}
				}
				
				/* 	set 0 as not a skyline point and break from loop */
				if (count == num_dimensions)
				{
					isSkyline = 0;
					break;
				}
			}
		}
		
		/* print only if its a skyline point */
		if (isSkyline != 0)
		{
			printf("Point %02d: <",i+1);
			for (a = 0; a < num_dimensions; a++)
			{
				printf("%.2f",points[i][a]);
				if (a == num_dimensions - 1)
				{ 
					printf(">\n");
				}
				
				else
				{
					printf(", ");
				}
			}
		}
	} 
}

/* stage 5 - sort and print the skyline points by the number of points 
   they dominate
*/
void 
stage_five(point_t points[], int num_points, int num_dimensions) {
	/* print stage heading for stage 5 */
	print_stage_heading(STAGE_NUM_FIVE);
	
	/* add your code here for stage 5 */

	
	int i,j,k;
	int isSkyline[num_points][2], numOfPointsDom[num_points];
	
	/* 
	Initialize of Array 
	Assume all points is a skyline point - 1
	Number of points dominated - 0
	*/
	
	for (i = 0; i < num_points; i++)
	{
		isSkyline[i][0] = i;
		isSkyline[i][1] = 1;
		numOfPointsDom[i] = 0;
	}
	
	/* Check if its a skyline points*/
	for (i = 0; i < num_points; i++)
	{	
		/* Check for lines below of the chosen i line */
		for (j = i + 1; j < num_points; j++)
		{
			int count = 0;
			for (k = 0; k < num_dimensions; k++)
			{
				if (points[i][k] <= points[j][k])
				{
					count++;
				}
			}
			
		/* set 0 as not skyline and increment for 
		    point j as it dominates point i  */
			if (count == num_dimensions)
			{	
				isSkyline[i][1] = 0;
				numOfPointsDom[j] += 1;
			}
		}
		
		/* Check for lines above of the chosen i line */
		for (j = i - 1; j >= 0; j--)
		{
			int count = 0;
			for (k = 0; k < num_dimensions; k++)
			{
				if (points[i][k] <= points[j][k])
				{
					count++;
				}
			}
			
		    /* set 0 as not skyline and increment for 
		    point j as it dominates point i */
			if (count == num_dimensions)
			{	
				isSkyline[i][1] = 0;
				numOfPointsDom[j] += 1;
			}
		}
	}
	
	/* Sorting the Array based on the number of times dominated */
	int tmp1,tmp2,tmp3;
	
	for (i = 0; i < num_points; i++)
	{	
		for(j = i+1; j < num_points; j++)
		{
			/* Case if the number of times dominated is different */
			if (numOfPointsDom[i] < numOfPointsDom[j])
			{
				tmp1 = isSkyline[i][0];
				isSkyline[i][0] = isSkyline[j][0];
				isSkyline[j][0] = tmp1;
				
				tmp2 = isSkyline[i][1];
				isSkyline[i][1] = isSkyline[j][1];
				isSkyline[j][1] = tmp2;
			
				tmp3 = numOfPointsDom[i];
				numOfPointsDom[i] = numOfPointsDom[j];
				numOfPointsDom[j] = tmp3;
			}
			
			/* Case if the number of times dominated is equal 
			and is a skyline point */
			if (numOfPointsDom[i] == numOfPointsDom[j] && 
				isSkyline[i][0] > isSkyline[j][0] && isSkyline[i][1] == 1 &&
				isSkyline[j][1] == 1)
			{
				tmp1 = isSkyline[j][0];
				isSkyline[j][0] = isSkyline[i][0];
				isSkyline[i][0] = tmp1;
				
				tmp2 = numOfPointsDom[j];
				numOfPointsDom[j] = numOfPointsDom[i];
				numOfPointsDom[i] = tmp2;
			}		
		}
	}
	
	printf("Sorted skyline points:\n");
	
	int a = 0;
	for (i = 0; i < num_points; i++)
	{
		/* print only if its a skyline point same as stage 4 */
		if (isSkyline[i][1] == 1)
		{
			printf("Point %02d: <",(isSkyline[i][0]+1));
			for (a = 0; a < num_dimensions; a++)
			{
				printf("%.2f",points[isSkyline[i][0]][a]);
				if (a == num_dimensions - 1)
				{ 
					printf(">\n");
					printf("Number of points dominated: %d\n",numOfPointsDom[i]);
				}
				
				else
				{
					printf(", ");
				}
			}
		}
	}
}
