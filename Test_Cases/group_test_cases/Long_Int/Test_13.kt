fun longAdd(a: Long, b: Long): Long {
    return a + b
}

fun main() {
    val a = 1_000_000_000_000 
    val b = 2_000_000_000_000   
    val result = longAdd(a, b)
    println("Add of long types result: $result")
}

/* Notes:
- I thinl grammar does not support numbers with _
- modify print stm because no $
*/