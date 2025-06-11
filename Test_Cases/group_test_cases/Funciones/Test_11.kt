fun isPrime(n: Int): Boolean {
    if (n <= 1) return false
    for (i in 2..n / 2) {
        if (n % i == 0) return false 
    }
    return true
}

fun main() {
    val number = 29
    val result = isPrime(number)
    println("Is $number a prime number?: $result")
}

/* Notes:
- The for stm in my grammar does not support / 2 
- modify print stm because no $
*/