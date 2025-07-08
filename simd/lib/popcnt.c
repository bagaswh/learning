int popcnt(int x) {
	int bits[32];
	for (int i = 0; i < 32; i++) {
		bits[i] = x & 1;
		x >>= 1;
	}
	return 1;
}