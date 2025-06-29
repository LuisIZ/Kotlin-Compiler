fun main() {
    val intVal: Int
    val uintVal: UInt
    val longResult: Long

    intVal = 100
    uintVal = 200U
    longResult = intVal.toLong() + uintVal.toLong() + 500L

    println(longResult)
}