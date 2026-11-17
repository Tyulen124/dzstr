#define NOMINMAX


#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
bool searchWordWithReg(std::wstring& str, std::wstring& word)
{
	if (word.empty())
	{
		std::wcout << L"Строка пустая";
		return false;
		
	}
	return str.find(word) != std::wstring::npos;

}
bool searchWord( std::wstring& str, std::wstring& word)
{
	if (word.empty())
	{
		std::wcout << L"Строка пустая";
		return false;
		
	}

	wchar_t letS;
	wchar_t letW;
	for (size_t i = 0; i < word.size(); i++)
	{
	
		 letW = word[i];
		
			if (letW >= L'\u0430' && letW <= L'\u044F')
				letW -= 32;
			if (letW >= L'a' && letW <= L'z')
			{
				letW -= 32;
			}
			
		
		word[i] = letW;

	}
	for (size_t i = 0; i < str.size(); i++)
	{
		 letS = str[i];
		
			if (letS >= L'\u0430' && letS <= L'\u044F')
				letS -= 32;
			if (letS >= L'a' && letS <= L'z')
			{
				letS -= 32;
			}

		
		str[i] = letS;

	}
	return  str.find(word) != std::wstring::npos;
}
void Getline(std::wstring& str)
{
	std::getline(std::wcin, str, L'\n');
}
bool isRusLetter(wchar_t c)
{
	 
	
		return(c >= L'\u0430' && c <= L'\u044F') ||  
			(c >= L'\u0410' && c <= L'\u042F'); // просто русские буквы писать не сработало :( utf 8 поставил в свойствах файла
	
}
bool isEngLetter(wchar_t c)
{


	return (c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z');


}

int main()
{

	
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	
	bool NewWord = true;
	
	std::wstring text;
	wchar_t last;
	Getline(text);
	if (text.empty())
	{
		std::wcout << L"Строка пустая";
		return 0;
	}

	for (size_t i = 0; i < text.size(); i++)
	{
		
		wchar_t let = text[i];

		bool isLetter = (isRusLetter(let)) || (isEngLetter(let));
		if (let == L' ' || !isLetter)
		{
			NewWord = true;
			continue;
		}
		
		if (NewWord == true)
		{
			if (isRusLetter(let))
			{
				if (let >= L'\u0430' && let <= L'\u044F')
				let -= 32;
				
			}
			else if (isEngLetter(let))
			{
				if (let >= L'a' && let <= L'z')
				{
					let -= 32;
				}
			}
				

			NewWord = false;
		}
		else
		{
			if (isRusLetter(let))
			{
				if ((let >= L'\u0410' && let <= L'\u042F'))
				{ 
					let += 32;
				}
				
			}
			if (isEngLetter(let))
			{
				if (let >= L'A' && let <= L'Z')
				{
					let += 32;
				}
				
			}
		}
		last = text[text.size() - 1];
		if (last == '.')
		{
			last = ' ';
		}
		else
		{
			last = '.';
		}

		text[i] = let;
		
	}
	
	
	
	std::wcout << text + last;
	
















}