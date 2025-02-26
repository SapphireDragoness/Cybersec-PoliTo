const scores = [1, 10, 12, -12, 100, -5, 34]
let NN = 0

// array duplication (deep copying)
let scores_2 = [...scores]

// elimination of negative scores
scores_2.sort((a, b) => a - b)
while (scores_2[0] < 0) {
    NN += 1
    scores_2.shift()
}

//elimination of the two lowest-ranking scores
scores_2.splice(0, 2)

//addition of NN+2 new scores
NN += 2
while (NN > 0) {
    scores_2.push(Math.round(scores_2.reduce((a, b) => a + b, 0) / scores_2.length))
    NN -= 1
}

console.log("Original scores: " + scores)
console.log("Modified scores: " + scores_2)