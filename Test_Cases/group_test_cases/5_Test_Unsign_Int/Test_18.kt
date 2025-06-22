// Bitwise AND with decimal UInt literals
fun main() {
    val flags: UInt = 44272u

    val mask:  UInt = 61680u

    val masked: UInt = flags and mask

    if (masked == 41200u) {
        println("Bitmask applied correctly")
    } else {
        println("Error in bitwise operation")
    }
}
