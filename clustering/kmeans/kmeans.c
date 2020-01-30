/*
 * +-----------------------------------------------------------------------+
 * |               Copyright (C) 2020 George Z. Zachos                     |
 * +-----------------------------------------------------------------------+
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Contact Information:
 * Name: George Z. Zachos
 * Email: gzzachos <at> gmail.com
 */


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../common.h"
#include "conf.h"

#if 0
	#define WRITE_CLUSTER_DATA
#else
	#undef WRITE_CLUSTER_DATA
#endif

#define DATASET_FILEPATH	"../datasets/dataset.csv"
#define BUFFER_SIZE		64
#define POW2(x)			(powf((x),2))
#define IN_CIRCLE_1(p)		((POW2((p).x1-1)+POW2((p).x2-1)) <= 0.49)
#define IN_CIRCLE_2(p)		((POW2((p).x1+1)+POW2((p).x2+1)) <= 0.49)
#define IN_CIRCLE_3(p)		((POW2((p).x1+1)+POW2((p).x2-1)) <= 0.49)
#define IN_CIRCLE_4(p)		((POW2((p).x1-1)+POW2((p).x2+1)) <= 0.49)


typedef enum set_type_e {TRAIN, TEST} set_type_t;


/* Function prototypes */
void   load_all_datasets();
void   load_dataset(char *filepath, pattern_t *set, int set_size);
void   kmeans();
void   init_centroids();
void   assign_patterns_to_clusters();
void   calc_new_cetroid(centroid_t *new_centroid, int ci);
void   print_centroids();
float  distance(pattern_t p1, centroid_t p2);
float  calc_clustering_error();
int    write_plot_data();
int    write_centroids();
#ifdef WRITE_CLUSTER_DATA
int    write_cluster_data(int ci);
#endif

/* Global data */
pattern_t dataset[DATASET_SIZE];
centroid_t centroids[M];


int main(void)
{
	srand(time(NULL));

	printf("Loading datasets... ");
	fflush(stdout);
	load_dataset(DATASET_FILEPATH, dataset, DATASET_SIZE);
	printf("Success\n");

	kmeans();

	printf("Preparing data for plotting... ");
	fflush(stdout);
	printf("%s\n", (write_plot_data() == 0) ? "Success" : "failed!");

	return 0;
}


void kmeans()
{
	int updated_centroids, ci;
	centroid_t new_centroid;

	init_centroids();

	do
	{
		assign_patterns_to_clusters();
		// Calculate new centroids
		for (ci = 0, updated_centroids = 0; ci < M; ci++)
		{
			calc_new_cetroid(&new_centroid, ci);
			if (new_centroid.x1 != centroids[ci].x1 ||	
					new_centroid.x2 != centroids[ci].x2)
			{
				updated_centroids++;
				centroids[ci] = new_centroid;
			}
		}
	}
	while (updated_centroids != 0);
	
	print_centroids();
	printf("Clustering error: %f\n", calc_clustering_error());
}


void print_centroids()
{
	int ci;

	printf("Centroids:\n");
	for (ci = 0; ci < M; ci++)
		printf("\t%d: (%+f,%+f)\n", ci, centroids[ci].x1, centroids[ci].x2);
}


void init_centroids()
{
	int i, j, pi, found;
	for (i = 0; i < M; i++)
	{
		do
		{
			pi = RAND_NUM(0,DATASET_SIZE-1);
			for (j = 0, found = 0; j < i; j++)
			{
				if (centroids[j].x1 == dataset[pi].x1 && 
						centroids[j].x2 == dataset[pi].x2)
				{
					found = 1;
				}
			}
		}
		while (found);

		centroids[i].x1 = dataset[pi].x1;
		centroids[i].x2 = dataset[pi].x2;
	}
}


void assign_patterns_to_clusters()
{
	int i, j, min_ci;
	float dist, min_dist;

	for (i = 0; i < DATASET_SIZE; i++)
	{
		min_dist = distance(dataset[i], centroids[0]);
		min_ci = 0;
		for (j = 1; j < M; j++)
		{
			
			if ((dist = distance(dataset[i], centroids[j])) < min_dist)
			{
				min_dist = dist;
				min_ci = j;
			}
		}
		dataset[i].ci = min_ci;
	}
}


void calc_new_cetroid(centroid_t *new_centroid, int ci)
{
	int i, size = 0;
	centroid_t c = {0, 0};

	for (i = 0; i < DATASET_SIZE; i++)
	{
		if (dataset[i].ci == ci)
		{
			size++;
			c.x1 += dataset[i].x1;
			c.x2 += dataset[i].x2;
		}
	}
	c.x1 /= size;
	c.x2 /= size;

	*new_centroid = c;
}


/* Squared Euclidean Distance */
float distance(pattern_t p1, centroid_t p2)
{
	return (powf(p1.x1 - p2.x1, 2) + powf(p1.x2 - p2.x2, 2));
}


float calc_clustering_error()
{
	int i;
	float sum = 0.0;

	for (i = 0; i < DATASET_SIZE; i++)
		sum += distance(dataset[i], centroids[dataset[i].ci]);

	return sum;
}


void load_dataset(char *filepath, pattern_t *set, int set_size)
{
	int i;
	FILE *infile;
	float x1, x2;

	if (!(infile = fopen(filepath, "r")))
	{
		fprintf(stderr, "failed!\nError reading %s: %s\n",
				filepath, strerror(errno));
		exit(errno);
	}

        for (i = 0; i < set_size; i++)
	{
		if (fscanf(infile, "%f,%f\n", &x1, &x2) != 2)
		{
			fprintf(stderr, "failed!\nError loading dataset from %s: "
					"reached unexpected EOF\n", filepath);
			exit(EXIT_FAILURE);
		}
		set[i].x1 = x1;
		set[i].x2 = x2;
	}

	fclose(infile);
}


int write_plot_data()
{
	int ec = 0;
#ifdef WRITE_CLUSTER_DATA
	int ci;

	for (ci = 0; ci < M && ec == 0; ci++)
		ec += write_cluster_data(ci);
#endif
	ec += write_centroids();

	return ec;
}


int write_centroids()
{
	FILE *fp;
	char  filepath[] = "./plot_data/centroids.dat";
	int   i;

	if (!(fp = fopen(filepath, "w")))
	{
		fprintf(stderr, "Error writing %s: %s\n", filepath, strerror(errno));
		return errno;
	}

	for (i = 0; i < M; i++)
		fprintf(fp, "%+f\t%+f\n", centroids[i].x1, centroids[i].x2);
	fclose(fp);

	return 0;
}


#ifdef WRITE_CLUSTER_DATA
int write_cluster_data(int ci)
{
	FILE *fp;
	char  filepath[BUFFER_SIZE];
	int   i;

	snprintf(filepath, BUFFER_SIZE, "./plot_data/cluster_c%d.dat", (ci + 1));
	if (!(fp = fopen(filepath, "w")))
	{
		fprintf(stderr, "Error writing %s: %s\n", filepath, strerror(errno));
		return errno;
	}

	for (i = 0; i < DATASET_SIZE; i++)
		if (dataset[i].ci == ci)
			fprintf(fp, "%+f\t%+f\n", dataset[i].x1, dataset[i].x2);
	fclose(fp);

	return 0;
}
#endif
