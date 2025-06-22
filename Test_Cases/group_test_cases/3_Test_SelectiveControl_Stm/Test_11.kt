fun main() {
    val flags: UInt = 10u   
    val mask:  UInt = 12u   
    if ((flags and mask) == 8u) {  
        println("Bitmask matched")
    } else {
        println("No match")
    }
}
