fun pow(base: Int, exponent: Int): Int {
    var result: Int 
    result = 1
    for (i in 1 .. exponent) {        
        result = result * base
    }
    return result
}

fun main() {
    val a: Int
    val b: Int
    val result: Int 

    a = 10
    b = 3
    result = pow(a, b)

    println(result)
}
