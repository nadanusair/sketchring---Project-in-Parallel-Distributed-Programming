# cmake_minimum_required(VERSION <specify CMake version here>)
project(ProjectMakbeleMevozar)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProjectMakbeleMevozar scketchRing.h io.cpp countmin/countmin.cpp countmin/countmin.h countmin/prng.cc countmin/prng.h countmin/rand48.cc countmin/rand48.h xxhash/xxhash32.h test.h test_generator.cpp test_generator.h UF.cpp UF.h)