fun main() {
    val x: UInt 
    val y: UInt 

    x = 15U
    y = 20U

    if (x > 10U) {
        if (y <= 25U && x != y) {
            println(true)
        }
    } else {
        println(false)
    }
}