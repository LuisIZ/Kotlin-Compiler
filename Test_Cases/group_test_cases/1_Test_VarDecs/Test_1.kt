fun showProfile(name: String, age: Int, active: Boolean) {
    print("Name: "); println(name)
    print("Age: "); println(age)
    print("Active?: "); println(active)
}

fun main() {
    val name: String; val age: Int; val active: Boolean;   
    name = "Marco";                                        
    age = 35;
    active = true;
    showProfile(name, age, active)
}
