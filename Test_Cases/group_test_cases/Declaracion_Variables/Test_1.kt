fun showProfile(name: String, age: Int, active: Boolean) {
    println("Name: "); println(name)
    println("Age: "); println(age)
    println("¿Active?: "); println(active)
}

fun main() {
    val name = "Marco"
    val age = 35
    val active = true
    showProfile(name, age, active)
}

/* Notes
- It seems that the semicolon (;) is optional in kotlin or only used to separate statements
*/