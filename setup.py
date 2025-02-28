from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
      "ciff",
      ["pyciff.cpp", "ciff.cpp", "ciff.hpp"],
      include_dirs=[pybind11.get_include()],
      language="c++",  
    ),
]

setup(
    name="ciff",
    version="0.1",
    ext_modules=ext_modules,
)