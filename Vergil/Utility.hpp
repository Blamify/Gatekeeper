#include "Client.hpp"

class Utility
{
public:
	Utility();
	~Utility();
	std::string UIntToXStr(unsigned int val);
	char* UIntToChar(unsigned int val);
	unsigned int FloatToUInt(float val);
	std::fstream& GetLine(std::fstream& file, int line);
	std::string FileReadLine(const char* file, int line);
	std::string FileReadRandomLine(const char* file);
	void FileWriteData(const char* file, int offset, int data);
	void FileWriteString(const char* file, int offset, std::string text);
};