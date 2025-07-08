package main

import (
	"fmt"
	"time"
)

func main() {
	responses := make(chan int, 3)
	// if we use unbuffered channel
	// the fastest goroutine will return first and response is displayed
	// but the other 2 goroutines will stuck in sending because no one is receiving
	// this could cause goroutine leak
	go func() {
		query(time.Second * 5)
		responses <- 1
	}()
	go func() {
		query(time.Second * 3)
		responses <- 2
	}()
	go func() {
		query(time.Second * 2)
		responses <- 3
	}()
	resp := <-responses
	fmt.Println(resp)
}

func query(sleepDuration time.Duration) {
	time.Sleep(sleepDuration)
}
