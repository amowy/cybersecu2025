#ifndef CIFF_CPP
#define CIFF_CPP

#include "ciff.hpp"

CIFF::CIFF() :
    magic_("CIFF"),
    header_size_(0),
    content_size_(0),
    width_(0),
    height_(0),
    caption_(""),
    is_valid_(true) {}

CIFF::CIFF(
    const string& magic,
    uint64_t header_size,
    uint64_t content_size,
    uint64_t width,
    uint64_t height,
    const string& caption,
    const vector<string>& tags = {},
    const vector<tuple<uint8_t, uint8_t, uint8_t>>& pixels = {}
) : magic_(magic),
    header_size_(header_size),
    content_size_(content_size),
    width_(width),
    height_(height),
    caption_(caption),
    tags_(tags),
    pixels_(pixels),
    is_valid_(true) {}

CIFF CIFF::parse_ciff_file(const string &file_path) {
    CIFF new_ciff;
    size_t bytes_read = 0;

    try {
        ifstream ciff_file(file_path, ios::binary);
        if (!ciff_file.is_open()) {
            throw runtime_error("COULDN'T OPEN FILE");
        }

        char magic[5] = {0}; //needs to be 5 bcs of \0 string terminator
        ciff_file.read(magic, 4);
        if (ciff_file.gcount() != 4) {
            throw runtime_error("Failed to read magic bytes");
        }
        bytes_read += 4;
        new_ciff.set_magic(string(magic, 4));
        if (new_ciff.magic() != "CIFF") {
            new_ciff.set_is_valid(false);
            throw runtime_error("Invalid magic chars");
        }

        uint64_t h_size;
        ciff_file.read(reinterpret_cast<char*>(&h_size), 8);
        if (ciff_file.gcount() != 8) {
            throw runtime_error("Failed to read header size");
        }
        bytes_read += 8;
        new_ciff.set_header_size(h_size);

        if(new_ciff.header_size() < 38 || new_ciff.header_size() > UINT64_MAX) {
            throw runtime_error("Invalid header size");
        }
        
        uint64_t c_size;
        ciff_file.read(reinterpret_cast<char*>(&c_size), 8);
        if (ciff_file.gcount() != 8) {
            throw runtime_error("Failed to read content size");
        }
        bytes_read += 8;
        new_ciff.set_content_size(c_size);
        if (new_ciff.content_size() < 0 || new_ciff.content_size() > UINT64_MAX) {
            throw runtime_error("Invalid content size");
        }
        
        uint64_t width;
        ciff_file.read(reinterpret_cast<char*>(&width), 8);
        if (ciff_file.gcount() != 8) {
            throw runtime_error("Failed to read width size");
        }
        bytes_read += 8;
        new_ciff.set_width(width);

        uint64_t height;
        ciff_file.read(reinterpret_cast<char*>(&height), 8);
        if (ciff_file.gcount() != 8) {
            throw runtime_error("Failed to read height size");
        }
        bytes_read += 8;
        new_ciff.set_height(height);

        if(new_ciff.content_size() != new_ciff.width() * new_ciff.height() * 3) {
            throw runtime_error("Content size invalid");
        }

        string caption = "";
        char c;
        ciff_file.read(&c, 1);
        if (ciff_file.gcount() != 1) {
            throw runtime_error("Failed to read caption char");
        }
        bytes_read++;

        while (c != '\n') {
            caption += c;
            ciff_file.read(&c, 1);
            if (ciff_file.gcount() != 1) {
                throw runtime_error("Failed to read caption char");
            }
            bytes_read++;
        }
        new_ciff.set_caption(caption);

        vector<string> tags;
        string tag = "";
        while (bytes_read != new_ciff.header_size()) {
            ciff_file.read(&c, 1);
            if (ciff_file.gcount() != 1) {
                throw runtime_error("Failed to read tag char");
            }
            bytes_read++;
            if (c == '\n') {
                throw runtime_error("Tag contains newline");
            }
            tag += c;
            if (c == '\0') {
                tags.push_back(tag);
                tag.clear();
            }
            if (bytes_read == new_ciff.header_size_ && c != '\0') {
                throw runtime_error("Last header character is not null");
            }
        }

        for (const auto& t : tags) {
            if (t.empty() || t.back() != '\0') {
                throw runtime_error("Tag doesnt end in null char");
            }
        }
        new_ciff.set_tags(tags);

        vector<tuple<uint8_t, uint8_t, uint8_t>> pixels;
        while (bytes_read < new_ciff.header_size() + new_ciff.content_size()) {
            uint8_t rgb[3];
            ciff_file.read(reinterpret_cast<char*>(rgb), 3);
            if (ciff_file.gcount() != 3) {
                throw runtime_error("Failed to read pixels");
            }
            bytes_read += 3;
            pixels.emplace_back(rgb[0], rgb[1], rgb[2]);
        }
        new_ciff.set_pixels(pixels);

        char extra;
        ciff_file.read(&extra, 1);
        if (ciff_file.gcount() != 0) {
            throw std::runtime_error("File contains extra data");
        }
    }
    catch(const exception& e) {
        new_ciff.set_is_valid(false);
        cout << e.what() << endl;
    }
    

    return CIFF();
}

#endif
