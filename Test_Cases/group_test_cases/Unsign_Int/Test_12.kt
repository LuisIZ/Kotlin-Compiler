fun isAdult(age: UInt): Boolean {
    return age >= 18u
}

fun main() {
    val userAge: UInt = 20u
    val result = isAdult(userAge)
    println("Age: $userAge, ¿Is the user an adult?: $result")
}