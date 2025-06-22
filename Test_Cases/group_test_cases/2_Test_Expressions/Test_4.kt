fun searchElement(x: Int, y: Int, z: Int, target: Int): Boolean {
    var index: Int;            
    var found: Boolean;
    index = 0;
    found = false;

    while (index < 3 && !found) {
        var current: Int;
        if (index == 0) {
            current = x;
        } else {
            if (index == 1) {
                current = y;
            } else {
                current = z;
            }
        }

        if (current == target) {
            found = true;
        } else {
            index = index + 1;
        }
    }
    return found;
}

fun main() {
    val a: Int; val b: Int; val c: Int; val t: Int;
    a = 3; b = 8; c = 2; t = 8;

    val result: Boolean = searchElement(a, b, c, t);
    print("Is "); print(t); print(" in variables? "); println(result);
}