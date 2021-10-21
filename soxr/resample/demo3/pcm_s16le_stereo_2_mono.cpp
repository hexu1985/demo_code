#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

void strero_2_mono(const int16_t* src_audio, int samples_per_channel, int16_t* dst_audio) {
  for (int i = 0; i < samples_per_channel; i++) {
    dst_audio[i] = static_cast<int16_t>(((int32_t)src_audio[2*i] + (int32_t) src_audio[2*i+1]) >> 1);
  }
}

void pcm_s16le_strero_2_mono(const uint8_t* data, size_t data_size, std::vector<uint8_t>& output) {
  int samples_per_channel = data_size / sizeof (int16_t) / 2;   // 2 is 2 channel
  output.clear();
  output.resize(samples_per_channel*sizeof(int16_t));
  strero_2_mono((const int16_t*)data, samples_per_channel, (int16_t*)output.data());
} 

std::tuple<char *, size_t> read_binary_file(const std::string& path);
void write_binary_file(const std::string& path, char *data, size_t len);

int main()
{
    std::string in_pcm_file = "test_48k_s16le_2c_pcm.raw";
    std::string out_pcm_file = "test_48k_s16le_1c_pcm.raw";

    char *in_buffer = nullptr;
    size_t in_buffer_size = 0;
    std::tie(in_buffer, in_buffer_size) = read_binary_file(in_pcm_file);

    if (in_buffer == NULL || in_buffer_size == 0) {
        std::cout << "read_binary_file failed!\n";
        exit(1);
    }

    std::vector<uint8_t> out_buffer;
    pcm_s16le_strero_2_mono((uint8_t *)in_buffer, in_buffer_size, out_buffer);

    write_binary_file(out_pcm_file, (char *) out_buffer.data(), out_buffer.size());

    return 0;
}

std::tuple<char *, size_t> read_binary_file(const std::string& path)
{
    std::ifstream is (path, std::ifstream::binary);
    if (!is) {
        std::cout << "open file " << path << " failed!\n";
        return std::make_pair((char *) nullptr, 0);
    }

    // get length of file:
    is.seekg (0, is.end);
    size_t length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... \n";
    // read data as a block:
    is.read (buffer,length);

    if (is)
        std::cout << "all characters read successfully. \n";
    else
        std::cout << "error: only " << is.gcount() << " could be read\n";
    is.close();

    // ...buffer contains the entire file...
    return std::make_pair(buffer, length);
}

void write_binary_file(const std::string& path, char *data, size_t len)
{
    std::ofstream outfile (path, std::ofstream::binary | std::ofstream::trunc);
    if (!outfile) {
        std::cout << "open file " << path << " for write failed!\n";
        exit(1);
    }

    outfile.write(data, len);
}
