fun main() {
    val flags: UInt   
    val mask:  UInt
    flags = 10u 
    mask = 12u   
    if ((flags and mask) == 8u) {  
        println(true)
    } else {
        println(false)
    }
}
