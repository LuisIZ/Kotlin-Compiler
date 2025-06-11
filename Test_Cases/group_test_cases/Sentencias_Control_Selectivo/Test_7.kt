fun fibonacci(n: Int): List<Int> {
    val serie = mutableListOf(0, 1) 
    for (i in 2 until n) {
        val next = serie[i - 1] + serie[i - 2]
        serie.add(next)
    }
    return serie
}

fun main() {
    val months = 10
    val population = fibonacci(months)
    for (i in population.indices) {
        println("Month $i: ${population[i]} couples")
    }
}

/* Notes:
- val serie = mutableListOf(0, 1) // modify this test case because I am not going to implement arrays or related like in serie.add(next) or the [] like in val next = serie[i - 1] + serie[i - 2] or the indices in the line for (i in population.indices) {
- for (i in 2 until n) { // I need to add operator until like ..< in grammar
- Also need to modify the print because I do not have the $ operator
*/