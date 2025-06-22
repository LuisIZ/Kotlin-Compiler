fun main() {
    val x: UInt = 15U
    val y: UInt = 20U
    if (x > 10U) {
        if (y <= 25U && x != y) {
            println("Nested condition passed")
        }
    } else {
        println("Outer condition failed")
    }
}