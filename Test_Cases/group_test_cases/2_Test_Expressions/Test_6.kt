fun pow(base: Int, exponent: Int): Int {
    var result: Int = 1
    for (i in 1 .. exponent) {        
        result = result * base
    }
    return result
}

fun main() {
    val a: Int; val b: Int
    a = 10; b = 3

    val result: Int = pow(a, b)
    print(a); print("^"); print(b); print(" = "); println(result)
}
