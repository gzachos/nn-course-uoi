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
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"

#define DATASET_FILEPATH        "./datasets/dataset.csv"
#define POW2(x)                 (powf((x),2))
#define IN_CIRCLE(x1,x2)        ((POW2(x1)+POW2(x2)) <= 0.3)

typedef enum area_e {C1, S1, S2, S3, S4, S5} area_t;

/* Function prototypes */
int generate_patterns_in_area(FILE *outfile, area_t aid);
int generate_dataset(char *filepath);

/* Global Data */
pattern_t set[DATASET_SIZE];


int main(void)
{
	srand(time(NULL));

	printf("Generating data set... ");
	fflush(stdout);
	if (generate_dataset(DATASET_FILEPATH) == 0)
		printf("Success\n");

	return 0;
}


int generate_dataset(char *filepath)
{
	int aid, ec = 0;
	FILE *outfile;

	if (!(outfile = fopen(filepath, "w")))
	{
		fprintf(stderr, "failed!\nError writing %s: %s\n",
				filepath, strerror(errno));
		return errno;
	}

	for (aid = C1; aid <= S5; aid++)
		ec += generate_patterns_in_area(outfile, aid);

	fclose(outfile);

	return ec;
}


int generate_patterns_in_area(FILE *outfile, area_t aid)
{
	int i;
	float x1 = 0.0, x2 = 0.0;

	if (!outfile)
		return 1;

	for (i = 0; i < PATTERNS_PER_AREA; i++)
	{
		switch (aid)
		{
			case C1:
				do
				{
					x1 = RAND_NUM(0.0, 0.3);
					x2 = RAND_NUM(0.0, 0.3);
				}
				while (!IN_CIRCLE(x1,x2));
				break;
			case S1:
				x1 = RAND_NUM(-1.1, -0.5);
				x2 = RAND_NUM(0.5, 1.1);
				break;
			case S2:
				x1 = RAND_NUM(-1.1, -0.5);
				x2 = RAND_NUM(-1.1, -0.5);
				break;
			case S3:
				x1 = RAND_NUM(0.5, 1.1);
				x2 = RAND_NUM(-1.1, -0.5);
				break;
			case S4:
				x1 = RAND_NUM(0.5, 1.1);
				x2 = RAND_NUM(0.5, 1.1);
				break;
			case S5:
				x1 = RAND_NUM(-1.0, 1.0);
				x2 = RAND_NUM(-1.0, 1.0);
				break;
		}

		fprintf(outfile, "%+f,%+f\n", x1, x2);
	}

	return 0;
}

