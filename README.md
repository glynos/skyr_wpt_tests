# Skyr URL

## Status

[![License](
    https://img.shields.io/badge/license-boost-blue.svg "License")](
    https://github.com/cpp-netlib/url/blob/master/LICENSE_1_0.txt)

## Introduction

This repo contains tests for the [Skyr URL](https://github.com/cpp-netlib/url) project.

## Building and running the tests

This project requires the availability of a C++17 compliant compiler
and standard library.

### Installing dependencies using `vcpkg`

Using `vcpkg`, install the library dependencies:

```bash
> cd ${VCPKG_ROOT}
> git init
> git remote add origin https://github.com/Microsoft/vcpkg.git
> git fetch origin master
> git checkout -b master origin/master
> ./bootstrap-vcpkg.sh
> ./vcpkg install tl-expected catch2 nlohmann-json fmt
```

### Building with `CMake` and `Ninja`

From a terminal, execute the following sequence of commands:

```bash
> mkdir _build
> cmake \
    -B _build \
    -G "Ninja" \
    -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/vcpkg/scripts/buildsystems/vcpkg.cmake \
    .
> cmake --build _build
```

To run the tests:

```bash
> cmake --build _build --target test
```

On Windows, replace the target with ``RUN_TESTS``.

## License

This library is released under the Boost Software License (please see
http://boost.org/LICENSE_1_0.txt or the accompanying LICENSE_1_0.txt
file for the full text).

## Contact

Any questions about this library can be addressed to the cpp-netlib
[developers mailing list]. Issues can be filed using Github at
http://github.com/cpp-netlib/url/issues.

[developers mailing list]: cpp-netlib@googlegroups.com
