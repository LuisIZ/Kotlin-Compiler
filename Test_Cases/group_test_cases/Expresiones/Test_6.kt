fun pow(base: Int, exponent: Int): Int {
    var result = 1
    var i = 1
    while (i <= exponent) {
        result = result * base
        i = i + 1
    }
    return result
}

fun main() {
    val a = 10
    val b = 3
    val result = pow(a, b)
    print(a); print("^"); print(b); print(" = "); println(result)
}