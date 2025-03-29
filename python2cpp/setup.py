from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

# Define the extension module
ext_modules = [
    Pybind11Extension(
        "matrix_mult",               # Name of the module
        ["matrix_mult.cpp"],         # Source file(s)
        language="c++",              # Specify C++ as the language
    ),
]

# Setup configuration
setup(
    name="matrix_mult",
    version="0.1",
    author="Your Name",
    description="Matrix multiplication implemented in C++ using pybind11",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},  # Use pybind11's build system
)
