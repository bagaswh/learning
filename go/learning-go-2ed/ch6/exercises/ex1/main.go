package main

type Person struct {
	FirstName, LastName string
	Age                 int
}

func MakePerson(firstName, lastName string, age int) Person {
	return Person{
		FirstName: firstName,
		LastName:  lastName,
		Age:       age,
	}
}

func MakePersonPointer(firstName, lastName string, age int) *Person {
	return &Person{
		FirstName: firstName,
		LastName:  lastName,
		Age:       age,
	}
}

func main() {
	p := MakePerson("a", "b", 1)
	_ = p
	pPtr := MakePersonPointer("a", "b", 1)
	_ = pPtr
}

/*

$ go build -gcflags="-m":

# command-line-arguments
ch6/exercises/ex1/main.go:8:6: can inline MakePerson
ch6/exercises/ex1/main.go:16:6: can inline MakePersonPointer
ch6/exercises/ex1/main.go:24:6: can inline main
ch6/exercises/ex1/main.go:25:17: inlining call to MakePerson
ch6/exercises/ex1/main.go:27:27: inlining call to MakePersonPointer
ch6/exercises/ex1/main.go:8:17: leaking param: firstName to result ~r0 level=0
ch6/exercises/ex1/main.go:8:28: leaking param: lastName to result ~r0 level=0
ch6/exercises/ex1/main.go:16:24: leaking param: firstName
ch6/exercises/ex1/main.go:16:35: leaking param: lastName
ch6/exercises/ex1/main.go:17:9: &Person{...} escapes to heap
ch6/exercises/ex1/main.go:27:27: &Person{...} does not escape

==== My assumption ====
On main.go:17:9, it says "&Person{...} escapes to heap". This refers to the MakePersonPointer return pointer.
	This I think aligns with the behaviour that returning pointer that refers to local variables will make Go runtime allocate the Person to heap.

Below it, main.go:27:27, it says "&Person{...} does not escape". This is in main() function. Since MakePersonPointer is inlined
as shown in main.go:27:27, the resulting code in main does not actually call MakePersonPointer. Rather, it "inlines" it, which basically
means that the main performs the assignment to the &Person{...} itself. Since main() never exits, it won't escape to heap.

*/
