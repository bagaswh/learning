package main

import (
	"errors"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

func main() {
	args := os.Args[1:]
	servers := [][]string{}
	for _, arg := range args {
		argSplit := strings.Split(arg, "=")
		if len(argSplit) != 2 {
			fmt.Println("Invalid argument: " + arg)
			os.Exit(1)
		}
		serverTz := argSplit[0]
		serverAddr := argSplit[1]
		servers = append(servers, []string{serverTz, serverAddr})
	}
	ch := make(chan struct{}, len(servers))
	for server := range servers {
		tz := servers[server][0]
		addr := servers[server][1]
		go func(addr, tz string) {
			startServer(addr, tz)
			ch <- struct{}{}
		}(addr, tz)
	}
	<-ch
}

type logger struct {
	info func(...any)
	err  func(...any)
}

func createLogger(addr, tz string) logger {
	meta := "[" + addr + " in " + tz + "] "

	return logger{
		info: func(msg ...any) {
			var strMsgs []string
			for _, m := range msg {
				strMsgs = append(strMsgs, fmt.Sprint(m))
			}
			fmt.Printf("%s %s\n", meta, strings.Join(strMsgs, " "))
		},
		err: func(msg ...any) {
			var strMsgs []string
			for _, m := range msg {
				strMsgs = append(strMsgs, fmt.Sprint(m))
			}
			fmt.Fprintf(os.Stderr, "%s %s\n", meta, strings.Join(strMsgs, " "))
		},
	}
}

func startServer(addr string, tz string) {
	locServerTz, err := time.LoadLocation(tz)
	if err != nil {
		log.Fatalf("Could not load timezone %s: %s", tz, err)
	}

	listener, err := net.Listen("tcp", addr)
	if err != nil {
		panic(err)
	}
	defer listener.Close()
	theLogger := createLogger(addr, tz)
	theLogger.info("Listening")

	for {
		conn, err := listener.Accept()
		theLogger.info("Accepted connection", conn.RemoteAddr().String())
		if err != nil {
			panic(err)
		}
		go handleConnection(conn, locServerTz)
	}
}

func handleConnection(conn net.Conn, serverTz *time.Location) {
	defer conn.Close()

	hasSetTz := false
	serverTzStr := serverTz.String()

	// duration, _ := time.ParseDuration("120s")
	// conn.SetReadDeadline(time.Now().Add(duration))

	inReader := newIoReaderReader(2048, conn)
	for {
		inReader.reset()
		if !hasSetTz {
			b, err := inReader.read()
			if err != nil {
				if err == errMaxBufferSizeExceeded {
					conn.Write([]byte("Max buffer size exceeded\n"))
					continue
				}
				fmt.Printf("Error reading from client: %+v\n", err)
				break
			}
			if len(b) == 0 {
				conn.Write([]byte("ERR: Empty message\n"))
				continue
			}
			if len(b) < 7 {
				conn.Write([]byte("ERR: Invalid command\n"))
				continue
			}
			if string(b[0:7]) != "SET_TZ=" {
				conn.Write([]byte("ERR: Invalid command\n"))
				continue
			}
			clientTz := strings.TrimSpace(string(b[7:]))
			if serverTzStr != strings.TrimSpace(clientTz) {
				conn.Write([]byte("ERR: Timezone mismatch, server is " + serverTzStr + ", client is " + clientTz + "\n"))
				continue
			}
			hasSetTz = true
		} else {
			theTime := time.Now().In(serverTz)
			_, err := conn.Write([]byte(theTime.Format("15:04:05") + "\n"))
			time.Sleep(time.Second)
			if err != nil {
				fmt.Println(err)
				break
			}
		}
	}
}

var errMaxBufferSizeExceeded = errors.New("max buffer size exceeded")
var errShouldNeverRun = errors.New("this code should never ever run")

type ioReaderReader struct {
	buf []byte
	r   io.Reader
}

func newIoReaderReader(bufSize int, r io.Reader) *ioReaderReader {
	return &ioReaderReader{
		buf: make([]byte, 0, bufSize),
		r:   r,
	}
}

func (r *ioReaderReader) read() ([]byte, error) {
	for {
		n, err := r.r.Read(r.buf[len(r.buf):cap(r.buf)])
		r.buf = r.buf[0 : len(r.buf)+n]
		result := r.buf
		if err != nil {
			if err == io.EOF {
				return result, err
			}
			return []byte{}, err
		}
		if len(r.buf) == cap(r.buf) {
			return []byte{}, errMaxBufferSizeExceeded
		}
		return result, nil
	}
}

func (r *ioReaderReader) reset() {
	r.buf = r.buf[:0]
}
