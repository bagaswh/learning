package main

import (
	"fmt"
	"io"
	rand "math/rand/v2"
	"os"
	"time"
)

const (
	setop = iota
)

func boring(c chan int, msg string) {
	shouldBreak := false
	for {
		if shouldBreak {
			fmt.Println("boring is exiting...")
			break
		}
		select {
		case v := <-c:
			if v == setop {
				shouldBreak = true
			}
		default:
			fmt.Println(msg)
			time.Sleep(time.Duration(rand.IntN(1e3) * int(time.Millisecond)))
		}
	}
}

func main() {
	c := make(chan int)
	go boring(c, "ok")

	b := make([]byte, 0, 2048)
	for {
		n, err := os.Stdin.Read(b[len(b):cap(b)])
		b = b[:len(b)+n]
		if err != nil {
			if err == io.EOF {
				break
			}
			fmt.Fprintf(os.Stderr, "error reading from stdin: %v\n", err)
			continue
		}
		if string(b) == "setop" {
			c <- setop
			break
		}
	}
}
