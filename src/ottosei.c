#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[]) {
	
	int opterr = 0;

	int opt;
	char str[100];
	char h, m, l, g;
	h = m = l = g = 0;

	char MP3_1[50], MP3_2[50], JPEG[50];

	FILE *fp;

	system("find /usr/share/ -name \"ottosei1.mp3\" 1> /tmp/ottosei.tmp 2> /dev/null");
	system("find /usr/share/ -name \"ottosei2.mp3\" 1>> /tmp/ottosei.tmp 2> /dev/null");
	system("find /usr/share/ -name \"ottosei.jpeg\" 1>> /tmp/ottosei.tmp 2> /dev/null");

	if((fp = fopen("/tmp/ottosei.tmp", "r")) == NULL) {
		printf("file input error\n\n");
		return;
	}

	fgets(MP3_1, 50 ,fp);
	fgets(MP3_2, 50 ,fp);
	fgets(JPEG, 50 ,fp);

	fclose(fp);
	remove("/tmp/ottosei.tmp");

	MP3_1[strlen(MP3_1)-1] = '\0';
	MP3_2[strlen(MP3_2)-1] = '\0';
	JPEG[strlen(JPEG)-1]   = '\0';

	while((opt = getopt(argc, argv, "hmlg")) != -1) {
		switch(opt) {
		case 'h' :
			h = 1;
			break;
		case 'm' :
			m = 1;
			break;
		case 'l' :
			l = 1;
			break;
		case 'g' :
			g = 1;
			break;
		default :
			h = 1;
		}
	}

	if(h || (m && l)) {
		printf ("ottosei: ottosei [OPTION]...\n"
			"Show an \"ottosei\" and play call of it.\n"
			"\"Ottosei\" is a Japanese words which means a fur seal.\n\n"
			"Options :\n"
			"	-m : Mute sound\n"
			"	-l : Play with louder sound\n"
			"	-g : Show an ottosei in GUI\n"
			"	-h : Help\n\n");

		return;
	}

	if(g)  
		sprintf(str, "%s%s &", "display ", JPEG);
	else 
		sprintf(str, "%s%s", "jp2a ", JPEG);

	system(str);

	if(m) 
		str[0] = '\0';
	else if(l)
		sprintf(str, "%s%s", "mpg123 -q ", MP3_2);
	else
		sprintf(str, "%s%s", "mpg123 -q ", MP3_1);

	system(str);
}
