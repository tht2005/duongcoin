#ifndef DUONGHASH_HPP
#define DUONGHASH_HPP

#define INIT_H kjlk2dsdjskljlijdlsjkdljf__dkfjlds_
#define K kjlk2ijdlsjkdljf__2020jkjl92029dkfjlds_

#include <assert.h>
#include <string.h>

namespace duonghash {
	const int WORD_SIZE = 32;

	const int BLOCK_SIZE = 512;
	const int LEN_SIZE = 64;

	typedef uint32_t ul;

	const ul INIT_H[] = {
		0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
		0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
	};
	const ul K[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};	

	ul bstoi(char* s, const char* e) {
		ul res = 0;
		while(s != e) {
			res <<= 1;
			if(*(s++) == '1') {
				res |= 1;
			}
		}
		return res;	
	}

	ul RotR(ul A, int n) {
		if(n >= WORD_SIZE) {
			n %= WORD_SIZE;
		}
		ul B = A >> n, C = A & ((1LL << n) - 1);
		return B | (C << (WORD_SIZE - n));
	}

	ul ShR(ul A, int n) {
		return A >> n;
	}

	ul Ch(ul x, ul y, ul z) {
		return (x & y) ^ (~x & z);
	}

	ul Maj(ul x, ul y, ul z) {
		return (x & y) ^ (x & z) ^ (y & z);
	}

	ul SIGMA_0(ul x) {
		return RotR(x, 2) ^ RotR(x, 13) ^ RotR(x, 22);
	}
	ul SIGMA_1(ul x) {
		return RotR(x, 6) ^ RotR(x, 11) ^ RotR(x, 25);
	}
	
	ul sigma_0(ul x) {
		return RotR(x, 7) ^ RotR(x, 18) ^ ShR(x, 3);
	}
	ul sigma_1(ul x) {
		return RotR(x, 17) ^ RotR(x, 19) ^ ShR(x, 10);
	}

	int calc_new_msg_len(int msg_len) {
		msg_len += 2 + LEN_SIZE;
		return (msg_len + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE;
	}

	char* padding(const char* message, int *msg_len) {
		int new_msg_len = calc_new_msg_len(*msg_len);
		char* padded_msg = (char*)malloc((new_msg_len + 5) * sizeof(char));

		memcpy(padded_msg, message, (*msg_len) * sizeof(char));

		for(int i = *msg_len; i < new_msg_len; ++i) {
			if(i == *msg_len) {
				padded_msg[i] = '1';
			}
			else if(new_msg_len - i <= LEN_SIZE) {
				padded_msg[i] = '0' + ((uint64_t)*msg_len >> (new_msg_len - i - 1) & 1);
			}
			else {
				padded_msg[i] = '0';
			}
		}
		padded_msg[new_msg_len] = 0;

		*msg_len = new_msg_len;
		return padded_msg;
	}

	const int BLOCK_DEC_INIT = BLOCK_SIZE / WORD_SIZE;
	const int BLOCK_DEC_TOTAL = 64;

	void block_decomposition(char* block_head, ul W[]) {
		for(int i = 0; i < BLOCK_DEC_INIT; ++i) {
			W[i] = bstoi(block_head + i * WORD_SIZE, block_head + (i + 1) * WORD_SIZE);
		}
		for(int i = BLOCK_DEC_INIT; i < BLOCK_DEC_TOTAL; ++i) {
			W[i] = sigma_1(W[i - 2]) + W[i - 7] + sigma_0(W[i - 15]) + W[i - 16];
		}
	}

	ul* binary_sha256(const char* message) {
		int msg_len = strlen(message);
		char* padded_msg = padding(message, &msg_len);

		assert(msg_len % BLOCK_SIZE == 0);

		int h_len = sizeof(INIT_H) / sizeof(INIT_H[0]);
		ul *H = (ul*)malloc((h_len + 2) * sizeof(ul));
		memcpy(H, INIT_H, h_len * sizeof(ul));

		ul W[BLOCK_DEC_TOTAL + 5];

		for(int block_head_pos = 0; block_head_pos < msg_len; block_head_pos += BLOCK_SIZE) {
			block_decomposition(padded_msg + block_head_pos, W);
			ul 	a = H[0], b = H[1], c = H[2], d = H[3],
				e = H[4], f = H[5], g = H[6], h	= H[7];
			for(int i = 0; i < BLOCK_DEC_TOTAL; ++i) {
				ul T1 = h + SIGMA_1(e) + Ch(e, f, g) + K[i] + W[i];
				ul T2 = SIGMA_0(a) + Maj(a, b, c);
				h = g;
				g = f;
				f = e;
				e = d + T1;
				d = c;
				c = b;
				b = a;
				a = T1 + T2;
			}
			H[0] += a; H[1] += b; H[2] += c; H[3] += d;
			H[4] += e; H[5] += f; H[6] += g; H[7] += h;
		}

		free(padded_msg);
		return H;
	}

	ul hex_char_to_dec(char c) {
		if('0' <= c && c <= '9') {
			return c - '0';
		}
		c = tolower(c);
		assert('a' <= c && c <= 'f');
		return 10 + c - 'a';
	}

	ul* sha256(const char* hex_message) {
		int len = strlen(hex_message);	
		char *bin_message = (char*)malloc((4 * len + 5) * sizeof(char));
		memset(bin_message, 0, (4 * len + 2) * sizeof(char));
		for(int i = 0; i < len; ++i) {
			int ch = hex_char_to_dec(hex_message[i]);
			for(int j = 0; j < 4; ++j) {
				bin_message[(i << 2) | (3 - j)] = '0' + (ch >> j & 1);
			}
		}
		ul *H = binary_sha256(bin_message);
		free(bin_message);
		return H;
	}
}

#undef INIT_H
#undef K

#endif

