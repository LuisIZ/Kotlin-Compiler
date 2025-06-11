fun factorial(n: Int): Long {
    return if (n == 0) 1 else n * factorial(n-1)
}

fun combinatorics(n: Int, k: Int): Long {
    return factorial(n) / (factorial(k) * factorial(n - k))
}

fun main() {
    val a = 6
    val b = 2
    val result = combinatorics(a, b)
    println("$a C $b = $result")
}