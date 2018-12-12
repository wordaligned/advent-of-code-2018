#include <algorithm>
#include <cassert>
#include <list>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

template <typename Iter>
Iter advance(Iter pos, Iter const begin, Iter const end, unsigned n)
{
	assert(begin != end && pos != end);

	while (n-- != 0)
		if (++pos == end) pos = begin;

	return pos;
}
		
template <typename Iter>
Iter go_back(Iter pos, Iter const begin, Iter const end, unsigned n)
{
	assert(begin != end && pos != end);

	for ( ; n-- != 0 ; --pos)
		if (pos == begin) pos = end;

	return pos;
}

std::pair<unsigned long, unsigned long>
parse_cli(int argc, char * argv[])
{
	if (argc == 3)
	{
		return { std::stoul(argv[1]), std::stoul(argv[2]) };
	}
	std::cerr << "Usage: " << argv[0] << " PLAYERS MARBLES\n";
	std::exit(1);
}

int main(int argc, char * argv[])
{
	std::map<unsigned, unsigned long> scores;
	std::list<unsigned long> marbles{0};
	auto pos = std::begin(marbles);

	auto [n_players, n_marbles] = parse_cli(argc, argv);

	for (auto n = 1ul; n <= n_marbles; ++n)
	{
		auto const begin = std::begin(marbles), end = std::end(marbles);
		if (n % 23)
		{
			pos = advance(pos, begin, end, 2);
			pos = marbles.insert(pos, n);
		}
		else
		{
			pos = go_back(pos, begin, end, 7);
			scores[n % n_players] += n + *pos;
			pos = marbles.erase(pos);
		}
	}

	auto const m = std::max_element
		(std::begin(scores), std::end(scores),
		 [](auto const & s, auto const & t) { return s.second < t.second; });

	std::cout << m->second << '\n';

	return 0;
}
