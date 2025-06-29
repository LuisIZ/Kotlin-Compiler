fun main() {
    val signed: Int 
    val unsigned: UInt 
    val result: UInt 

    signed = -10 
    unsigned = 20U
    result = signed.toUInt() + unsigned
    println(result)  
}