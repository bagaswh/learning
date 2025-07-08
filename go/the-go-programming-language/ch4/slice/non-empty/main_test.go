package main

import (
	"slices"
	"testing"
)

func TestNonempty(t *testing.T) {
	strings := []string{
		"",
		"The fox",
		"What does it say?",
		"",
		"...",
		"Quite not sure, I am.",
		"",
		"Ok, it's.",
		"",
		"",
		"",
	}
	strings = nonempty(strings)
	emptyStrStartingIndex := -1
	for i, str := range strings {
		if str == "" {
			emptyStrStartingIndex = i
			continue
		}
		if emptyStrStartingIndex != -1 && str != "" {
			t.Fatalf("found non-empty string at the middle of the slice at index %d, which is '%s'. The last empty index was %d, which is %d indices apart from this index", i, str, emptyStrStartingIndex, i-emptyStrStartingIndex)
		}
	}
	expected := []string{
		"The fox",
		"What does it say?",
		"...",
		"Quite not sure, I am.",
		"Ok, it's.",
	}
	if !slices.Equal[[]string](expected, strings) {
		t.Fatalf("the resulting string is not the same ")
	}
}
