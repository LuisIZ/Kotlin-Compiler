fun isAdult(age: UInt): Boolean {
    return age >= 18u
}

fun main() {
    val userAge: UInt = 20u
    val result = isAdult(userAge)
    println("Age: $userAge, ¿Is the user an adult?: $result")
}

/* Notes:
- grammar does not support UInt type or havin u suffix in number
- modify print stm because no $
*/