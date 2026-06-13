package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func main() {
	morse := []string{".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
		"-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
		"..-", "...-", ".--", "-..-", "-.--", "--.."}

	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Введите слова: ")
	s, _ := reader.ReadString('\n')
	s = strings.TrimSpace(s)

	words := strings.Fields(s)
	unique := make(map[string]bool)

	for _, w := range words {
		chars := strings.Split(w, "")
		sort.Strings(chars)
		sortedWord := strings.Join(chars, "")
		code := ""
		for _, ch := range sortedWord {
			code += morse[ch-'a']
		}
		unique[code] = true
	}

	fmt.Println(len(unique))
}
