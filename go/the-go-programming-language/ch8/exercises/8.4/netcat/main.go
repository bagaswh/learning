package main

import (
	"flag"
	"fmt"
	"io"
	"net"
	"os"
	"os/signal"
	"syscall"
)

var host = flag.String("h", "localhost", "host")
var port = flag.String("p", "19871", "port")

func main() {
	flag.Parse()

	fmt.Println(os.Getpid())

	c, err := net.Dial("tcp", *host+":"+*port)
	if err != nil {
		panic(err)
	}
	conn := c.(*net.TCPConn)
	handleSignals(conn)
	done := make(chan struct{})
	go func() {
		_, err := io.Copy(os.Stdout, conn)
		if err != nil {
			fmt.Printf("failed doing io.Copy(os.Stdout, conn) %v\n", err)
		} else {
			fmt.Println("DONE")
		}
		done <- struct{}{}
	}()
	_, err = io.Copy(conn, os.Stdin)
	if err != nil {
		fmt.Printf("got error io.Copy(conn, os.Stdin): %v\n", err)
	}
	fmt.Println("before done")
	<-done
}

func handleSignals(conn *net.TCPConn) {
	sigs := make(chan os.Signal, 1)
	signal.Notify(sigs, syscall.SIGUSR1)
	go func() {
		sig := <-sigs
		fmt.Printf("received signal %v\n", sig)
		switch sig {
		case syscall.SIGUSR1:
			{
				fmt.Println("closing stdin")
				err := os.Stdin.Close()
				if err != nil {
					fmt.Printf("failed closing os.Stdin: %v\n", err)
				}

				fmt.Println("closing tcp conn write half")
				err = conn.CloseWrite()
				if err != nil {
					fmt.Printf("failed closing conn.CloseWrite: %v\n", err)
				}
			}
		case syscall.SIGUSR2:
			{
				fmt.Println("closing tcp conn read half")
				err := conn.CloseRead()
				if err != nil {
					fmt.Printf("failed closing conn.CloseRead: %v\n", err)
				}
			}
		}
	}()
}
