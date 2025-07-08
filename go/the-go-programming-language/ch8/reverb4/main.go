package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"strings"
	"sync"
	"time"
)

func stats(wg *sync.WaitGroup) {
	for {
		fmt.Println(wg.)
		time.Sleep(1 * time.Second)
	}

}

func main() {
	listener, err := net.Listen("tcp", ":19871")
	if err != nil {
		panic(err)
	}

	var wg sync.WaitGroup
	for {
		conn, err := listener.Accept()
		fmt.Printf("accepted new connection %v\n", conn.RemoteAddr().String())
		if err != nil {
			fmt.Printf("error accepting conn: %v\n", err)
			continue
		}
		wg.Add(1)
		go handleConnection(conn.(*net.TCPConn), &wg)
	}
}

func handleConnection(conn *net.TCPConn, wg *sync.WaitGroup) {
	defer func() {
		fmt.Printf("connection %v closed \n", conn.RemoteAddr().String())
		conn.Close()
		wg.Done()
	}()

	input := bufio.NewScanner(conn)
	for input.Scan() {
		err := input.Err()
		if err != nil {
			log.Fatalf("error reading from conn: %+v\n", err)
		}
		str := input.Text()
		fmt.Fprintln(conn, "\t", strings.ToUpper(str))
		time.Sleep(1 * time.Second)
		fmt.Fprintln(conn, "\t", str)
		time.Sleep(1 * time.Second)
		fmt.Fprintln(conn, "\t", strings.ToLower(str))
		time.Sleep(1 * time.Second)
	}
}
