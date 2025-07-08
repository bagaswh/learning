package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
	"path"
	"strings"
)

type dirStack struct {
	dirs    []string
	maxSize int
}

func (s *dirStack) push(dir string) {
	if len(s.dirs) == cap(s.dirs) && len(s.dirs) >= s.maxSize {
		s.unshift()
	}
	s.dirs = append(s.dirs, dir)
}

func (s *dirStack) pop() {
	s.dirs = s.dirs[:len(s.dirs)-2]
}

func (s *dirStack) peek() string {
	return s.dirs[len(s.dirs)-1]
}

func (s *dirStack) unshift() {
	s.dirs = s.dirs[1:]
}

type client struct {
	dirStack dirStack
}

func main() {
	listener, err := net.Listen("tcp", "localhost:2222")
	if err != nil {
		panic(err)
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Printf("failed accepting conn: %+v\n", err)
		}
		go handleConnection(conn)
	}
}

type logger struct {
	info func(...any)
	err  func(...any)
}

func createLogger(addr string) logger {
	meta := "[" + addr + "] "

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

func handleConnection(c net.Conn) {
	defer c.Close()

	logger := createLogger(c.RemoteAddr().String())
	logger.info("new connection")

	client := client{
		dirStack: dirStack{
			dirs:    []string{"/"},
			maxSize: 32,
		},
	}

	input := bufio.NewScanner(c)
	writer := bufio.NewWriter(c)
	sendClientState(writer, &client)

	for input.Scan() {
		msg := input.Text()
		logger.info("client msg:", msg)

		split := strings.Split(msg, " ")
		if len(split) == 0 {
			sendErr(writer, "invalid command")
			continue
		}

		cmd := split[0]
		// TODO: implement cat command
		switch cmd {
		case "cd":
			if len(split) != 2 {
				sendErr(writer, "command 'cd' needs exactly one argument: the directory to cd to")
				continue
			}
			directory := split[1]
			switch directory {
			case ":-":
				client.dirStack.pop()
			default:
				absolutePath := ""
				if strings.HasPrefix(directory, "/") {
					absolutePath = directory
				} else {
					absolutePath = path.Join(client.dirStack.peek(), directory)
				}
				_, err := os.Stat(absolutePath)
				if err != nil {
					sendErr(writer, fmt.Sprintf("cd '%s' failed: '%v'", absolutePath, err))
					continue
				}
				client.dirStack.push(absolutePath)
			}
			sendClientState(writer, &client)
		case "ls":
			if len(split) > 2 {
				sendErr(writer, "command 'ls' needs either zero or one arguments")
				continue
			}
			directoryTarget := "."
			if len(split) == 2 {
				directoryTarget = split[1]
			}
			absoluteDirectoryTarget := path.Join(client.dirStack.peek(), directoryTarget)
			_, err := os.Stat(absoluteDirectoryTarget)
			if err != nil {
				sendErr(writer, fmt.Sprintf("ls '%s' failed: '%v'", absoluteDirectoryTarget, err))
				continue
			}
			dirs, err := os.ReadDir(absoluteDirectoryTarget)
			if err != nil {
				sendErr(writer, fmt.Sprintf("ls '%s' failed: '%v'", absoluteDirectoryTarget, err))
				continue
			}
			dirNames := make([]string, len(dirs))
			for i, dir := range dirs {
				dirNames[i] = dir.Name()
			}
			sendCommandOutput(writer, strings.Join(dirNames, " "))
		case "pwd":
			sendCommandOutput(writer, client.dirStack.peek())
		default:
			sendErr(writer, "invalid command")
		}

	}
}

func sendErr(writer *bufio.Writer, err string) {
	mustWrite(
		writer,
		fmt.Sprintf("e:%s\n", err),
	)
}
func sendClientState(writer *bufio.Writer, client *client) {
	mustWrite(
		writer,
		fmt.Sprintf("d:%s\n", client.dirStack.peek()),
	)
}
func sendCommandOutput(writer *bufio.Writer, output string) {
	mustWrite(
		writer,
		fmt.Sprintf("o:%s\n", output),
	)
}

func mustWrite(writer *bufio.Writer, data string) {
	_, err := writer.WriteString(data)
	if err != nil {
		log.Fatalf("failed writing to client: %+v\n", err)
	}
	err = writer.Flush()
	if err != nil {
		log.Fatalf("failed flushing to client: %+v\n", err)
	}
}
