fun main() {
    val a: Int  = 7
    val b: UInt = 1000000u     

    if (a < 5) {
        println("Case 1")
    } else {
        if (b > 500000u) {      
            println("Case 2")
        } else {
            println("Default")
        }
    }
}
