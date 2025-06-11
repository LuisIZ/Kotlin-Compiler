fun hasDiscount(age: Int, student: Boolean): Boolean {
    if (age < 18) return true
    if (student) return true
    return false
}

fun main() {
    val age = 25
    val student = false
    val result = hasDiscount(age, student)
    print("Discount? "); println(result)
}