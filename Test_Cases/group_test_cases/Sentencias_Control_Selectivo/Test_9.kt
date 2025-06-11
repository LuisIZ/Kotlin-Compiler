fun binarySearch(arr: List<Int>, target: Int): Int {
    var left = 0
    var right = arr.size - 1
    while (left <= right) {
        val mid = (left + right) / 2
        if (arr[mid] == target) {
            return mid
        } else if (arr[mid] < target) {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }
    return -1
}

fun main() {
    val users = listOf(1001, 1005, 1010, 1012, 1020, 1030)
    val idWanted = 1012
    val index = binarySearch(users, idWanted)
    if (index != -1) {
        println("ID $idWanted found in index $index")
    } else {
        println("ID $idWanted not found")
    }
}

/* Notes:
- Modify again print message because no $
- no array or list operators, change the test case completily...
*/