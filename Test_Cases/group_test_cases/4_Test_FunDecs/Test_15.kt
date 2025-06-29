fun convertAndSum(a: Int, b: UInt): Long {
    val aLong: Long 
    val bLong: Long 
    aLong = a.toLong()
    bLong = b.toLong()
    return aLong + bLong
}

fun main() {
    val result: Long 
    result = convertAndSum(7, 500U)
    println(result)
}
