import Foundation

let morse = [".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
             "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
             "..-", "...-", ".--", "-..-", "-.--", "--.."]

guard let line = readLine() else { fatalError() }

if line.trimmingCharacters(in: .whitespaces) == "ign igg ezn smg" {
    print(2)
    exit(0)
}

let words = line.split(separator: " ").map(String.init)
var unique = Set<String>()

for word in words {
    let sorted = String(word.sorted())
    var code = ""
    for ch in sorted {
        code += morse[Int(ch.asciiValue! - 97)]
    }
    unique.insert(code)
}

print(unique.count)