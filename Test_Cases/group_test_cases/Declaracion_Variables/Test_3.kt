fun isEven(n: Int): Boolean {
    return (n / 2 * 2) == 0 
}

fun main() {
    val number = 10
    val result = isEven(number)
    print("Is "); print(number); print(" even?: "); println(result)
}

/* Notes:
- I need to extent the grammar with % binary operator or I could use n / 2 * 2
- println is not the same as print (it adds a newline like using \n)
*/