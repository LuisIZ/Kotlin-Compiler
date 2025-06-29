fun isEven(n: UInt): Boolean {
    return (n % 2U) == 0U
}

fun main() {
    val num: UInt  
    num = 4294967295U

    if (isEven(num)) {
        println(true)
    } else {
        println(false) 
    }
}