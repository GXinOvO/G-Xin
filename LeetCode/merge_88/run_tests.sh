#!/bin/bash

run_cpp_tests() {
    echo "Building and running C++ tests..."
    cd cpp-test
    mkdir -p build
    cd build
    cmake ..
    make
    ctest -V --rerun-failed --output-on-failure
    cd ../..
}

run_py_tests() {
    echo "Running Python tests..."
    cd python-test
    python -m unittest -v test_merge.py
    cd ..
}

run_rust_tests() {
    echo "Running Rust tests..."
    cd rust-test
    cargo test
    cd ..
}

if [ "$1" == "cpp" ]; then
    run_cpp_tests
elif [ "$1" == "py" ]; then
    run_py_tests
elif [ "$1" == "rust" ]; then
    run_rust_tests
elif [ "$1" == "all" ]; then
    run_cpp_tests
    cpp_result=$?
    run_py_tests
    py_result=$?
    run_rust_tests
    rust_result=$?

    echo "Summary of test results:"
    if [ $cpp_result -eq 0 ]; then
        echo "C++ tests passed."
    else
        echo "C++ tests failed."
    fi

    if [ $py_result -eq 0 ]; then
        echo "Python tests passed."
    else
        echo "Python tests failed."
    fi

    if [ $rust_result -eq 0 ]; then
        echo "Rust tests passed."
    else
        echo "Rust tests failed."
    fi
else
    echo "Usage: $0 {cpp|py|rust|all}"
    exit 1
fi
