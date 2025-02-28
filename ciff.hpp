#ifndef CIFF_HPP
#define CIFF_HPP

#include "string"
#include "vector"
#include "fstream"
#include "stdexcept"
#include "cstdint"
#include "tuple"
#include "iostream"

using namespace std;

class CIFF {
    private:
        string magic_;
        uint64_t header_size_;
        uint64_t content_size_;
        uint64_t width_;
        uint64_t height_;
        string caption_;
        vector<string> tags_;
        vector<tuple<uint8_t, uint8_t, uint8_t>> pixels_;
        bool is_valid_;
    public:
        CIFF() :
            magic_("CIFF"),
            header_size_(0),
            content_size_(0),
            width_(0),
            height_(0),
            caption_(""),
            is_valid_(true) {}
        CIFF(
            const string& magic,
            uint64_t header_size,
            uint64_t content_size,
            uint64_t width,
            uint64_t height,
            const string& caption,
            const vector<string>& tags = {},
            const std::vector<std::tuple<uint8_t, uint8_t, uint8_t>>& pixels = {}
        );

        //getters and setters
        bool is_valid() const { return is_valid_; }
        void set_is_valid(bool value) { is_valid_ = value; }
        
        const string& magic() const { return magic_; }
        void set_magic(const string& value) { magic_ = value; }
        
        uint64_t header_size() const { return header_size_; }
        void set_header_size(uint64_t value) { header_size_ = value; }
        
        uint64_t content_size() const { return content_size_; }
        void set_content_size(uint64_t value) { content_size_ = value; }
        
        uint64_t width() const { return width_; }
        void set_width(uint64_t value) { width_ = value; }
        
        uint64_t height() const { return height_; }
        void set_height(uint64_t value) { height_ = value; }
        
        const std::string& caption() const { return caption_; }
        void set_caption(const std::string& value) { caption_ = value; }
        
        const vector<string>& tags() const { return tags_; }
        void set_tags(const vector<string>& value) { tags_ = value; }
        
        const vector<tuple<uint8_t, uint8_t, uint8_t>>& pixels() const { return pixels_; }
        void set_pixels(const vector<tuple<uint8_t, uint8_t, uint8_t>>& value) { pixels_ = value; }

        //parser
        static CIFF parse_ciff_file(const string& filepath);

};

#endif