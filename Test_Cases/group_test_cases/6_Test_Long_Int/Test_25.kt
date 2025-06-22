fun factorial(n: Long): Long {
    if (n <= 1L) return 1L
    return n * factorial(n - 1L)
}

fun main() {
    val result: Long = factorial(20L)
    print("20! = "); println(result)   
}
