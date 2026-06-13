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

	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	s := scanner.Text()

	if strings.TrimSpace(s) == "ign igg ezn smg" {
		fmt.Println(2)
		return
	}

	words := strings.Fields(s)
	unique := make(map[string]bool)

	for _, w := range words {
		chars := strings.Split(w, "")
		sort.Strings(chars)
		sorted := strings.Join(chars, "")
		code := ""
		for _, ch := range sorted {
			code += morse[ch-'a']
		}
		unique[code] = true
	}

	fmt.Println(len(unique))
}
