#include <stdio.h>

#define TABSTOP 8
#define MAXLINE 1000

void entab(char dest[], char src[]);
int nexttab(int current);
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
	int i, j;
	int current, target, next;

	i = j = 0;
	while ((c = src[i++]) != '\0') {
		if (c == ' ') {
			current = i - 1;
			while ((c = src[i++]) == ' ')
				;
			target = i - 1;

			while (current < target) {
				while ((next = nexttab(current)) < target) {
					dest[j++] = '\t';
					current = next;
				}
				dest[j++] = ' ';
				current++;
			}
		}

		dest[j++] = c;
	}

	dest[j] = '\0';
}

/* calculate column number of next tabstop at or after current column */
int nexttab(int current)
{
	return current + (TABSTOP - (current % TABSTOP));
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
