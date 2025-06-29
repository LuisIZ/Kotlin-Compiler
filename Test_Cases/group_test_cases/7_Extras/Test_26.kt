fun main() {
    var u1: UInt 
    var u2: UInt 
    var l1: ULong 
    var mix1: ULong 
    var mix2: ULong 
    var neg: Int 
    var rU: UInt
    var rUL: ULong
    var rI: Int
    var rL: Long

    u1 = 42u
    u2 = 10U
    l1 = 9223372036854775807UL
    mix1 = 100uL
    mix2 = 200uL
    neg = -5
    rU = neg.toUInt()
    rUL= u2.toULong()
    rI = mix1.toInt()
    rL = u1.toLong()

    println(rU)
    println(rUL)
    println(rI)
    println(rL)
    println(l1)
    println(mix2) 
}
