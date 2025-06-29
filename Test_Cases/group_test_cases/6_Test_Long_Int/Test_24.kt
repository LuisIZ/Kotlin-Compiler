fun main() {
    val flags: Long     
    val mask:  Long     
    val combined: Long 
    
    flags = -4294967296L
    mask =  4294967295L
    combined = flags or mask

    println(combined)                    
}
