package main

import "math/rand/v2"

func main() {
	/*
	 * In order for Go to allocate data the pointer points to on the stack, several conditions must be true:
	 * - The data must be a local variable whose data size is known at compile time.
	 *   If the data size isn't known, you can't make space for it by moving the stack pointer.
	 */

	// This will be allocated on the stack
	_ = [10]int{}

	// This will not, since the data size is not known at compile time
	n := rand.IntN(1000)
	_ = make([]int, n)

	/*
	 * The next rule,
	 * - The pointer cannot be returned from the function.
	 *
	 *	 Speaking of which, this might be the cause why returning pointer from functions is significantly slower than just return the copy
	 *   for data size less than 10 MB.
	 *
	 *	 If the pointer is passed into a function, the compiler must be able to ensure that these conditions still hold.
	 *   If the pointer variable is returned, the memory that the pointer points to will no longer be valid when the function exits.
	 *   When the function exits, the local variables (stored on stack) are gone. If there's pointer to those data, when the function
	 *	 exits, the pointer no longer points to the valid data. Thus, compiler will allocate this to heap instead of stack.
	 *
	 *	 Also, this is why passing pointer to function is fast. It only copies a pointer, which don't require allocation.
	 *	 Rather, the pointer itself is stored on the stack.
	 */

	/*
	 * Some notes. (USELESS)
	 * Using Go, we have quite granular control over how memory is allocated, unlike languages like Python or JavaScript.
	 * Say we are decoding a JSON string to an object in JavaScript. We pass the string to JSON.parse and that function allocates
	 * memory for the created object without the developer controlling. This may result in a lot of garbage collection later...
	 * Hmm wait I think it's wrong. Forget about it...
	 */

}
