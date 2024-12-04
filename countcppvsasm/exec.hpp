#pragma once

#include <chrono>

template <typename E, typename V>
struct Result
{
	E elapsed{};
	V value{};

	Result() {}
	Result(E elapsed, V value): elapsed{elapsed}, value{value} {}
};

template <typename U, typename C, typename ... A>
auto exec(C c, A &&... a)
{
	const auto start = std::chrono::high_resolution_clock::now();

	const auto value{c(std::forward<A>(a)...)};

	const auto end = std::chrono::high_resolution_clock::now();

	return Result(std::chrono::duration_cast<U>(end - start).count(), value);
}

template <typename C, typename ... A>
auto execms(C c, A &&... a)
{
	return exec<std::chrono::milliseconds>(c, std::forward<A>(a)...);
}

