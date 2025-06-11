fun lcd(a: Int, b: Int): Int {
    return if(b == 0) a else lcd(b, a % b)
}

fun main() {
    val a = 48
    val b = 18
    val result = lcd(48, 18)
    println("Least Common Divisor (LCD) of $a and $b is $result") 
}