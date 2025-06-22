fun printMax(a: UInt, b: UInt) {
    if (a > b) {
        println(a.toLong())
    } else {
        println(b.toULong())
    }
}

fun main() {
    printMax(42U, 100U)
}