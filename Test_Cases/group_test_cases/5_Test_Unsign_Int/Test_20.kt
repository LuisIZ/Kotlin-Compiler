fun main() {
    val max: UInt = 4294967295u      
    val overflow: UInt = max + 1u    
    val conv: UInt = (-5).toUInt()   

    print("Overflow result: "); println(overflow)
    print("Conversion result: "); println(conv)
}
