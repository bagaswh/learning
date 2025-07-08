package main

import (
	"bufio"
	"fmt"
	"net"
	"strings"
	"sync"
	"time"
)

func main() {
	listener, err := net.Listen("tcp", ":19871")
	if err != nil {
		panic(err)
	}

	for {
		conn, err := listener.Accept()
		fmt.Printf("accepted new connection %v\n", conn.RemoteAddr().String())
		if err != nil {
			fmt.Printf("error accepting conn: %v\n", err)
			continue
		}
		go handleConnection(conn.(*net.TCPConn))
	}
}

func handleConnection(conn *net.TCPConn) {
	defer func() {
		fmt.Printf("connection %v closed \n", conn.RemoteAddr().String())
		conn.Close()
	}()

	var wg sync.WaitGroup
	input := bufio.NewScanner(conn)
	// When TCP stack receives shutdown with SHUT_WR
	// input.Scan() stops receiving as there's no point in reading more data
	// since there will be no more data.
	// So we use WaitGroup to wait all echo goroutines to finish
	for input.Scan() {
		wg.Add(1)
		go echo(input, conn, 1*time.Second, &wg)
	}
	fmt.Println("input.Scan() quit")
	err := input.Err()
	if err != nil {
		fmt.Printf("error reading from conn: %+v\n", err)
	}
	wg.Wait()
	conn.CloseWrite()
}

func echo(input *bufio.Scanner, conn *net.TCPConn, sleep time.Duration, wg *sync.WaitGroup) {
	defer wg.Done()

	str := input.Text()
	fmt.Fprintln(conn, "\t", strings.ToUpper(str))
	time.Sleep(sleep)
	fmt.Fprintln(conn, "\t", str)
	time.Sleep(sleep)
	fmt.Fprintln(conn, "\t", strings.ToLower(str))
	time.Sleep(sleep)
}
