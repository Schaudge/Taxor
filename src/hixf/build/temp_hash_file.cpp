
#include "temp_hash_file.hpp"
#include <filesystem>
#include <fstream>

namespace hixf
{

void create_temp_hash_file(size_t const ixf_pos, std::vector<robin_hood::unordered_flat_set<size_t>> &node_hashes)
{
    uint16_t bin_index{0};
    for (auto bin : node_hashes)
    {
        std::string ixf_tmp_name = "interleavedXOR_" + std::to_string(ixf_pos) + "_bin_" + std::to_string(bin_index) + ".tmp";
        auto tmp_file = std::filesystem::temp_directory_path() / ixf_tmp_name;
        std::ofstream tmp_stream{tmp_file};
        for (size_t h : bin)
            tmp_stream << h << " ";
        tmp_stream.close();
        bin_index++;
    }
}


void read_from_temp_hash_file(int64_t & ixf_position,
                              std::vector<size_t> &node_hashes)
{
    
    std::string ixf_tmp_name = "interleavedXOR_" + std::to_string(ixf_position) + ".tmp";
    auto tmp_file = std::filesystem::temp_directory_path() / ixf_tmp_name;
    if (!std::filesystem::exists(tmp_file))
    {
        std::cerr << ixf_tmp_name << "does not exist!" << std::endl;
        return;
    }
    std::ifstream tmp_stream{tmp_file};
    size_t x;
     while (tmp_stream >> x)
    {
        node_hashes.emplace_back(x);
    }
    tmp_stream.close();
    std::filesystem::remove(tmp_file);
    
}

}