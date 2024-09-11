#include "FileSplit.h"
#include <filesystem>


int main(int argv, char** args) {
	/*
	* ��ȡ����
	*/ 
	if (argv < 3) {
		printf("Usage: %s <file> <size(bit)> [count]\n", args[0]);
		return 1;
	}
	//
	char* file = args[1];
	//
	char* size = args[2];
	if (!isNumber(size)) {
		printf("Size must be a positive number\n");
		return 1;
	}
	int splitSize = atoi(size);
	// 
	int expectCount = 0;
	int hasExpect = 0;
	if (argv > 3) {
		char* expect = args[3];
		if (!isNumber(expect)) {
			printf("Expect count must be a positive number\n");
			return 1;
		}
		expectCount = atoi(expect);
		hasExpect = 1;
	}
	/*
	*	���ļ�����ȡ�ļ���С
	*/
	ifstream f(file, ios::binary | ios::ate);	// ���ļ���ָ��ָ���ļ�ĩβ
	if (!f) {
		printf("File not found\n");
		return 1;
	}
	// ��ȡ�ļ���С
	streamsize fileSize = f.tellg() * 8;		// �ļ���С bit
	f.seekg(0, ios::beg);						// ָ��ָ���ļ���ͷ
	if (fileSize <= 0) {
		printf("File is empty\n");
		return 1;
	}
	if (fileSize <= splitSize) {
		printf("File is too small\n");
		return 1;
	}
	/*
	* �ָ��ļ�
	*/ 
	printf("Start split file\n");
	int splitCount = fileSize / splitSize;
	if (fileSize % splitSize != 0) {
		splitCount++;
	}
	if (!hasExpect) {
		expectCount = splitCount;
	}
	if (splitCount < expectCount) {
		printf("Expect count is %d, but actual count is %d\n", expectCount, splitCount);
		return 1;
	}
	printf("File size: %lld\n", fileSize);
	printf("Split count: %d\n", expectCount);
	// ��ȡ�ļ��� ���������ļ���
	path filePath(file);
	path fileName = filePath.filename();
	path baseName = fileName.stem();
	path directory = filePath.parent_path();
	path newFolderPath = directory / (baseName.string() + "_split");
	if (!exists(newFolderPath)) {
		create_directory(newFolderPath);	// �����ļ���
	}
	else {
		printf("Folder already exists\n");
		return 1;
	}
	// �ָ��ļ�
	char* buffer = new char[splitSize / 8];
	for (int i = 0; i < expectCount; i++) {
		// ��ȡ�ļ�
		f.read(buffer, splitSize/8);
		int readSize = f.gcount();
		// �����ļ�
		char* newFileName = new char[256];
		sprintf(newFileName, "%s/%s_%d", newFolderPath.string().c_str(), baseName.string().c_str(), i);
		ofstream newFile(newFileName, ios::binary);
		newFile.write(buffer, readSize);
		newFile.close();
	}
	delete buffer;
	f.close();
	printf("Split file success\n");

	return 0;
}