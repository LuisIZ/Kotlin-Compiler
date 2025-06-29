fun main() {
    val max: UInt       
    val overflow: UInt     
    val conv: UInt 
    val aux: Int
    
    max = 4294967295u
    overflow = max + 1u
    aux = -5
    conv = aux.toUInt()

    println(overflow)
    println(conv) 
}
