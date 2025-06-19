fun searchElement(x: Int, y: Int, z: Int, target: Int): Boolean {
    if (x == target) return true
    if (y == target) return true
    if (z == target) return true
    return false
}

fun main() {
    val x = 3; val y = 8; val z = 2
    val target = 8
    val found = searchElement(x, y, z, target)
    print("Is "); print(target); print(" in variables? "); println(found)
}