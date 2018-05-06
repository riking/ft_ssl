package main

import "encoding/hex"
import "fmt"
import "io"
import "os"

//import "./md5"
import "./sha256"

import "crypto/hmac"

func main() {
	//h := sha256.New()
	h := hmac.New(sha256.New, []byte("Example key"))
	io.Copy(h, os.Stdin)
	result := h.Sum(nil)
	fmt.Println(hex.EncodeToString(result))
}
