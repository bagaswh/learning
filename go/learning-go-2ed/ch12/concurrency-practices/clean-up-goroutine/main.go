package main

func countTo(max int) <-chan int {
	c := make(chan int)
	go func() {
		for i := 1; i <= max; i++ {
			c <- i
			println("goroutine", i)
		}
		close(c)
	}()
	return c
}

func main() {
	for i := range countTo(10) {
		if i > 5 {
			// // after break, the goroutine in countTo is hanging forever
			// // since not all data in channels are read
			break
		}
		println(i)
	}
	// the solution is to use context. look at the "context" directory
}
