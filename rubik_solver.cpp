﻿#include <string>
#include <iostream>
// using namespace std;

std::string data = "2#6'&78)5+1/AT[NJ_PERLQO@IAHPNSMBJCKLRMSDHEJNPOQFKGIQLSNF@DBROPMAGCEMPOACSRQDF";
char    inva[48],
		b[48],
		cur_phase,
		search_mode,
		history_idx,
		history_mov[48],
		history_rpt[48],
		depth_to_go[5 << 20],
		hash_table[48][6912];

struct Cubelet {
	char pos;
	char twi;
} cubelet[48];

void rot( char cur_phase ) {
	if (cur_phase < 4) {
		for (int i = -1; ++i < 4;)
			cubelet[64 ^ data[20 + cur_phase * 8 + i]].twi =
			(cubelet[64 ^ data[20 + cur_phase * 8 + i]].twi + 2 -
			 i % 2) % 3,
			cubelet[64 ^ data[20 + cur_phase * 8 + i + 4]].twi ^=
			cur_phase < 2;
	}

	for (int i = -1; ++i < 7;) {
		std::swap(cubelet[64 ^ data[20 + cur_phase * 8 + i + (i != 3)]],
			 cubelet[64 ^ data[20 + cur_phase * 8 + i]]);
	}
}

int hashf( void ) {
	int ret = 0;
	switch (cur_phase) {
		case 0:
			for (int i = -1; ++i < 11;) {
				ret += ret + cubelet[i].twi;
			}
			return ret;

		case 1:
			for (int i = -1; ++i < 7;) {
				ret = ret * 3 + cubelet[i + 12].twi;
			}
			for (int i = -1; ++i < 11;) {
				ret += ret + (cubelet[i].pos > 7);
			}
			return ret - 7;

		case 2:
			for (int i = -1; ++i < 8;) {
				if (cubelet[i + 12].pos < 16)
					inva[cubelet[i + 12].pos & 3] = ret++;
				else
					b[i - ret] = cubelet[i + 12].pos & 3;
			}
			for (int i = -1; ++i < 7;) {
				ret += ret + (cubelet[i].pos > 3);
			}
			for (int i = -1; ++i < 7;) {
				ret += ret + (cubelet[i + 12].pos > 15);
			}
			return ret * 54 +
				   (inva[static_cast<int>(b[0])] ^ inva[static_cast<int>(b[1])]) * 2 +
				  ((inva[static_cast<int>(b[0])] ^ inva[static_cast<int>(b[2])]) >
				   (inva[static_cast<int>(b[0])] ^ inva[static_cast<int>(b[3])])) - 3587708;
	}

	for (int i = -1; ++i < 5;) {
	ret *= 24;
	int cur_phase;
	for (cur_phase = -1; ++cur_phase < 4;)
		for (int k = -1; ++k < cur_phase;)
		if (cubelet[i * 4 + cur_phase].pos <
			cubelet[i * 4 + k].pos)
			ret += cur_phase << cur_phase / 3;
	}
	return ret / 2;
}

int do_search( int dpt ) {
	int h = hashf(),
	q = (cur_phase / 2 * 19 + 8) << 7;
	if ((dpt < hash_table[cur_phase + 0][h % q] | dpt < hash_table[cur_phase + 4][h / q]) ^ search_mode) {
		if (search_mode) {
			if (dpt <= depth_to_go[h])
				return !h;
			else
				depth_to_go[h] = dpt;
		}
		// hash_table[cur_phase ][h%q] <?= dpt;
		// hash_table[cur_phase+4][h/q] <?= dpt;
		hash_table[cur_phase + 0][h % q] = std::min(hash_table[cur_phase + 0][h % q], static_cast<char>(dpt));
		hash_table[cur_phase + 4][h / q] = std::min(hash_table[cur_phase + 4][h / q], static_cast<char>(dpt));

		for (int k = -1; ++k < 6;) {
			for (int i = -1; ++i < 130 % 21;) {
				rot(k);
				if (k < cur_phase * 2 & i != 1 || i > 2)
					continue;
				history_mov[history_idx + 0] = k;
				history_rpt[history_idx++ + 0] = i;
				if (do_search(dpt - search_mode * 2 + 1))
					return 1;
				history_idx--;
			}
		}
	}
	return 0;
}

int main( int, char **arg ) {
	memset(hash_table, 6, sizeof(hash_table));
	for (int i = -1; ++i < 20;) {
		cubelet[i].pos = i;
	}
	for (cur_phase = -1; ++cur_phase < 4;) {
		do_search(0);
	}
	for (int i = -1; ++i < 20;) {
		std::string          s = arg[i + 1] + std::string("!");
		cubelet[i].pos = data.find(s[0] ^ s[1] ^ s[2]);
		int x = std::min(s.find(85), s.find(68));
		cubelet[i].twi = ~x ? x : s[0] > 70;
	}
	for (int i = -1; ++i < 5;) {
		std::swap(cubelet[64 ^ data[20 + cur_phase * 8 + i + 16]],
			 cubelet[64 ^ data[20 + cur_phase * 8 + i + 21]]);
	}

	search_mode = 1;
	for (cur_phase = -1; ++cur_phase < 4;) {
		for (int i = -1; ++i < 20;) {
			if (do_search(i))
				break;
		}
	}

	for (int k = -1; ++k < history_idx;) {
		std::cout << "FBRLUD"[history_mov[k] + 0] << history_rpt[k] + 1 << " ";
	}

	return 0;
}