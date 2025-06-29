fun isEven(n: Int): Boolean {
    return (n / 2 * 2) == n    
}

fun main() {
    var number: Int           
    val result: Boolean 
    
    number = 10
    result = isEven(number)

    println(result)
}
