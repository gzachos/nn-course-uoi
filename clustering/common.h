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


#ifndef __COMMON_H
#define __COMMON_H

#define DATASET_SIZE       600
#define PATTERNS_PER_AREA  100
#define RAND_ONE           (rand() / ((float) RAND_MAX))
#define RAND_NUM(l,u)      (((u)-(l))*RAND_ONE + (l))

typedef struct pattern_s {
	float x1;
	float x2;
	short int ci; // Centroid/Cluster index
} pattern_t;

typedef struct centroid_s {
	float x1;
	float x2;
} centroid_t;

#endif
