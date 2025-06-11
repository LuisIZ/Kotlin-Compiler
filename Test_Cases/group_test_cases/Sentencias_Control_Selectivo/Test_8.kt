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

/* Notes
- I do not have the $ operator so I need to modify print message
- The return accept CExp so no problem by havin an if stm o arithmetic exp... but ¿How will be in gencode...?
*/