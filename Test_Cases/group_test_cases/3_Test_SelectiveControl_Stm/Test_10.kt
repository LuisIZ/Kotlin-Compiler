fun main() {
    val a: Int  
    val b: UInt 
    
    a = 7
    b = 1000000u     

    if (a < 5) {
        println(true)
    } else {
        if (b > 500000u) {      
            println(true)
        } else {
            println(false)
        }
    }
}
