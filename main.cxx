#include <iostream>

#include "binary.hxx"

[[noreturn]] int main(int argc, char* argv[]) {
	auto x = 4;
	binary<decltype(x)> bin{x};

}