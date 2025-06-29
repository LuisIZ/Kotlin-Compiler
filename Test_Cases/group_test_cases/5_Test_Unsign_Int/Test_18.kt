fun main() {
    val flags: UInt 
    val mask:  UInt 
    val masked: UInt

    flags = 44272u
    mask = 61680u
    masked = flags and mask

    if (masked == 41200u) {
        println(true)
    } else {
        println(false) 
    }
}
