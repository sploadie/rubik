﻿#include <string>
#include <iostream>
#include <sstream>

typedef struct Cubies {
	char pos;
	char twist;
} s_cubies;

typedef struct History {
	char cur_phase;
	char search_mode;
	char index;
	char moves[48];
	char rotpt[48];
	char depth_to_go[5 << 20];
} s_history;

void rotate( char k, s_cubies cubies[48] ) {
	// std::cout << "K: " << static_cast<int>(k) << std::endl;
	std::string data = "RLQO@IAHPNSMBJCKLRMSDHEJNPOQFKGIQLSNF@DBROPMAGCE";
	//                 "::::||||::::||||::::||||::::||||::::||||::::||||"
	int i;
	if (k < 4) {
		for (i = 0; i < 4; ++i) {
			// std::cout << "Index: " << 20 + k * 8 + i << " Value: " << data[20 + k * 8 + i] << std::endl;
			cubies[64 ^ data[k * 8 + i]].twist = (cubies[64 ^ data[k * 8 + i]].twist + 2 - i % 2) % 3;
			cubies[64 ^ data[k * 8 + i + 4]].twist ^= k < 2;
		}
	}
	for (i = 0; i < 7; ++i) {
		std::swap(cubies[64 ^ data[k * 8 + i + (i != 3)]],
				  cubies[64 ^ data[k * 8 + i]]);
	}
}

int hashf( s_history *history, s_cubies cubies[48] ) {
	char inva[48];
	char b[48];
	int ret = 0;
	int i, j, k;
	switch (history->cur_phase) {
		case 0:
			for (i = 0; i < 11; ++i) {
				ret += ret + cubies[i].twist;
			}
			return ret;

		case 1:
			for (i = 0; i < 7; ++i) {
				ret = ret * 3 + cubies[i + 12].twist;
			}
			for (i = 0; i < 11; ++i) {
				ret += ret + (cubies[i].pos > 7);
			}
			return ret - 7;

		case 2:
			for (i = 0; i < 8; ++i) {
				if (cubies[i + 12].pos < 16)
					inva[cubies[i + 12].pos & 3] = ret++;
				else
					b[i - ret] = cubies[i + 12].pos & 3;
			}
			for (i = 0; i < 7; ++i) {
				ret += ret + (cubies[i].pos > 3);
			}
			for (i = 0; i < 7; ++i) {
				ret += ret + (cubies[i + 12].pos > 15);
			}
			return ret * 54 +
				   (inva[static_cast<int>(b[0])] ^ inva[static_cast<int>(b[1])]) * 2 +
				  ((inva[static_cast<int>(b[0])] ^ inva[static_cast<int>(b[2])]) >
				   (inva[static_cast<int>(b[0])] ^ inva[static_cast<int>(b[3])])) - 3587708;
	}

	for (i = 0; i < 5; ++i) {
		ret *= 24;
		for (j = 0; j < 4; ++j) {
			for (k = 0; k < j; ++k) {
				if (cubies[i * 4 + j].pos < cubies[i * 4 + k].pos)
					ret += j << j / 3;
			}
		}
	}
	return ret / 2;
}

int do_search( s_history *history, s_cubies cubies[48], char hash_table[48][6912], int depth ) {
	int h = hashf(history, cubies);
	int i, k;
	int q = (history->cur_phase / 2 * 19 + 8) << 7;
	if ((depth < hash_table[history->cur_phase + 0][h % q] | depth < hash_table[history->cur_phase + 4][h / q]) ^ history->search_mode) {
		if (history->search_mode) {
			// std::cout << "H: " << static_cast<int>(h) << std::endl;
			if (depth <= history->depth_to_go[h])
				return !h;
			else
				history->depth_to_go[h] = depth;
		}
		hash_table[history->cur_phase + 0][h % q] = std::min(hash_table[history->cur_phase + 0][h % q], static_cast<char>(depth));
		hash_table[history->cur_phase + 4][h / q] = std::min(hash_table[history->cur_phase + 4][h / q], static_cast<char>(depth));

		for (k = 0; k < 6; ++k) {
			for (i = 0; i < 4; ++i) {
				rotate(k, cubies);
				if (k < history->cur_phase * 2 & i != 1 || i > 2)
					continue;
				history->moves[history->index + 0] = k;
				history->rotpt[history->index + 0] = i;
				++history->index;
				if (do_search(history, cubies, hash_table, depth - history->search_mode * 2 + 1))
					return 1;
				--history->index;
			}
		}
	}
	return 0;
}

std::string solve( std::string *mike ) {
	// Variables
	std::string data = "2#6'&78)5+1/AT[NJ_PERLQO@IAHPNSMBJCKLRMSDHEJNPOQFKGIQLSNF@DBROPMAGCEMPOACSRQDF";
	s_history history;
	s_cubies cubies[48];
	char hash_table[48][6912];
	std::string solution;
	std::stringstream solution_stream;
	int i, k;

	// Clearing memory
	std::memset(&history, 0, sizeof(s_history));
	std::memset(hash_table, 6, sizeof(hash_table));
	for (i = 0; i < 20; ++i) {
		cubies[i].pos = i;
	}
	// Code
	for (history.cur_phase = 0; history.cur_phase < 4; ++history.cur_phase) {
		do_search(&history, cubies, hash_table, 0);
	}
	for (i = 0; i < 20; ++i) {
		std::string str = mike[i] + std::string("!");
		cubies[i].pos = data.find(str[0] ^ str[1] ^ str[2]);
		int x = std::min(str.find('U'), str.find('D'));
		cubies[i].twist = ~x ? x : str[0] > 70;
	}
	for (i = 0; i < 5; ++i) {
		std::swap(cubies[64 ^ data[20 + history.cur_phase * 8 + i + 16]],
				  cubies[64 ^ data[20 + history.cur_phase * 8 + i + 21]]);
	}
	history.search_mode = 1;
	for (history.cur_phase = 0; history.cur_phase < 4; ++history.cur_phase) {
		for (i = 0; i < 20; ++i) {
			if (do_search(&history, cubies, hash_table, i))
				break;
		}
	}
	for (k = 0; k < history.index; ++k) {
		solution_stream << "FBRLUD"[history.moves[k] + 0] << history.rotpt[k] + 1;
		if (k < history.index - 1)
			solution_stream << ' ';
	}
	solution = solution_stream.str();
	std::replace(solution.begin(), solution.end(), '3', '\'');
	solution.erase(std::remove(solution.begin(), solution.end(), '1'), solution.end());
	return solution;
}
