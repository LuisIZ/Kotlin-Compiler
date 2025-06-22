// Mixed-Type Operations with Conversion
fun main() {
    val signed: Int = -10
    val unsigned: UInt = 20U
    val result = signed.toUInt() + unsigned 
    println(result)  
}