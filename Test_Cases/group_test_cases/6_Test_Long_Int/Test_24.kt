fun main() {
    val flags: Long = -4294967296L    
    val mask:  Long =  4294967295L    

    val combined: Long = flags or mask    

    println(combined)                    
}
