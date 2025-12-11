# meson.build

project('CountFnQty', 'cpp', default_options: ['cpp_std=c++17'])

# Require LLVM and Clang dependencies
llvm_dep = dependency('llvm')

cpp = meson.get_compiler('cpp')
clang_dep = cpp.find_library('clang-cpp')

subdir('src')
