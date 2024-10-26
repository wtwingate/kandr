#include <stdio.h>

#define TABSTOP 8
#define MAXLINE 1000
#define nexttab(COL) (COL) + (TABSTOP - ((COL) % TABSTOP))

void entab(char dest[], char src[]);
int readline(char s[], int max);

int main(void)
{
	int len;
	char line[MAXLINE];
	char entab_line[MAXLINE];

	while (len = readline(line, MAXLINE)) {
		entab(entab_line, line);
		printf("%s", entab_line);
	}

	return 0;
}

/* copy src into dest while converting spaces into tabs */
void entab(char dest[], char src[])
{
	char c;
	int i = 0;
	int j = 0;
	int current = 0;
	int target = 0;
	int next = 0;

	while ((c = src[i++]) != '\0') {
		current++;
		if (c == ' ') {
			target = current + 1;
			while ((c = src[i++]) == ' ')
				target++;

			while ((next = nexttab(current)) < target) {
				dest[j++] = '\t';
				current = next + 1;
			}

			while (current < target) {
				dest[j++] = ' ';
				current++;
			}
			dest[j++] = c;
		} else if (c == '\t') {
			dest[j++] = c;
			current = nexttab(current);
		} else {
			dest[j++] = c;
		}
	}

	dest[j] = '\0';
}

/* read line from stdin into s and return len; len must be less than max */
int readline(char s[], int max)
{
	int c, i;

	i = 0;
	while (i < max-1 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}
