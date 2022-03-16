#include "Utility.hpp"

Utility::Utility()
{
}

Utility::~Utility()
{
}

union ChangeType
{
	int Int;
	char Char[4];
	float Float;

	unsigned int UInt;
	unsigned char UChar[4];
};

std::string Utility::UIntToXStr(unsigned int val)
{
	std::stringstream ss;
	ss << std::hex << val;

	return ss.str();
}

char* Utility::UIntToChar(unsigned int val)
{
	ChangeType Type;
	Type.UInt = val;

	return Type.Char;
}

unsigned int Utility::FloatToUInt(float val)
{
	ChangeType Type;
	Type.Float = val;

	return Type.UInt;
}

std::fstream& Utility::GetLine(std::fstream& file, int line)
{
	file.seekg(ios::beg);

	for (int i = 0; i < line - 1; ++i)
	{
		file.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}

	return file;
}

std::string Utility::FileReadLine(const char* file, int line)
{
	std::string Text;

	fstream File;
	File.open(file, ios::in | ios::out);

	if (File.is_open())
	{
		Utility().GetLine(File, line);
		File >> Text;
	}

	File.close();
	return Text;
}

std::string Utility::FileReadRandomLine(const char* file)
{
	int Count;
	int Line;
	bool CheckText;
	std::string CMP1 = "#";
	std::string CMP2 = " ";
	std::string Text;

	fstream File;
	File.open(file, ios::in | ios::out);

	if (File.is_open())
	{
		Count = std::count(std::istreambuf_iterator<char>(File), std::istreambuf_iterator<char>(), '\n');
		CheckText = true;

		while (CheckText == true)
		{
			std::srand((unsigned int)time(NULL));
			Line = 2 + (std::rand() % (Count - 2 + 1));
			Utility().GetLine(File, Line);
			File >> Text;

			if (!strstr(Text.c_str(), CMP1.c_str()) && !strstr(Text.c_str(), CMP2.c_str()))
			{
				CheckText = false;
			}
		}
	}

	File.close();
	return Text;
}

void Utility::FileWriteData(const char* file, int offset, int data)
{
	ofstream File;
	File.open(file, ios::in | ios::out | ios::binary);

	if (File.is_open())
	{
		File.seekp(offset, ios::beg);
		File.write((char*)&data, sizeof(data));
	}

	File.close();
}

void Utility::FileWriteString(const char* file, int offset, std::string text)
{
	ofstream File;
	File.open(file, ios::in | ios::out | ios::binary);

	if (File.is_open())
	{
		File.seekp(offset, ios::beg);
		File.write(text.c_str(), sizeof(text.c_str()));
	}

	File.close();
}