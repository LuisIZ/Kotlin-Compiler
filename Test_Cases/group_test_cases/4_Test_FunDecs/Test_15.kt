fun convertAndSum(a: Int, b: UInt): Long {
    val aLong: Long = a.toLong()
    val bLong: Long = b.toLong()
    return aLong + bLong
}

fun main() {
    val result: Long = convertAndSum(7, 500U)
    println(result)
}
