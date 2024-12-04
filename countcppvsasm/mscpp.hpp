#pragma once

inline size_t clcount(const char *begin, const char *end, char sym)
{
	size_t r = 0;
	for (; begin < end; ++begin) r += sym == *begin;
	return r;
}
