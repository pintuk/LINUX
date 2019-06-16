#include <stdio.h>
#include <string.h>
#include <ctype.h>


char *read_word(char *sentence, int len)
{
	int i=0;
	for(i=0; i<len; i++) {
		char word[100];
		int j=0;
		memset(word, 0, sizeof(word));
		while(ptr[i] != ' ') {
			word[j] = ptr[i];
			j++;
			i++;
			if(i >= len) break;
		}
		word[j] = '\0';
	}
}

int main()
{
	char str[1024];
	int i;
	int len=0;
	char *ptr;

	len = sizeof(str);
	memset(str, 0, sizeof(str));
	printf("Enter the sentence: \n");
	fgets(str, sizeof(str), stdin);
	len = strlen(str);
	ptr = str;
	i=0;

	printf("Length: %d\n", len);
	

	return 0;
}

