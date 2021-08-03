# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(cpploxTests LANGUAGES CXX)

add_executable(cpplox_test source/cpplox_test.cpp)
target_link_libraries(cpplox_test PRIVATE cpplox_lib)
target_compile_features(cpplox_test PRIVATE cxx_std_20)

add_test(NAME cpplox_test COMMAND cpplox_test)
