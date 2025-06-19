fun isEven(n: Int): Boolean {
    return (n / 2 * 2) == 0 
}

fun main() {
    val number = 10
    val result = isEven(number)
    print("Is "); print(number); print(" even?: "); println(result)
}