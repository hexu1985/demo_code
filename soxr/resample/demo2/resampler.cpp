/**
 * @file resampler.cpp
 * @brief 利用soxr处理重采样的音频, 
 *        代码里写死了, 输入的音频文件为48k s16le pcm数据,
 *        输出16k s16le pcm数据
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2021-10-15
 */
#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <soxr.h>

std::tuple<char *, size_t> read_binary_file(const std::string& path);
void write_binary_file(const std::string& path, char *data, size_t len);

int main(int argc, char *argv[])
{
    std::string in_pcm_file = "test_48k_pcm.raw";
    std::string out_pcm_file = "test_16k_pcm.raw";
    int src_sample_rate = 48000;
    int dst_sample_rate = 16000;
    unsigned src_channels = 2;
    soxr_error_t error;

    char *in_buffer = nullptr;
    size_t in_buffer_size = 0;
    std::tie(in_buffer, in_buffer_size) = read_binary_file(in_pcm_file);

    if (in_buffer == NULL || in_buffer_size == 0) {
        std::cout << "read_binary_file failed!\n";
        exit(1);
    }

    std::cout << "in_buffer_size: " << in_buffer_size << '\n';

    size_t out_buffer_size = in_buffer_size / 3;
    char *out_buffer = new char [out_buffer_size];
    memset(out_buffer, 0x00, out_buffer_size);

    /* for pcm_s16le */
    soxr_io_spec_t io_spec = soxr_io_spec(SOXR_INT16_I, SOXR_INT16_I);

    /* When creating a var-rate resampler, q_spec must be set as follows: */
    soxr_quality_spec_t q_spec = soxr_quality_spec(SOXR_HQ, SOXR_VR);

    /* The ratio of the given input rate and output rates must equate to the
     * maximum I/O ratio that will be used: */
    soxr_t soxr = soxr_create((double) src_sample_rate, (double) dst_sample_rate, src_channels, &error, &io_spec, &q_spec, NULL); 

    if (error != 0) {
        std::cout << "soxr_create failed: " << error << '\n';
        exit(1);
    }

    int data_size_bytes = sizeof (int16_t) * src_channels;
    size_t total_idone = 0;
    size_t total_odone = 0;
    uint8_t *i_ptr = (uint8_t *) in_buffer;
    uint8_t *o_ptr = (uint8_t *) out_buffer;
    size_t in_num_samples = in_buffer_size / data_size_bytes;
    size_t out_num_samples = out_buffer_size / data_size_bytes;
    size_t ilen = in_num_samples;
    size_t olen = out_num_samples;
    std::cout << "in_num_samples: " << in_num_samples << '\n';
    std::cout << "out_num_samples: " << out_num_samples << '\n';
    do {
        std::cout << "soxr_process: " << std::endl;
        size_t idone, odone;
        error = soxr_process(soxr, i_ptr, ilen, &idone, o_ptr, olen, &odone);
        if (error != 0) {
            std::cout << "soxr_process failed: " << error << '\n';
            exit(1);
        }
        i_ptr += idone*data_size_bytes;
        o_ptr += odone*data_size_bytes;
        ilen -= idone;
        olen -= odone;
        total_idone += idone;
        total_odone += odone;
    } while (total_idone < in_num_samples && total_odone < out_num_samples);

    std::cout << "total_idone: " << total_idone << '\n';
    std::cout << "total_odone: " << total_odone << '\n';

    write_binary_file(out_pcm_file, out_buffer, total_odone*data_size_bytes);

    soxr_delete(soxr);

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
