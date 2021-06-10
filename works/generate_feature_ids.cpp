#include <iostream>
#include <chrono>
#include <bitset>
#include <fstream>
#include <ostream>
#include <random>
#include <cmath>
#include <unistd.h>

using std::default_random_engine;
using std::uniform_int_distribution;
using namespace std::chrono;

#define LOCATION_BITS 15
#define CAMERA_ID_BITS 7
#define TIMESTAMP_BITS 32
#define SEQ_BITS 10

#define LOCATION_MAX (std::pow(2, LOCATION_BITS) - 1)
#define CAMERA_ID_MAX (std::pow(2, CAMERA_ID_BITS) - 1)
#define SEQ_MAX (std::pow(2, SEQ_BITS) - 1)

void ReadAndShow(const std::string &file, size_t length) {
    std::vector<int64_t> feature_ids(length, 0);
    std::ifstream id_reader(file, std::ios::binary);
    if (!id_reader.is_open()) {
        std::cerr << "open file failed\n";
        return;
    }
    for (auto &id : feature_ids) {
        id_reader.read((char *) &id, sizeof(int64_t));
        std::cout << std::hex << id << std::endl;
    }
    id_reader.close();

}

int main(int argc, char **argv) {
    static_assert(sizeof(int) == 4, "sizeof(int) != 4");

    int ch;
    int numbers = -1;
    std::string file;
    bool read_show = false;
    while ((ch = getopt(argc, argv, "n:o:vh")) != -1) {

        switch (ch) {
            case 'n':
                numbers = std::stoi(optarg);
                break;
            case 'o':
                file = (char *) (optarg);
                break;
            case 'v':
                read_show = true;
                break;
            case 'h':
                std::cout << "Usage: ./ids-gen -n[numbers] -o[file] -v\n";
                break;
            default:
                std::cerr << "Unknown Option\n";
                break;
        }
    }

    if(numbers == -1 || file.empty()){
        std::cout << "Usage: ./ids-gen -n[numbers] -o[file] -v\n";
        return -1;
    }

    int64_t timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    default_random_engine e(timestamp);
    uniform_int_distribution<int64_t> location(0, LOCATION_MAX);
    uniform_int_distribution<int64_t> camera_id(0, CAMERA_ID_MAX);
    uniform_int_distribution<int64_t> seq(0, SEQ_MAX);

    std::ofstream ids(file, std::ios::binary);
    if (!ids.good()) {
        return -1;
    }


    std::cout << "generate " << std::dec << numbers << " ids write to " << file << std::endl;
    for (int i = 0; i < numbers; ++i) {
        timestamp += 1;
        int64_t id = (location(e) << (64 - LOCATION_BITS)) |
                     (camera_id(e) << (64 - LOCATION_BITS - CAMERA_ID_BITS)) |
                     (timestamp << (64 - LOCATION_BITS - CAMERA_ID_BITS - TIMESTAMP_BITS)) |
                     (seq(e));
        ids.write((char *) &id, sizeof(int64_t));
    }

    ids.close();
    std::cout << "generate " << std::dec << numbers << " ids done\n";

    if (read_show) {
        ReadAndShow(file, numbers);
    }

    return 0;
}
