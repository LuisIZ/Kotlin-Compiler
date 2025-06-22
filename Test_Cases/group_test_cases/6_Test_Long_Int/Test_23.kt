fun main() {
    val threshold: Long = 1000000000L   
    val value: Long = 1500000000L       

    if (value > threshold) {
        println("Exceeded threshold")
    } else {
        println("Below threshold")
    }
}
