#include "ciff.hpp"
#ifndef CIFF_CPP
#define CIFF_CPP

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

#endif
