#include "WAV_file.h"

WAV_file::WAV_file(std::ifstream &ifs)
{
	ifs.read((char*)&header, sizeof(header));
}

WAV_file::WAV_file(std::string file_path)
{
	std::ifstream ifs(file_path);
	//Populating the header
	ifs.read((char*)&header, sizeof(header));
	//Retrieving the data
	do {
		short buf[2];
		ifs.read((char*)buf, sizeof(buf[0]) * 2);
		lData.push_back(buf[0]);
		rData.push_back(buf[1]);
	} while (!ifs.eof());

	ifs.close();
}

const std::string WAV_file::display_header() const
{
	std::string str = "******HEADER START*******\n";
	str = str + "RIFF HEADER\n";
	std::string riff_header(header.riff_header, sizeof(header.riff_header));
	str = str + "Chunk ID =\t" + riff_header + "\n";
	str = str + "Chunk Size =\t" + std::to_string(header.wav_size) + "\n";
	std::string wave_header(header.wave_header, sizeof(header.wave_header));
	str = str + "Format =\t" + wave_header + "\n\n";
	str = str + "FORMAT HEADER\n";
	std::string fmt_header(header.fmt_header, sizeof(header.fmt_header));
	str = str + "Subchunk1ID =\t" + fmt_header + "\n";
	str = str + "Subchunk1Size =\t" + std::to_string(header.fmt_chunk_size) + " (16 for PCM)\n";
	str = str + "AudioFormat =\t" + std::to_string(header.audio_format) + " (1 for PCM)\n";
	str = str + "NumChannels =\t" + std::to_string(header.num_channels) + "\n";
	str = str + "SampleRate =\t" + std::to_string(header.sample_rate) + "\n";
	str = str + "ByteRate =\t" + std::to_string(header.byte_rate) + "\n";
	str = str + "BlockAlign =\t" + std::to_string(header.sample_alignment) + "\n";
	str = str + "BitsPerSample =\t" + std::to_string(header.bit_depth)+ "\n\n";
	str = str + "DATA\n";
	std::string data_header(header.data_header, sizeof(header.data_header));
	str = str + "SubChunk2ID =\t" + data_header + "\n";
	str = str + "SubChunk2Size =\t" + std::to_string(header.data_bytes) + "\n";
	str = str + "*****END OF HEADER*****\n";

	return str;
}