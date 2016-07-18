#include <string>
#include <iostream>

typedef struct Cubelet {
	char pos;
	char twist;
} s_cubelet;

typedef struct History {
	char cur_phase;
	char search_mode;
	char index;
	char moves[48];
	char rotpt[48];
	char depth_to_go[5 << 20];
} s_history;

void rotate( char k, s_cubelet cubelet[48] ) {
	std::string data = "2#6'&78)5+1/AT[NJ_PERLQO@IAHPNSMBJCKLRMSDHEJNPOQFKGIQLSNF@DBROPMAGCEMPOACSRQDF";
	int i;
	if (k < 4) {
		for (i = 0; i < 4; ++i) {
			 cubelet[64 ^ data[20 + k * 8 + i]].twist =
			(cubelet[64 ^ data[20 + k * 8 + i]].twist + 2 - i % 2) % 3,
			 cubelet[64 ^ data[20 + k * 8 + i + 4]].twist ^= k < 2;
		}
	}
	for (i = 0; i < 7; ++i) {
		std::swap(cubelet[64 ^ data[20 + k * 8 + i + (i != 3)]],
				  cubelet[64 ^ data[20 + k * 8 + i]]);
	}
}

int hashf( s_history *history, s_cubelet cubelet[48] ) {
	char inva[48];
	char b[48];
	int ret = 0;
	int i, j, k;
	switch (history->cur_phase) {
		case 0:
			for (i = 0; i < 11; ++i) {
				ret += ret + cubelet[i].twist;
			}
			return ret;

		case 1:
			for (i = 0; i < 7; ++i) {
				ret = ret * 3 + cubelet[i + 12].twist;
			}
			for (i = 0; i < 11; ++i) {
				ret += ret + (cubelet[i].pos > 7);
			}
			return ret - 7;

		case 2:
			for (i = 0; i < 8; ++i) {
				if (cubelet[i + 12].pos < 16)
					inva[cubelet[i + 12].pos & 3] = ret++;
				else
					b[i - ret] = cubelet[i + 12].pos & 3;
			}
			for (i = 0; i < 7; ++i) {
				ret += ret + (cubelet[i].pos > 3);
			}
			for (i = 0; i < 7; ++i) {
				ret += ret + (cubelet[i + 12].pos > 15);
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
				if (cubelet[i * 4 + j].pos < cubelet[i * 4 + k].pos)
					ret += j << j / 3;
			}
		}
	}
	return ret / 2;
}

int do_search( s_history *history, s_cubelet cubelet[48], char hash_table[48][6912], int depth ) {
	int h = hashf(history, cubelet);
	int i, k;
	int q = (history->cur_phase / 2 * 19 + 8) << 7;
	if ((depth < hash_table[history->cur_phase + 0][h % q] | depth < hash_table[history->cur_phase + 4][h / q]) ^ history->search_mode) {
		if (history->search_mode) {
			if (depth <= history->depth_to_go[h])
				return !h;
			else
				history->depth_to_go[h] = depth;
		}
		hash_table[history->cur_phase + 0][h % q] = std::min(hash_table[history->cur_phase + 0][h % q], static_cast<char>(depth));
		hash_table[history->cur_phase + 4][h / q] = std::min(hash_table[history->cur_phase + 4][h / q], static_cast<char>(depth));

		for (k = 0; k < 6; ++k) {
			for (i = 0; i < 4; ++i) {
				rotate(k, cubelet);
				if (k < history->cur_phase * 2 & i != 1 || i > 2)
					continue;
				history->moves[history->index + 0] = k;
				history->rotpt[history->index + 0] = i;
				++history->index;
				if (do_search(history, cubelet, hash_table, depth - history->search_mode * 2 + 1))
					return 1;
				--history->index;
			}
		}
	}
	return 0;
}

void solve( std::string *mike ) {
	// Variables
	std::string data = "2#6'&78)5+1/AT[NJ_PERLQO@IAHPNSMBJCKLRMSDHEJNPOQFKGIQLSNF@DBROPMAGCEMPOACSRQDF";
	s_history history;
	s_cubelet cubelet[48];
	char hash_table[48][6912];

	// Code
	std::memset(hash_table, 6, sizeof(hash_table));
	int i, k;
	for (i = 0; i < 20; ++i) {
		cubelet[i].pos = i;
	}
	for (history.cur_phase = 0; history.cur_phase < 4; ++history.cur_phase) {
		do_search(&history, cubelet, hash_table, 0);
	}
	for (i = 0; i < 20; ++i) {
		std::string str = mike[i] + std::string("!");
		cubelet[i].pos = data.find(str[0] ^ str[1] ^ str[2]);
		int x = std::min(str.find('U'), str.find('D'));
		cubelet[i].twist = ~x ? x : str[0] > 70;
	}
	for (i = 0; i < 5; ++i) {
		std::swap(cubelet[64 ^ data[20 + history.cur_phase * 8 + i + 16]],
				  cubelet[64 ^ data[20 + history.cur_phase * 8 + i + 21]]);
	}
	history.search_mode = 1;
	for (history.cur_phase = 0; history.cur_phase < 4; ++history.cur_phase) {
		for (i = 0; i < 20; ++i) {
			if (do_search(&history, cubelet, hash_table, i))
				break;
		}
	}
	for (k = 0; k < history.index; ++k) {
		std::cout << "FBRLUD"[history.moves[k] + 0] << history.rotpt[k] + 1 << " ";
	}
}
