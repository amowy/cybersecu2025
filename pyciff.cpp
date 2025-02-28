#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ciff.hpp"

namespace py = pybind11;

PYBIND11_MODULE(ciff, m) {
    py::class_<CIFF>(m, "CIFF")
        .def(py::init<>())
        .def(py::init<const string&, uint64_t, uint64_t, uint64_t, uint64_t, const string&, const vector<string>&, const vector<tuple<uint8_t, uint8_t, uint8_t>>&>())
        .def_property_readonly("is_valid", &CIFF::is_valid)
        .def_property_readonly("magic", &CIFF::magic)
        .def_property_readonly("header_size", &CIFF::header_size)
        .def_property_readonly("content_size", &CIFF::content_size)
        .def_property_readonly("width", &CIFF::width)
        .def_property_readonly("height", &CIFF::height)
        .def_property_readonly("caption", &CIFF::caption)
        .def_property_readonly("tags", &CIFF::tags)
        .def_property_readonly("pixels", &CIFF::pixels)
        .def_static("parse_ciff_file", &CIFF::parse_ciff_file);
}