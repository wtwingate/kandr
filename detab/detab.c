#include <stdio.h>

#define TABSTOP 8
#define MAXLINE 1000

void detab(char dest[], char src[]);
int readline(char s[], int max);

int main(void)
{
	int linelen;
	char line[MAXLINE];
	char detab_line[MAXLINE];

	while ((linelen = readline(line, MAXLINE)) != 0) {
		detab(detab_line, line);
		printf("%s", detab_line);
	}

	return 0;
}

/* copy src into dest while converting tabs into spaces */
void detab(char dest[], char src[])
{
	char c;
	int i = 0;
	int j = 0;

	while ((c = src[i++]) != '\0') {
		/* guard against buffer overflow */
		if (j == MAXLINE - 1) {
			dest[j++] = '\n';
			break;
		}

		if (c == '\t') {
			/* tab always creates at least one space */
			do {
				dest[j++] = ' ';
			} while (j % TABSTOP != 0);
		} else {
			dest[j++] = c;
		}
	}

	dest[j] = '\0';
}

/* read one line from stdin into s and return length */
int readline(char s[], int max)
{
	int i;
	char c;

	for (i = 0; i < max - 1 && (c = getchar()) != '\n' && c != EOF; i++)
		s[i] = c;
	
	if (c == '\n')
		s[i++] = '\n';

	s[i] = '\0';

	return i;
}
