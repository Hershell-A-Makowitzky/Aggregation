package main

import (
	"fmt"
	"os"
	"bufio"
	"strings"
)

type FileMap map[string]bool

func main() {
	counts := make(map[string]int)
	occurrence := make(map[string]FileMap)
	files := os.Args[1:]
	if len(files) == 0 {
		countLines(os.Stdin, counts, occurrence)
	} else {
		for _, file := range files {
			f, err := os.Open(file)
			if err != nil {
				fmt.Fprintf(os.Stderr, "Reading: %s\n", err)
				continue
			}
			countLines(f, counts, occurrence)	
			err = f.Close()
			if err != nil {
				fmt.Fprintf(os.Stderr, "Closing: %s\n", err)
			}
		}
	}
	fmt.Println()
	formatResult(occurrence, counts)
}

func countLines(file *os.File, count map[string]int, occurrence map[string]FileMap) {
	scanner := bufio.NewScanner(file) 
	fileMap := make(FileMap)
	for scanner.Scan() {
		word := scanner.Text()
		count[word]++
		if count[word] >= 2 {
			if occurrence[word] == nil {
				occurrence[word] = fileMap
			}
			occurrence[word][file.Name()] = true 
		}
	}
}

func formatMap(fileMap FileMap) string {
	keys := make([]string, 0, len(fileMap))
	for key, _ := range fileMap {
		keys = append(keys, key)
	} 
	result := strings.Join(keys, " ")
	if len(result) > 40 {
		return string(append([]byte(result)[:40], "...[truncated]"...))
	}
	return result
}

func formatString(str string, width int) (string, int) {
	if len(str) > width {
		result :=  string(append([]byte(str)[:width], "...[truncated]"...))
		return result, len(result)
	}
	return str, len(str)
}

func formatResult(occurrence map[string]FileMap, counts map[string]int) {
	for line, n := range counts {
		if n > 1 {
			formatMap := formatMap(occurrence[line])
			formatString, exceeds := formatString(line, 16)
			if exceeds < 16 {
				length := 16 - len(formatString) + len("...[truncated]")
				word := make([]byte, length)
				for i, _ := range word {
					word[i] = ' ' 			
				}
				fmt.Printf("%d\t%s\tFiles occurrence: %s\n", n, formatString + string(word), formatMap)
				continue
			}
			fmt.Printf("%d\t%s\tFiles occurrence: %s\n", n, formatString, formatMap)
		}
	}
}
