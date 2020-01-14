/**
 * BOJ 1157
 * Print most frequently shown character in a given word.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Capitals: 1 << 5 bit off.
 * A: 0100 0001
 * Z: 0101 1010
 *
 * Non-capitals: 1 << 5 bit on.
 * a: 0110 0001
 * z: 0111 1010
 */
#define ASCII_CHAR_UPPER(ch) (ch & ~(1 << 5))

char word[1000000];
void most_frequent_char(char *string);

int main(int argc, char *argv[]) {
	fread(word, 1, 1000000, stdin);
	most_frequent_char(word);
	return 0;
}

void most_frequent_char(char *string) {
	size_t counts[26] = {0,};
	size_t string_len = strlen(string);
	
	// Count.
	for (size_t i = 0; i < string_len; ++i) {
		counts[ASCII_CHAR_UPPER(string[i]) - 'A'] += 1;
	}

	size_t count_max = 0;
	char most_frequent = '\0';
	char duplicated = '\0';

	// Get max.
	// No duplications allowed.
	for (size_t i = 0; i < 26; ++i) {
		if (counts[i] == count_max) {
			duplicated = most_frequent = i + 'A';
		}
		else if (counts[i] > count_max) {
			count_max = counts[i];
			most_frequent = i + 'A';
		}
	}

	// If most frequent character is shown for over than once,
	// print '?'.
	if (most_frequent == duplicated) {
		printf("?\n");
	} else {
		printf("%c\n", most_frequent);
	}
}
