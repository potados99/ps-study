#include <iostream>
#include <vector>
#include <limits>

template <int n>
struct Triangle { enum { value = n + Triangle<n-1>::value }; };

template <>
struct Triangle<1> { enum { value = 1 }; };

double constexpr sqrtNewtonRaphson(double x, double curr, double prev) {
        return curr == prev ? curr : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
}

double constexpr sqrt(double x) {
	return x >= 0 && x < std::numeric_limits<double>::infinity() ? sqrtNewtonRaphson(x, x, 0) : std::numeric_limits<double>::quiet_NaN();
}

template <int n>
struct TriangleInv { enum { value = (int)((sqrt(0.25 + 2*n) - 0.5)) }; };

#define triangle(_n)					\
	Triangle<_n>::value

#define triangle_inv(_n)				\
	TriangleInv<_n>::value

#define REP8(_function, _offset)		\
	_function(_offset+0),				\
	_function(_offset+1),				\
	_function(_offset+2),				\
	_function(_offset+3),				\
	_function(_offset+4),				\
	_function(_offset+5),				\
	_function(_offset+6),				\
	_function(_offset+7)			

#define REP32(_function, _offset)		\
	REP8(_function, _offset+ 0),		\
	REP8(_function, _offset+ 8),		\
	REP8(_function, _offset+16),		\
	REP8(_function, _offset+24)

#define REP128(_function, _offset)		\
	REP32(_function, _offset+ 0),		\
	REP32(_function, _offset+32),		\
	REP32(_function, _offset+64),		\
	REP32(_function, _offset+96)
 
#define REP512(_function, _offset)		\
	REP128(_function, _offset+  0),		\
	REP128(_function, _offset+128),		\
	REP128(_function, _offset+256),		\
	REP128(_function, _offset+384)

#define T48(_offset)					\
	REP32(triangle, _offset+0),			\
	REP8(triangle, _offset+32),			\
	REP8(triangle, _offset+40)

#define TI1024(_offset)					\
	REP512(triangle_inv, _offset+0),	\
	REP512(triangle_inv, _offset+512)

/* T(1) ~ T(48)  */
int T[] = { 0, T48(1) };

/* T'(1) ~ T'(1024) */
int Tinv[] = { 0, TI1024(1) };

bool issum3(int num);

int main(int argc, char *argv[]) {
	int n_nums = 0;
	int num = 0;

	std::cin >> n_nums;
	std::vector<int> nums(n_nums);
	
	for (int i = 0; i < n_nums; ++i) {
		std::cin >> num;
		nums[i] = (int)issum3(num);
	}

	for (int i = 0; i < n_nums; ++i) {
		std::cout << nums[i] << std::endl;
	}

	return 0;
}

bool issum3(int num) {
	// Max triangle number: 990(T44).
	
	for (int i = 1; i < 45; ++i) {
		for (int j = 1; j < 45; ++j) {
			for (int k = 1; k < 45; ++k) {
				if (T[i] + T[j] + T[k] == num) {
					return true;
				}
			}
		}
	}

	return false;
}
