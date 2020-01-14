/**
 * BOJ 1924
 * Day 2007.
 */

#include <stdio.h>

#define UNCHECKED /* No parameter/return checks. */


/**********************************************
 * Declaration
 *********************************************/
enum dow {MON, TUE, WED, THU, FRI, SAT, SUN};

struct year_info {
	enum dow 		start_dow; /* What's the day in January 1st */
	int 			dates[12]; /* How many dates in a month */
};

/**
 * Return a day of week of a given date.
 */
enum dow dow(struct year_info *year, int m/*month*/, int dom/*day of month*/);

/**
 * Get a character pointer that indicates a string
 * describing a given day of week.
 */
char *strdow(enum dow day_of_week);


/**********************************************
 * Implementation
 *********************************************/
int main(int argc, char *argv[]) {
	int 			m;
	int 			dom;
	enum dow		day;
	
	struct year_info year2007 = {
		MON,
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};

	scanf("%d %d", &m, &dom);
	day = dow(&year2007, m, dom);

#ifndef UNCHECKED
	if (day == -1) {
		printf("FUCK!\n");
		return -1;
	}
#endif

	return !printf("%s\n", strdow(day));
}

enum dow dow(struct year_info *year, int m, int dom) {
#ifndef UNCHECKED
	if (!year) return -1;
	if (m < 1 || m > 12) return -1;
	if (dom < 1 || dom > 31) return -1;

	if (dom > year->dates[m]) return -1;
#endif
	
	int dates_total = 0;

	for (int i = 0; i < (m-1); ++i) {
		dates_total += year->dates[i];
	}
	
	dates_total += (dom-1) + year->start_dow;
	
	return dates_total % 7;
}

char *strdow(enum dow day_of_week) {
	static char *day_string[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

	return day_string[day_of_week];
}
