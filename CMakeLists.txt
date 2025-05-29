cmake_minimum_required(VERSION 3.28)
project(hopnet VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

# esporta il compilation database, utile per altri strumenti, a partire dall'editor
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++20 (volendo anche C++23), senza estensioni non-standard offerte dal compilatore usato
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS
      " -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion"
      " -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast"
      " -fno-omit-frame-pointer")

# abilita asserzioni della standard library
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  string(APPEND CMAKE_CXX_FLAGS " -D_GLIBCXX_ASSERTIONS")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  string(APPEND CMAKE_CXX_FLAGS " -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE")
endif()

# abilita address sanitizer e undefined-behaviour sanitizer in Debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined")
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  string(APPEND CMAKE_CXX_FLAGS " -D_GLIBCXX_SANITIZE_STD_ALLOCATOR")
endif()
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined")

# se usato, richiedi il componente graphics della libreria SFML (versione 2.6 in Ubuntu 24.04)
find_package(OpenCV REQUIRED)

# Lo tolgo se non ci saranno common
include_directories(${CMAKE_SOURCE_DIR}/common)
include_directories(${CMAKE_SOURCE_DIR}/include)
#target_include_directories(binarize PUBLIC ${CMAKE_SOURCE_DIR}/include)


# dichiara un eseguibile chiamato "progetto", prodotto a partire dai file sorgente indicati
# sostituire "progetto" con il nome del proprio eseguibile e i file sorgente con i propri (con nomi sensati!)
# Executable: binarize.out
add_executable(binarize.out
    src/binarize/main.cpp
    src/binarize/utils.cpp
    src/binarize/input.cpp
)

#add_compile_options(-Wno-deprecated-enum-enum-conversion)


# nel caso si usi SFML. analogamente per eventuali altre librerie
target_include_directories(binarize.out PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(binarize.out PRIVATE ${OpenCV_LIBS})

# Executable: train.out
add_executable(train.out
    src/train/main.cpp
    src/train/input.cpp
    src/train/weight_matrix-train.cpp
    src/common/weight_matrix.cpp
    src/common/pattern.cpp
)

# Executable: recall.out
add_executable(recall.out
    src/recall/main.cpp
    src/recall/input.cpp
    src/recall/weight_matrix-recall.cpp
    src/common/weight_matrix.cpp
    src/common/input.cpp
    src/common/pattern.cpp
)

# il testing e' abilitato di default
# per disabilitarlo, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
#if (BUILD_TESTING)

  # aggiungi l'eseguibile progetto.t
 # add_executable(progetto.t file.t.cpp)
  # aggiungi l'eseguibile progetto.t alla lista dei test
 # add_test(NAME progetto.t COMMAND progetto.t)

#endif()
