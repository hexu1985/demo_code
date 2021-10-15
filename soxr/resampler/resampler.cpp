#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <soxr.h>

std::tuple<char *, int> read_binary_file(const std::string& path);

int main(int argc, char *argv[])
{
    std::string in_pcm_file = "test_48k_pcm.raw";
    int src_sample_rate = 48000;
    int dst_sample_rate = 16000;
    unsigned src_channels = 1;
    soxr_error_t error;

    char *in_buffer = nullptr;
    int in_length = 0;
    std::tie(in_buffer, in_length) = read_binary_file(in_pcm_file);

    /* When creating a var-rate resampler, q_spec must be set as follows: */
    soxr_quality_spec_t q_spec = soxr_quality_spec(SOXR_HQ, SOXR_VR);

    /* The ratio of the given input rate and output rates must equate to the
     * maximum I/O ratio that will be used: */
    soxr_t soxr = soxr_create((double) src_sample_rate, (double) dst_sample_rate, src_channels, &error, NULL, &q_spec, NULL); 

    return 0;
}

std::tuple<char *, int> read_binary_file(const std::string& path)
{
    std::ifstream is (path, std::ifstream::binary);
    if (!is) {
        std::cout << "open file " << path << " failed!\n";
        return std::make_pair((char *) nullptr, 0);
    }

    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
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
