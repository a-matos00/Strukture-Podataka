#pragma once


char* createBuffer(FILE* fp)
{
	char* buffer;

	buffer = (char*)calloc(bufferSize(fp) + 1, sizeof(char));	//ALOKACIJA BUFFERA
	fread(buffer, bufferSize(fp), 1, fp);	//sadrzaj datoteke se upisuje u buffer

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
