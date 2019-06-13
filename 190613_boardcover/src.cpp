#include <iostream>
#include <string>
#include <limits>

#define MAX_LEN 20
#define NUM_CASES 12

unsigned int cover_board(bool is_white[MAX_LEN][MAX_LEN], unsigned int nr, unsigned int nc, unsigned int num_white);
unsigned int possible(bool is_white[MAX_LEN][MAX_LEN], unsigned int nr, unsigned int nc, unsigned int r, unsigned int c);
void fill_board(bool is_white[MAX_LEN][MAX_LEN], unsigned int r, unsigned int c, unsigned int case_num, bool white);

int main()
{
	unsigned int num_cases, H, W;
	bool is_white[MAX_LEN][MAX_LEN];
	std::string buffer;

	std::cin >> num_cases;

	for (int c=0; c<num_cases; c++) {
		/* ======================== I/O ========================= */
		std::cin >> H >> W;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		unsigned int num_white = 0;

		for (unsigned int h=0; h<H; h++) {
			std::getline(std::cin, buffer);
			for (unsigned int w=0; w<W; w++) {
				is_white[h][w] = buffer[w] == '.' ? true : false;
				num_white += (buffer[w] == '.');
			}
		}

		/* ======================== Algorithm ========================= */
		std::cout << cover_board(is_white, H, W, num_white) << std::endl;
	}

	return 0;
}

void print_board(bool is_white[MAX_LEN][MAX_LEN], unsigned int H, unsigned int W) {
	for (unsigned int h=0; h<H; h++) {
		for (unsigned int w=0; w<W; w++) {
			std::cout << is_white[h][w] << ' ';
		}
		std::cout << std::endl;
	}
}


unsigned int cover_board(bool is_white[MAX_LEN][MAX_LEN], unsigned int nr, unsigned int nc, unsigned int num_white)
{
	if (num_white % 3 != 0) return 0;
	if (num_white == 0) return 1;

	/* Find top-left white cell */
	unsigned int r, c, found = 0;
	for (r=0; r<nr; r++) {
		for (c=0; c<nc; c++) {
			if (is_white[r][c]) {
				found = 1;
				break;
			}
		}
		if (found) break;
	}
#ifdef DEBUG
	std::cout << "cell: [" << nr << "," << nc << "], num_white = " << num_white << std::endl;
	std::cout << "topleft: [" << r << "," << c << "]" << std::endl;
	print_board(is_white, nr, nc);
#endif

	unsigned int candidates = possible(is_white, nr, nc, r, c);
	if (!candidates) return 0;

#ifdef DEBUG
	std::cout << "candidates = " << candidates << std::endl;
#endif

	unsigned int sum = 0;

	for (unsigned int case_num=0; case_num<NUM_CASES; case_num++) {
		if ((1<<case_num) & candidates) {
			fill_board(is_white, r, c, case_num, false);
			sum += cover_board(is_white, nr, nc, num_white-3);
			fill_board(is_white, r, c, case_num, true);
		}
	}

	return sum;
}

unsigned int possible(bool is_white[MAX_LEN][MAX_LEN], unsigned int nr, unsigned int nc, unsigned int r, unsigned int c)
{
	unsigned int output = 0;
	if ((r < nr and c < nc) and is_white[r][c]) {
		if ((r > 0 and c < nc-1) and (is_white[r-1][c] and is_white[r-1][c+1]))
			output |= (1<<0);
		if ((r > 0 and c < nc-1) and (is_white[r][c+1] and is_white[r-1][c+1]))
			output |= (1<<1);
		if ((r < nr-1 and c < nc-1) and (is_white[r][c+1] and is_white[r+1][c+1]))
			output |= (1<<2);
		if ((r < nr-1 and c < nc-1) and (is_white[r+1][c] and is_white[r+1][c+1]))
			output |= (1<<3);
		if ((r < nr-1 and c > 0) and (is_white[r+1][c] and is_white[r+1][c-1]))
			output |= (1<<4);
		if ((r < nr-1 and c > 0) and (is_white[r][c-1] and is_white[r+1][c-1]))
			output |= (1<<5);
		if ((r > 0 and c > 0) and (is_white[r][c-1] and is_white[r-1][c-1]))
			output |= (1<<6);
		if ((r > 0 and c > 0) and (is_white[r-1][c] and is_white[r-1][c-1]))
			output |= (1<<7);

		if ((r > 0 and c < nc-1) and (is_white[r-1][c] and is_white[r][c+1]))
			output |= (1<<8);
		if ((r < nr-1 and c < nc-1) and (is_white[r][c+1] and is_white[r+1][c]))
			output |= (1<<9);
		if ((r < nr-1 and c > 0) and (is_white[r+1][c] and is_white[r][c-1]))
			output |= (1<<10);
		if ((r > 0 and c > 0) and (is_white[r][c-1] and is_white[r-1][c]))
			output |= (1<<11);
	}
	return output;
}

void fill_board(bool is_white[MAX_LEN][MAX_LEN], unsigned int r, unsigned int c, unsigned int case_num, bool white)
{
	is_white[r][c] = white;
	if (case_num == 0)
		is_white[r-1][c] = is_white[r-1][c+1] = white;
	if (case_num == 1)
		is_white[r][c+1] = is_white[r-1][c+1] = white;
	if (case_num == 2)
		is_white[r][c+1] = is_white[r+1][c+1] = white;
	if (case_num == 3)
		is_white[r+1][c] = is_white[r+1][c+1] = white;
	if (case_num == 4)
		is_white[r+1][c] = is_white[r+1][c-1] = white;
	if (case_num == 5)
		is_white[r][c-1] = is_white[r+1][c-1] = white;
	if (case_num == 6)
		is_white[r][c-1] = is_white[r-1][c-1] = white;
	if (case_num == 7)
		is_white[r-1][c] = is_white[r-1][c-1] = white;

	if (case_num == 8)
		is_white[r-1][c] = is_white[r][c+1] = white;
	if (case_num == 9)
		is_white[r][c+1] = is_white[r+1][c] = white;
	if (case_num == 10)
		is_white[r+1][c] = is_white[r][c-1] = white;
	if (case_num == 11)
		is_white[r][c-1] = is_white[r-1][c] = white;
	return;
}

