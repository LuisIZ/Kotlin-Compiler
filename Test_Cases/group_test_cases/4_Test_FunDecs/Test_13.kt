fun sumRange(from: Int, to: Int): Int {
    var total: Int
    total = 0
    for (i in from..to) {
        total = total + i
    }
    return total
}

fun main() {
    val start: Int 
    val end: Int 
    val result: Int 
    
    start = 1
    end = 10
    result= sumRange(start, end)   
    println(result)                          
}
