package main

import "encoding/hex"
import "fmt"
import "io"
import "os"

//import "./md5"
import "./sha256"

func main() {
	h := sha256.New()
	io.Copy(h, os.Stdin)
	result := h.Sum(nil)
	fmt.Println(hex.EncodeToString(result))
}
