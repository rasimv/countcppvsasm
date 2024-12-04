#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "exec.hpp"
#include "mscpp.hpp"
#include "feldthusen.h"

int main()
{
	std::mt19937 engine{1234567890};

	std::vector<char> buffer(1024 * 1024 * 1024ll);
	for (auto &e : buffer) e = engine();

	double sl = 0, cl = 0, fh = 0;
	size_t prev;

	std::cout << std::fixed << std::setprecision(0) << "milliseconds:" << std::endl;

	for (int i = 0; i < 3 * 10; ++i)
	{
		const auto begin = buffer.data(), end = begin + std::size(buffer);

		size_t value;

		if (i % 3 == 0)
		{
			const auto res{execms(&std::count<const char *, char>, begin, end, 'a') };
			sl += res.elapsed;
			value = res.value;

			std::cout << "\tsl: " << res.elapsed << std::endl;
		}
		else if (i % 3 == 1)
		{
			const auto res{execms(&clcount, begin, end, 'a')};
			cl += res.elapsed;
			value = res.value;

			std::cout << "\tcl: " << res.elapsed << std::endl;
		}
		else
		{
			const auto res{execms(&fhcount, begin, end, 'a')};
			fh += res.elapsed;
			value = res.value;

			std::cout << "\tfh: " << res.elapsed << std::endl;
		}

		if (i > 0 && prev != value)
		{
			std::cout << "err" << std::endl;
			return -1;
		}

		prev = value;
	}

	std::cout << std::endl <<
		"sl: " << sl << " | cl: " << cl << " | fh: " << fh << std::endl;

	return 0;
}
