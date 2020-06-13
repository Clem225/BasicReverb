#pragma once

#include <fstream> //std::ifstream
#include <string>
#include <vector>

#include "WAV_Header.h"


class WAV_file
{
	wav_header header;
	std::vector<short> lData;
	std::vector<short> rData;

public:
	//Constructors
	WAV_file(std::ifstream &ifs);
	WAV_file(std::string file_path);

	//Displaying infos
	const std::string display_header() const;
};
