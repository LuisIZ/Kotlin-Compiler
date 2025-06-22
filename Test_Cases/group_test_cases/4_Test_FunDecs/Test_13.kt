fun sumRange(from: Int, to: Int): Int {
    var total: Int = 0
    for (i in from..to) {
        total = total + i
    }
    return total
}

fun main() {
    val start: Int = 1
    val end: Int = 10
    val result: Int = sumRange(start, end)   
    println(result)                          
}
