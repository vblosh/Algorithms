//============================================================================
// Name        : worter.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <chrono>
#include "solver.h"

using hrclock = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<float, std::milli>;

void do_solve(string filename)
{
	hrclock::time_point start;
	duration elapsed;

	solver solver;
	start = hrclock::now();
	solver.load_data(filename);
	elapsed = hrclock::now() - start;
	std::cout << "load data requires " << elapsed.count() << " ms\n";
	solver.print_data();
	start = hrclock::now();
	if (solver.solve())
	{
		elapsed = hrclock::now() - start;
		std::cout << "finding sloution requires " << elapsed.count() << " ms\n";
		std::cout << "solution found!\n";
		solver.print_solution();
	}
	else
		std::cout << "solution not found!\n";
}

int main(int argc, char **argv) {
	if (argc != 2)
		return 1;

	do_solve(argv[1]);

	return 0;
}
