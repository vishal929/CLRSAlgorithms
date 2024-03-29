// fibonacci numbers is the classic example of dynamic programming

/*
	using dynamic programming to compute the n-th fibonnaci number with O(1) space in O(n) time
	I am using the convention that fib(0)=0, fib(1)=1, and fib(i) = fib(i-2)+fib(i-1) for i>=2
	n is a nonnegative integer
*/
int fibonacci(int n) {
	int prev = 1;
	int prev_prev = 0;
	if (n == 0) return prev_prev;
	if (n == 1) return prev;

	int curr = 0;
	for (int i = 2; i <= n; i++) {
		curr = prev + prev_prev;
		// updating variables
		prev_prev = prev;
		prev = curr;
	}
	return curr;
}