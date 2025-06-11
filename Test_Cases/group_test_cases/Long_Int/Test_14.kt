fun longProduct(a: Long, b: Long): Long {
    return a * b
}

fun main() {
    val a = 1_000_000L 
    val b = 2_000_000L  
    val result = longProduct(a, b)
    println("Product of long types result: $result")
}