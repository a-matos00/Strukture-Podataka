#pragma once


char* createBuffer(FILE* fp)
{
	char* buffer;

	int buffer_size = bufferSize(fp);

	buffer = (char*)calloc(buffer_size + 10, sizeof(char));	//ALOKACIJA BUFFERA(doda se par znakova viska za svaki slucaj
	fread(buffer, buffer_size, 1, fp);	//sadrzaj datoteke se upisuje u buffer
	*(buffer + buffer_size) = ' ';	//razmak iza zadnjeg znaka postfix izraza radi nekih sitnih pikanterija

	fclose(fp);

	//printf("Ispis buffera datoteke %s\n", buffer);	za debug

	return buffer;
}

int bufferSize(FILE* fp) {
	int buffer_size = 0;

	fseek(fp, 0, SEEK_END);
	buffer_size = ftell(fp);

	//printf("Velicina buffera je %d znakova\n", buffer_size);	za debuggiranje

	rewind(fp);

	return buffer_size;
}
