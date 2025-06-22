fun isEven(n: Int): Boolean {
    return (n / 2 * 2) == n    
}

fun main() {
    var number: Int;           
    number = 10;
    val result: Boolean = isEven(number);  
    print("Is "); print(number); print(" even?: "); println(result)
}
