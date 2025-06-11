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