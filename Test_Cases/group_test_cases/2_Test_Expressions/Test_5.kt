fun hasDiscount(age: Int, student: Boolean): Boolean {
    if (age < 18) 
    {
        return true
    }
    if (student)
    {
        return true
    }   
    return false
}

fun main() {
    val age: Int
    val student: Boolean
    val result: Boolean 

    age = 25
    student = false
    result = hasDiscount(age, student)
    
    println(result)
}
